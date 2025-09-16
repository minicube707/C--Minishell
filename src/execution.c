/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/15 18:08:29 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_list *head, int subshell, t_channel *shell_channel)
{
	int			exit_code;

	(void)subshell;
	(void)shell_channel;
	exit_code = 0;

	execute_here_doc(head);
	
	/*Put this loop in new function*/
	while (head != NULL && exit_code == 0)
	{	
		exit_code = pipe(head->mypipe);
		if (exit_code != 0)
		{
			print_error("failure creation of pipe");
			//Close all
			//Stock exit code
			return ;
		}
		
		/*SET dans parsing*/
		head->in_out->in = 0;
		head->in_out->out = 1;
		
		if (head->next != NULL)
		{
			head->in_out->in = head->mypipe[0];
			head->in_out->out = head->mypipe[1];	
		}
		
		/*S'il n'y a pas de precedant nous ne somme pas dans le premier neoud*/
		if (head->previous != NULL)
			head->in_out->in = head->previous->mypipe[0];
			
			
		/*Check the last exist code*/
		exit_code = execute_open_file(head);
		if (exit_code)
		{
			//Close all
			//Stock exit code
			return;
		}
		
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
