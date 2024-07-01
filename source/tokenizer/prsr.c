/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:04:51 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/01 18:34:30 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tokenizer.h"


t_ast	*ft_get_ast_node(int type);
t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms);

void	ft_free_ast(t_ast *ast)
{
	t_ast	*curr;
	t_ast	*tmp;

	if (!ast)
		return ;
	if (ast->left)
		ft_free_ast(ast->left);
	if (ast->right)
		ft_free_ast(ast->right);
	if (ast->str)
		free(ast->str);
	if (ast->io)
	{
		curr = ast->io;
		while (curr)
		{
			tmp = curr;
			free(curr->str);
			curr = curr->io;
			free(tmp);
		}
	}
	free(ast);
}

int	ft_prcd(int type)
{
	if (type == t_and || type == t_or)
		return (0);
	return (1);
}

int	ft_is_tkn(t_tkns *tkns)
{
	if (tkns->curr_tkn >= tkns->i)
		return (0);
	return (1);
}

int	ft_is_tkn_bop(t_tkns *tkns)
{
	int	type;

	if (!ft_is_tkn(tkns))
		return (0);
	type = tkns->arr[tkns->curr_tkn].type;
	if (type == t_pipe || type == t_or || type == t_and)
		return (type);
	return (0);	
}

int	ft_is_tkn_io(t_tkns *tkns)
{
	int	type;
	
	if (!ft_is_tkn(tkns))
		return (0);
	type = tkns->arr[tkns->curr_tkn].type;
	if (type == t_lwr || type == t_bgr || type == t_lwrlwr || type == t_bgrbgr)
		return (type);
	return (0);	
}

int	ft_is_tkn_cmnd(t_tkns *tkns)
{
	int	type;
	
	if (!ft_is_tkn(tkns))
		return (0);
	type = tkns->arr[tkns->curr_tkn].type;
	if (type == 0)
		return (1);
	return (0);	
}

char	*ft_strjoin_space(char *s1, char *s2)
{
	char	*part;
	char	*final;

	if (!s1 || !s2)
		return (0);
	part = ft_strjoin(s1, " ");
	if (!part)
		return (0);
	final = ft_strjoin(part, s2);
	free(part);
	return (final);
}

int	ft_join_cmnd(t_tkns *tkns, t_ast *cmnd_node)
{
	char	*tmp;

	if (!cmnd_node->str)
		cmnd_node->str = ft_strdup("");
	if (!cmnd_node->str)
		return (0);
	while (ft_is_tkn_cmnd(tkns))
	{	
		tmp = cmnd_node->str;
		cmnd_node->str = ft_strjoin_space(cmnd_node->str, tkns->arr[tkns->curr_tkn].str);
		if (!cmnd_node)
		{
			free(tmp);
			return (0);
		}
		free(tmp);
		tkns->curr_tkn++;
	}
	return (1);
}

void	ft_add_io_node(t_ast *cmnd_node, t_ast *io_node)
{
	t_ast	*curr;

	if (!cmnd_node->io)
	{
		cmnd_node->io = io_node;
		return ;
	}
	curr = cmnd_node->io;
	while (curr && curr->io)
		curr = curr->io;
	curr->io = io_node; 
}

int	ft_get_io(t_tkns *tkns, t_ast *cmnd_node, t_ms *ms)
{
	t_ast	*io_node;
	int		type;

	(void) ms;
	while (ft_is_tkn_io(tkns))
	{
		type = ft_is_tkn_io(tkns);	
		tkns->curr_tkn++;
		if (!ft_is_tkn_cmnd(tkns))
		{
			printf("ERROR1"); //ERROR syntax
			return (0);
		}
		io_node = ft_get_ast_node(type);
		if (!io_node)
		{
			printf("ERROR7");//MEM error
			return (0);
		}
		io_node->str = ft_strdup(tkns->arr[tkns->curr_tkn].str);
		if (!io_node->str)
		{
			free(io_node);
			return (0);
		}
		ft_add_io_node(cmnd_node, io_node);
		tkns->curr_tkn++;
	}
	return (1);
}

