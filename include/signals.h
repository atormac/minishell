/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:53:03 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/19 12:54:46 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SIGNALS_H
# define SIGNALS_H

enum
{
	SIGNALS_PARENT,
	SIGNALS_HEREDOC,
	SIGNALS_DEFAULT
};
int		set_signals(t_ms *ms, int type);

#endif
