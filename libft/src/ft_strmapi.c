/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:24:59 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 13:56:52 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*res;

	if (s == NULL || f == NULL)
		return (NULL);
	res = malloc(((ft_strlen(s) + 1)) * sizeof(char));
	if (res == NULL)
		return (NULL);
	index = 0;
	while (s[index] != 0)
	{
		res[index] = s[index];
		index++;
	}
	res[index] = 0;
	index = 0;
	while (res[index] != 0)
	{
		res[index] = (*f)(index, res[index]);
		index++;
	}
	return (res);
}
