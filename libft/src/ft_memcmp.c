/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:10:15 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 13:52:12 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (n == 0)
		return (0);
	i = 0;
	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	while (p1[i] == p2[i] && i < n - 1)
		i++;
	return (p1[i] - p2[i]);
}