t_ast	*ft_get_cmnd(t_tkns *tkns, t_ms *ms)
{
	t_ast	*cmnd_node;

	cmnd_node = ft_get_ast_node(0);
	if (!cmnd_node)
	{
		printf("ERROR7");//MEM error
		return (0);
	}
	while (ft_is_tkn_cmnd(tkns) || ft_is_tkn_io(tkns))
	{
		if (ft_is_tkn_cmnd(tkns))
		{
			if (!ft_join_cmnd(tkns, cmnd_node))
				printf("ERROR8");//ERROR
		}
		else if (ft_is_tkn_io(tkns))
		{
			if (!ft_get_io(tkns, cmnd_node, ms))
				printf("ERROR9");//ERROR
		} 
	}
	return (cmnd_node);
}

t_ast	*ft_get_branch(t_tkns *tkns, t_ms *ms)
{
	t_ast	*branch;

	if (ft_is_tkn_bop(tkns) || tkns->arr[tkns->curr_tkn].type == t_prnths_cls)
	{
		printf("ERROR4");//ERROR syntax
		return (0);
	}
	else if (tkns->arr[tkns->curr_tkn].type == t_prnths_opn)
	{
		tkns->curr_tkn++;
		branch = ft_get_ast(tkns, 1, ms);
		if (!branch)
		{
			printf("ERROR5");//mem error
			return (0);
		}
		if (!ft_is_tkn(tkns) || tkns->arr[tkns->curr_tkn].type != t_prnths_cls)
		{
			printf("ERROR6");//;syntax error
			return (branch);
		}
		tkns->curr_tkn++;
		return (branch);
	}
	else
		return (ft_get_cmnd(tkns, ms));
}

t_ast	*ft_get_ast_node(int type)
{
	t_ast	*new_node;

	new_node = (t_ast *) ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

t_ast	*ft_merge_branch(t_ast *ast, int op, t_ast *new_branch, t_ms *ms)
{
	t_ast	*new_ast;

	(void) ms;	
	if (!new_branch)
		return (ast);
	new_ast = ft_get_ast_node(op);
	if (!new_ast)
	{
		printf("ERROR3");//MEMORY error
		return (0);
	}
	new_ast->left = ast;
	new_ast->right = new_branch;
	return (new_ast);
}

t_ast	*ft_get_ast(t_tkns *tkns, int tree_top, t_ms *ms)
{
	t_ast	*ast;
	int		op;

	if (!ft_is_tkn(tkns))
		return (0);
	ast = ft_get_branch(tkns, ms);
	if (!ast)
		return (0); 	
	while ((tree_top && ft_is_tkn_bop(tkns)) || (!tree_top && ft_is_tkn_bop(tkns) == t_pipe))
	{
		op = tkns->arr[tkns->curr_tkn].type;
		tkns->curr_tkn++;
		if (!ft_is_tkn(tkns))
		{
			printf("ERROR1");//ERROR syntax
			return (ast);
		}
		ast = ft_merge_branch(ast, op, ft_get_ast(tkns, 0, ms), ms);
		if (!ast)
		{
			printf("ERROR2");
			return (0);//free ast and right, return NULL
		}
	}
	return (ast);
}


void	ft_print_ast(t_ast *ast)
{
	t_ast *curr;

	if (!ast)
		return ;
	printf("Ast type %d, str %s", ast->type, ast->str);
	if (!ast->io)
		printf("\n");
	else
	{
		curr = ast->io;
		while (curr)
		{
			printf(", IO type: %d, s: %s", curr->type, curr->str);
			curr = curr->io;
		}
		printf("\n");
	}
	if (ast->left)
		ft_print_ast(ast->left);
	if (ast->right)
		ft_print_ast(ast->right);
}

/*
int main(void)		
{		
	//char *line = "(1 > outfile.txt > out2 > out3 | 3) && (4 || (5 && (6 && 7 || 8)))";
	//char *line = "6 && 7 || 8";
	printf("%s\n", line);

	t_tkns *tkns = ft_get_tokens(line);
	if (!tkns)
		return (1);
	for (int i = 0; i < tkns->i; i++)
	{
		//printf("Type %d str %s\n", tkns.arr[i].type, tkns.arr[i].str);
	}

	printf("------------AST-------------- i=%ld curr=%ld\n", tkns->i, tkns->curr_tkn);
	t_ast *ast = ft_get_ast(tkns, 1);

	ft_print_ast(ast);
	ft_free_ast(ast);
	ft_free_tkns(&tkns);
	return 0;
}
*/
