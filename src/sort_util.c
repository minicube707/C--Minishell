/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 01:50:32 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/31 05:49:01 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sort(t_list_env **arr, int size, int i)
{
	t_shell	*shell;

	shell = get_shell(NULL);
	i = -1;
	while (++i < size && arr[i]->name)
	{
		if (arr[i]->content)
		{
			ft_putstr_fd("export ", shell->head->in_out[1]);
			ft_putstr_fd(arr[i]->name, shell->head->in_out[1]);
			ft_putstr_fd("=\"", shell->head->in_out[1]);
			ft_putstr_fd(arr[i]->content, shell->head->in_out[1]);
			ft_putstr_fd("\"\n", shell->head->in_out[1]);
		}
		else
		{
			ft_putstr_fd("export ", shell->head->in_out[1]);
			ft_putstr_fd(arr[i]->name, shell->head->in_out[1]);
			ft_putstr_fd("\n", shell->head->in_out[1]);
		}
	}
}
