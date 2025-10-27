/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 01:50:32 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/27 02:04:53 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sort(t_list_env **arr, int size, int i)
{
	i = -1;
	while (++i < size)
	{
		if (arr[i]->content)
			printf("export %s=\"%s\"\n", arr[i]->name, arr[i]->content);
		else
			printf("export %s\n", arr[i]->name);
	}
}
