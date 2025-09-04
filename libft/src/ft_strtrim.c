/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:00:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 13:58:15 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*p;

	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]))
		start++;
	if (start > ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	p = malloc((end - start + 2) * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, &s1[start], end - start + 2);
	return (p);
}
