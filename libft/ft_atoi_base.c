/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:32:30 by atorma            #+#    #+#             */
/*   Updated: 2024/06/19 14:32:32 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	get_distance(char c, char *base_table)
{
	char	*b;

	b = base_table;
	while (*b && *b != c)
		b++;
	return (b - base_table);
}

static int	ft_base_convert(char *str, int radix, char *base_table)
{
	int		ret;
	int		m_count;

	ret = 0;
	m_count = 0;
	while (is_whitespace(*str))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m_count++;
		str++;
	}
	while (*str >= base_table[0] && *str <= base_table[radix - 1])
	{
		ret = ret * radix + get_distance(*str, base_table);
		str++;
	}
	if (m_count % 2)
		ret = -(ret);
	return (ret);
}

static int	find_base(char *base)
{
	char	*b;
	char	*tmp;

	b = base;
	if (*b == 0 || *(b + 1) == 0)
		return (0);
	while (*b)
	{
		tmp = b + 1;
		if (*b <= 32 || *b > 126)
			return (0);
		if (*b == '-' || *b == '+')
			return (0);
		while (*tmp)
		{
			if (*tmp == *b)
				return (0);
			tmp++;
		}
		b++;
	}
	return (b - base);
}

int	ft_atoi_base(char *str, char *base)
{
	int		radix;

	radix = find_base(base);
	if (radix <= 0)
		return (0);
	return (ft_base_convert(str, radix, base));
}
