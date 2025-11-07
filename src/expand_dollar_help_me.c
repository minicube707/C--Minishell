/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_help_me.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:09:00 by florent           #+#    #+#             */
/*   Updated: 2025/11/07 23:12:33 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_path_wildcard_i_want_to_die(char *tmpsq, char *tmpdq)
{
	int		lens;
	int		lend;

	lend = 0;
	lens = 0;
	if (tmpsq != NULL)
		lens = ft_strlen(ft_strrchr(tmpsq, '\''));
	if (tmpdq != NULL)
		lend = ft_strlen(ft_strrchr(tmpdq, '"'));
	if (ft_strlen(tmpsq) == lens && ft_strlen(tmpdq) == lend)
		return (1);
	return (0);
}
