/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/13 15:25:15 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_list *head, int subshell, t_channel *shell_channel)
{
	t_channel 	in_out;
	int			exit_code;

	(void)subshell;
	exit_code = 0;

	execute_here_doc(head);
	
	/*Put this loop in new function*/
	while (head != NULL && exit_code == 0)
	{	
		/*S'il n'y a pas de precedant nous somme dans le premier neoud*/
		if (head->previous == NULL)
			in_out.in = shell_channel->in;
		else
			in_out.in = head->previous->mypipe[0];
			
		/*S'il n'y a pas de suivant nous somme dans le dernier neoud*/
		if (head->next == NULL)
			in_out.out = shell_channel->out;
		else
			in_out.out = head->mypipe[1];
			
		/*Check the last exist code*/
		exit_code = execute_open_file(head, &in_out);
		if (exit_code)
		{
			//Close all
			//Stock exit code
			return;
		}
		
		/*Save the input ouput in the strucuture*/
		head->in_out = &in_out;
		
		/*
		if (head->subshell != NULL)
			Check subshell
		*/
			
		
		exit_code = execute_command(head);
		if (exit_code)
		{
			//Close all
			//Stock exit code
			return;
		}
		head = head->next;
	}
	/*Stocker le last exit dans un ficheir tmp*/
}
