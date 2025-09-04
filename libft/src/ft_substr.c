/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:15:24 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 13:58:26 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		size;
	size_t		i;
	char		*p;
	size_t		min;

	i = 0;
	size = 0;
	min = len;
	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	if (size - start < len)
		min = size - start;
	p = malloc((min + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < min)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = 0;
	return (p);
}
