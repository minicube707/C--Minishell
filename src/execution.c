/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/13 13:39:51 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_list *head, int subshell, t_channel *shell_channel)
{
	t_channel 	in_out;
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
		exit_code = execute_open_file(head, &in_out);
		
		/*S'il n'y a pas de precedant nous somme dans le premier neoud*/
		if (head->previous == NULL)
			shell_channel->in = in_out.in;

		/*S'il n'y a pas de suivant nous somme dans le dernier neoud*/
		if (head->next == NULL)
			shell_channel->out = in_out.out;
			
		/*Check subshell*/
		/*Check Commande*/
		head = head->next;
	}
	/*Stocker le last exit dans un ficheir tmp*/
}
