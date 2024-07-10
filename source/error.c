/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:15:45 by atorma            #+#    #+#             */
/*   Updated: 2024/07/10 15:58:18 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void error_print(char *s, char *error_str)
{
	char	buffer[1024];

	if (!error_str)
		error_str = strerror(errno);
	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	ft_strlcat(buffer, s, sizeof(buffer) - 1);
	ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	ft_strlcat(buffer, error_str, sizeof(buffer) - 1);
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}

void error_builtin(char *builtin, char *s, char *error_str)
{
	char	buffer[1024];

	if (!error_str)
		error_str = strerror(errno);
	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	ft_strlcat(buffer, builtin, sizeof(buffer) - 1);
	ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	ft_strlcat(buffer, s, sizeof(buffer) - 1);
	if (error_str[0] != '\0')
	{
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
		ft_strlcat(buffer, error_str, sizeof(buffer) - 1);
	}
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}

void	error_cmd(char *s)
{
	char	buffer[1024];

	ft_strlcpy(buffer, s, sizeof(buffer) - 1);
	ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	ft_strlcat(buffer, "command not found", sizeof(buffer) - 1);
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}
