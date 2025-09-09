/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/09/09 18:22:49 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execution(t_list *head, int subshell, t_channel shell_channel)
{
    (void)head;

    t_list *tmphead;
    int     *exit_tabe;

    /*Creation de la pseudo structure*/
    tmphead->pre_redir = 0;
    tmphead->command = "ls";
    tmphead->option = NULL;
    tmphead->tab_file = NULL;
    tmphead->subshell = NULL;
    tmphead->next = NULL;
    tmphead->previous = NULL;

    execute_here_doc(&tmphead);

    while (tmphead!= NULL)
    {
        /*Check the last exist code*/

        /*Open the file + do redirection*/

        /*Check subshell*/

        /*Check Commande*/

        tmphead = tmphead->next;
    }
    /*Stocker le last exit dans un ficheir tmp*/
}

