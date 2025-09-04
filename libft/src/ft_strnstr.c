/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:00:46 by fmotte            #+#    #+#             */
/*   Updated: 2025/08/16 13:46:41 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	unsigned long	i;
	int				j;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] != 0)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len && little[j] != 0)
			j++;
		if (little[j] == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
