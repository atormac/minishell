/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:56:51 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 12:57:50 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include <fcntl.h>

static void	convert_hex(char *src, char *dst, ssize_t size)
{
	char			*table;
	unsigned char	c;

	table = "0123456789abcdef";
	while (size-- > 0)
	{
		c = *src;
		*dst++ = table[c >> 4];
		*dst++ = table[c & 0x0f];
		src++;
	}
	*dst = 0;
}

static int	generate_filename(char *out, size_t out_size)
{
	char	tmp[32];
	char	result[64];
	int		fd;
	ssize_t	size;

	ft_strlcpy(out, "/tmp/tmp-", out_size);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (0);
	size = read(fd, tmp, 16);
	close(fd);
	if (size < 0)
		return (0);
	convert_hex(tmp, result, size);
	ft_strlcat(out, result, out_size);
	return (1);
}

int	heredoc_file(int *out_write, int *out_read)
{
	int		fd_write;
	int		fd_read;
	char	filepath[128];

	if (!generate_filename(filepath, sizeof(filepath)))
	{
		error_print("Error generating heredoc filename!\n", "");
		return (0);
	}
	fd_write = open(filepath, O_CREAT | O_EXCL | O_WRONLY | O_TRUNC, 0600);
	fd_read = open(filepath, O_RDONLY, 0600);
	if (fd_write == -1 || fd_read == -1)
	{
		error_print("Error creating heredoc tmp file!\n", NULL);
		close(fd_write);
		close(fd_read);
		return (0);
	}
	*out_write = fd_write;
	*out_read = fd_read;
	unlink(filepath);
	return (1);
}
