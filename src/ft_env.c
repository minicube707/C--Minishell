/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:23:21 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/10 16:32:00 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **environment)
{
	int	i;

	i = 0;
	while (environment[i] != NULL)
	{
		write(1, environment[i], ft_strlen(environment[i]));
		write(1, "\n", 1);
		i++;
	}
}
