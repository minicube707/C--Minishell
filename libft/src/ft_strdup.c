/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:28:26 by fmotte            #+#    #+#             */
/*   Updated: 2025/08/15 15:33:33 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*tab;
	int		len;

	len = ft_strlen(src);
	if (len == 0)
	{
		tab = malloc(sizeof(char));
		if (tab == NULL)
			return (NULL);
		tab[0] = 0;
		return (tab);
	}
	len++;
	tab = malloc(sizeof(char) * len);
	if (tab == NULL)
		return (NULL);
	ft_strncpy(tab, src, len);
	return (tab);
}
