/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:56:07 by fmotte            #+#    #+#             */
/*   Updated: 2025/08/15 23:36:15 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_num(int n)
{
	long	i;
	int		len;

	i = 1;
	len = 0;
	if (n < 0)
		len = 1;
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		i *= 10;
		len++;
	}
	return (len);
}

static char	*int_to_char(int tmp, char *res, int index)
{
	long	i;

	i = 1;
	while (tmp / i > 0)
		i *= 10;
	if (tmp != 0)
		i /= 10;
	while (i > 0)
	{
		res[index] = ((tmp / i) % 10 + 48);
		index++;
		i /= 10;
	}
	res[index] = 0;
	return (res);
}

static int	negative(int tmp, int *is_negative)
{
	int	j;
	int	res;

	j = -1;
	res = tmp ^ j;
	*is_negative = 1;
	return (res + 1);
}

char	*ft_itoa(int n)
{
	unsigned int	tmp;
	int				is_negative;
	char			*res;
	int				index;
	int				len;

	index = 0;
	is_negative = 0;
	tmp = (unsigned int) n;
	if (n == -2147483648LL)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		tmp = negative(tmp, &is_negative);
	len = len_num(tmp) + is_negative;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	if (is_negative)
	{
		res[index] = '-';
		index++;
	}
	res = int_to_char(tmp, res, index);
	return (res);
}
