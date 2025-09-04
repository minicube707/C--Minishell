/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:26 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 13:58:00 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = NULL;
	while (s[i] != 0)
	{
		if (s[i] == (char) c)
			p = (char *) &s[i];
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (p);
}
