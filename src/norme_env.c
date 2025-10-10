/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:55:21 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/10 16:25:23 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*norme_env(char *env, int n)
{
	int	i;

	if (env == NULL)
		return (NULL);
	if (ft_isdigit(env[0]))
		return (NULL);
	i = 0;
	while (env[i] != '\0' && i < n)
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
			return (NULL);
		i++;
	}
	return (env);
}
