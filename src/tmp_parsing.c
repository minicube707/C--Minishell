/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_parsing->c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student->42->fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:49:18 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/10 16:58:09 by fmotte           ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list  *tmp_parsing(int argc, char **argv, char **envp)
{
    (void)argc;
	(void)argv;
	(void)envp;
    
    t_list          *head;
    t_file_info     **file_info;
    t_file_info     *element1;
    t_file_info     *element2;

    /*Creation de la strucuture*/
    head = malloc(sizeof(t_list));
    if (head == NULL)
        return (NULL);
    
    /*Creation du tableau*/
    file_info = malloc(2 * sizeof(t_file_info *));
    if (file_info == NULL)
        return (NULL);
    
    /*Creation de la premiere cellule*/
    element1 = malloc(sizeof(t_file_info));
    if ( element1 == NULL)
        return (NULL);

    element1->file_name = ft_strdup("out");
    element1->type = OUPUT;

    element2 = NULL;

    file_info[0] = element1;
    file_info[1] = element2;

    printf("Adress");
    printf("Adrress %p \n", file_info);
    printf("Adrress %p \n", file_info[0]->file_name);

    printf("\nRes\n");
    printf("File Name %s\n", file_info[0]->file_name);
    printf("Type %d\n", file_info[0]->type);

    head->pre_redir = 0;
    head->command = ft_strdup("ls");
    head->option = NULL;
    head->tab_file = file_info;
    head->subshell = NULL;
    head->next = NULL;
    head->previous = NULL;

    printf("\nRes\n");
    printf("Command %s\n", head->command);
    printf("File Name %s\n", head->tab_file[0]->file_name);
    printf("Type %d\n", head->tab_file[0]->type);
    return (head);
}