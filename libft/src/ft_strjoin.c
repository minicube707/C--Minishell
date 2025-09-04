/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:38:55 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 13:56:00 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	while (s1[i] != 0)
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != 0)
	{
		res[j] = s2[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}
