
#include "../include/minishell.h"
#include <fcntl.h>

int	open_infile(char *file, int is_heredoc)
{
	int		fd;

	if (is_heredoc)
		file = "heredoc";
	if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
		return (-1);
	fd = open(file, O_RDONLY, 0644);
	return (fd);
}

int	open_outfile(char *file, int is_heredoc)
{
	int		fd;
	int		flags;

	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (is_heredoc)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		return (-1);
	fd = open(file, flags, 0644);
	return (fd);
}

static void	dup_close(int a, int to_a, int b, int to_b)
{
	dup2(a, to_a);
	close(a);
	dup2(b, to_b);
	close(b);
}

static void	redirect_io(t_ast *ast)
{
	int	file_fd;
	int	to_fd;

	to_fd = STDIN_FILENO;
	if (ast->io->type == 4)
	{
		to_fd = STDOUT_FILENO;
		file_fd = open_outfile(ast->io->str, 0);
	}
	else
		file_fd = open_infile(ast->io->str, 0);
	if (file_fd == -1)
	{
		ft_putstr_fd("file error\n", 2);
		return ;
	}
	dup2(file_fd, to_fd);
}


void	redirect(t_ms *ms, t_ast *ast, int cmd_id, int *prev_fd)
{
	if (ast->io)
		redirect_io(ast);
	if (cmd_id == CMD_FIRST)
	{
		close(ms->pipe_read);
		if (dup2(ms->pipe_write, STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else if (cmd_id == CMD_MIDDLE)
		dup_close(ms->pipe_write, STDOUT_FILENO, prev_fd[0], STDIN_FILENO);
	else if (cmd_id == CMD_LAST)
	{
		close(prev_fd[1]);
		if (dup2(prev_fd[0], STDIN_FILENO) == -1)
			perror("dup2");
	}
}

