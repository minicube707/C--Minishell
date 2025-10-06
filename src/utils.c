/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:42:26 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/06 10:15:22 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t oldsize)
{
	void	*nptr;
	size_t	cp_size;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(size);
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
