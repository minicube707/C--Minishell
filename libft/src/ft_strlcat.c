/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:48:08 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 13:56:18 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = 0;
	len_src = 0;
	while (dst[len_dst] != 0 && len_dst < size)
		len_dst++;
	while (src[len_src] != 0)
		len_src++;
	if (len_dst >= size)
		return (size + len_src);
	while ((len_dst + i + 1 < size) && src[i] != 0)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	if (len_dst + i < size)
		dst[len_dst + i] = 0;
	return (len_dst + len_src);
}
