/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:29:45 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/03 14:03:38 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	res;
	int	signe;

	res = 0;
	signe = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
	{
		signe = -1;
		str++;
	}
	else if (*str == 43)
		str++;
	while (48 <= *str && *str <= 57)
	{
		res *= 10;
		res += (*str - 48);
		str++;
	}
	res *= signe;
	return (res);
}
