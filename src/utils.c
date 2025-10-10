/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:42:26 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/07 16:05:36 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t oldsize)
{
	void	*nptr;
	size_t	cp_size;

	if (!ptr)
		return (ft_calloc(1, size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	nptr = ft_calloc(1, size);
	if (!nptr)
		return (NULL);
	if (oldsize < size)
		cp_size = oldsize;
	else
		cp_size = size;
	ft_memcpy(nptr, ptr, cp_size);
	free(ptr);
	return (nptr);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < nb)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
