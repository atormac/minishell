/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:42:02 by atorma            #+#    #+#             */
/*   Updated: 2024/05/01 18:48:42 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*pos_newline(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*line_join(char *s1, size_t s1_len, char *s2, size_t s2_len)
{
	char	*ret;

	ret = malloc(s1_len + s2_len + 1);
	if (!ret)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(ret, s1, s1_len);
	ft_memcpy(ret + s1_len, s2, s2_len);
	ret[s1_len + s2_len] = 0;
	free(s1);
	return (ret);
}

static char	*read_line(int fd, char *rem, char *buf, size_t *buf_size)
{
	char	tmp_buf[BUFFER_SIZE + 1];
	ssize_t	size_read;

	while (1)
	{
		size_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(buf);
			rem[0] = 0;
			return (NULL);
		}
		if (size_read <= 0)
			break ;
		tmp_buf[size_read] = 0;
		buf = line_join(buf, *buf_size, tmp_buf, size_read);
		*buf_size += size_read;
		if (!buf || pos_newline(tmp_buf))
			break ;
	}
	return (buf);
}

static char	*dup_line(char *buffer, char *rem, size_t buf_len)
{
	char	*line;
	char	*line_break;
	size_t	line_length;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	line_break = pos_newline(buffer);
	line_length = line_break - buffer;
	if (!line_break)
		line_length = buf_len - 1;
	line = malloc(line_length + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, line_length + 1);
	line[line_length + 1] = 0;
	if (buf_len > (line_length + 1))
		ft_strlcpy(rem, buffer + line_length + 1, buf_len - line_length + 2);
	else
		rem[0] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	rem[BUFFER_SIZE + 1];
	char		*buf;
	size_t		buf_size;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf_size = ft_strlen(rem);
	if (buf_size > 0 && pos_newline(rem))
		return (dup_line(rem, rem, buf_size));
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	ft_memcpy(buf, rem, buf_size);
	buf[buf_size] = 0;
	buf = read_line(fd, rem, buf, &buf_size);
	line = dup_line(buf, rem, buf_size);
	free(buf);
	return (line);
}
