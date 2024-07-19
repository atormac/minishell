/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:47:24 by atorma            #+#    #+#             */
/*   Updated: 2024/07/19 12:41:42 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static void	format_print(struct t_write_state *ws, va_list ap, const char *f)
{
	if (*f == 'c')
		print_char(ws, va_arg(ap, int));
	else if (*f == '%')
		print_char(ws, '%');
	else if (*f == 's')
		print_string(ws, va_arg(ap, char *));
	else if (*f == 'd' || *f == 'i')
		print_integer(ws, va_arg(ap, int));
	else if (*f == 'u')
		print_unsigned(ws, va_arg(ap, unsigned int));
	else if (*f == 'x')
		hex_uint(ws, va_arg(ap, unsigned int), 1);
	else if (*f == 'X')
		hex_uint(ws, va_arg(ap, unsigned int), 0);
	else if (*f == 'p')
		print_ptr(ws, va_arg(ap, unsigned long long));
}

int	ft_printf(const char *f, ...)
{
	va_list					ap;
	struct t_write_state	ws;

	ws.fd = 1;
	ws.bytes_written = 0;
	ws.ret_val = 0;
	va_start(ap, f);
	while (*f)
	{
		if (*f == '%' && ft_strchr("cspdiuxX%", *(f + 1)))
		{
			f++;
			format_print(&ws, ap, f);
		}
		else
			ft_write(&ws, (char *)f, 1);
		if (ws.ret_val == -1)
			break ;
		f++;
	}
	va_end(ap);
	if (ws.ret_val == -1)
		return (-1);
	return (ws.bytes_written);
}

int	ft_printf_fd(int fd, const char *f, ...)
{
	va_list					ap;
	struct t_write_state	ws;

	ws.fd = fd;
	ws.bytes_written = 0;
	ws.ret_val = 0;
	va_start(ap, f);
	while (*f)
	{
		if (*f == '%' && ft_strchr("cspdiuxX%", *(f + 1)))
		{
			f++;
			format_print(&ws, ap, f);
		}
		else
			ft_write(&ws, (char *)f, 1);
		if (ws.ret_val == -1)
			break ;
		f++;
	}
	va_end(ap);
	if (ws.ret_val == -1)
		return (-1);
	return (ws.bytes_written);
}
