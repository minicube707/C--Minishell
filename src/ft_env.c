/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:23:21 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/15 18:41:59 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **environment)
{
	int	i;

	//Check argument
	//IF env env .... execute
	
	i = 0;
	while (environment[i] != NULL)
	{
		write(1, environment[i], ft_strlen(environment[i]));
		write(1, "\n", 1);
		i++;
	}
}
