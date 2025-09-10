/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/10 16:04:24 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_list *head, int subshell, t_channel *shell_channel)
{
	int	*exit_tabe;
	int	exit_code;

	(void)exit_tabe;
	(void)subshell;
	exit_code = 0;
	execute_here_doc(head);
	/*Put this loop in new function*/
	while (head != NULL && exit_code == 0)
	{
		/*Check the last exist code*/
		exit_code = execute_open_file(head, shell_channel);
		/*Check subshell*/
		/*Check Commande*/
		head = head->next;
	}
	/*Stocker le last exit dans un ficheir tmp*/
}
