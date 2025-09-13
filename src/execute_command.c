/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:38:39 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/13 16:34:32 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_pipe(t_list *head)
{
	int	exit_code;
	
	exit_code = 0;
		
	/*Dup input*/
	if (head->in_out->in != 0)
	{
		dup2(head->in_out->in, STDIN_FILENO);
		close(head->in_out->in);	
	}
	
	/*Dup output*/
	if (head->in_out->out != 1)
	{
		dup2(head->in_out->out, STDOUT_FILENO);
		close(head->in_out->out);
	}
		
	//Close all pipe
	
	//Creat function to join option to path command
	//Insert command in pos 0heqd-> option
	exit_code = execve(head->command, head->option, head->enviroment);
	print_error_unknow_cmd(head->command);
	return (exit_code);
}

int	single_command(t_list *head, pid_t *ptr_pid)
{
	pid_t	pid;
	int 	exit_code;
	
	exit_code = 0;
	pid = fork();
	if (pid == 0)
	{
		exit_code = manage_pipe(head);
		return (exit_code);
	}
	//Close prevouse pipe
	*ptr_pid = pid;
	return (exit_code);
}

int	multiple_command(t_list *head, pid_t *ptr_pid)
{
	pid_t	pid;
	int 	exit_code;
	
	exit_code = 0;
	exit_code = pipe(head->mypipe);
	if (exit_code != 0)
	{
		print_error("failure creation of pipe");
		return (exit_code);
	}
	pid = fork();
	if (pid == 0)
	{
		exit_code = manage_pipe(head);
		return (exit_code);
	}
	//Close prevouse pipe
	*ptr_pid = pid;
	return (exit_code);
}

int execute_command(t_list *head)
{
	int 			exit_code;
	pid_t			pid;
	
	printf("IN %d \n", head->in_out->in);
	printf("OUT %d \n", head->in_out->out);
	
	exit_code = 0;
	if (head->previous == NULL && head->next == NULL)
		exit_code = single_command(head, &pid);
	else
		exit_code = multiple_command(head, &pid);
	waitpid(pid, NULL, 0);
	return (exit_code);
}
