/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkns.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:36:42 by lopoka            #+#    #+#             */
/*   Updated: 2024/07/28 11:27:03 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKNS_H
# define TKNS_H

//Tkns
void	ft_get_tokens(t_ms *ms, char *line);

//Tkns utils
int		ft_is_quote(char *c);
char	*ft_quote_end(char *line);
int		ft_is_whtspc(char *c);
char	*ft_skip_whtspc(char **str);
int		ft_is_opr(char *str);

//Tkns memory handling
void	ft_tkns_realloc(t_ms *ms);
void	ft_free_tkns(t_ms *ms);

#endif
