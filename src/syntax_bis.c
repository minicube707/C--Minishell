/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:03:42 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/27 21:28:10 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unclosed_quote(char *arg)
{
	free(arg);
	ft_putstr_fd("minishell: unclose quotes are not supported\n", 2);
	return (NULL);
}

int	count_max_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == str[0])
	{
		i++;
		if (i == 3)
			break ;
	}
	return (i);
}

int	err_multi_redir(char c, int i)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	while (i--)
	{
		write(2, &c, 1);
	}
	ft_putstr_fd("\'\n", 2);
	return (0);
}
