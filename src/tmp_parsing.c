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
    
    t_list          *head;
    t_file_info     **file_info;
    t_file_info     *element1;
    t_file_info     *element2;
    t_file_info     *element3;
    t_file_info     *element4;
    t_file_info     *element5;

    /*Creation de la strucuture*/
    head = malloc(sizeof(t_list));
    if (head == NULL)
        return (NULL);
    
    /*Creation du tableau*/
    file_info = malloc(5 * sizeof(t_file_info *));
    if (file_info == NULL)
        return (NULL);
    
    /*Creation de la premiere cellule*/
    
    element1 = malloc(sizeof(t_file_info));
    if ( element1 == NULL)
        return (NULL);

    element2 = malloc(sizeof(t_file_info));
    if ( element2 == NULL)
        return (NULL);

    element3 = malloc(sizeof(t_file_info));
    if ( element3 == NULL)
        return (NULL);

    element4 = malloc(sizeof(t_file_info));
    if ( element4 == NULL)
        return (NULL);
        
    element1->file_name = ft_strdup("outfile");
    element1->type = OUPUT;

    element2->file_name = ft_strdup("infile");
    element2->type = INPUT;

    element3->file_name = ft_strdup("out");
    element3->type = APPEND;
    
    element4->file_name = ft_strdup("stop");
    element4->type = HERE_DOC;

    element5 = NULL;
    
    file_info[0] = element1;
    file_info[1] = element2;
    file_info[2] = element3;
    file_info[3] = element4;
    file_info[4] = element5;

    printf("Adress\n");
    printf("Adrress %p \n", file_info);
    printf("Adrress %p \n", file_info[0]);

    
    printf("\nRes\n");
    printf("File Name %s\n", file_info[0]->file_name);
    printf("Type %d\n", file_info[0]->type);
    printf("File Name %s\n", file_info[1]->file_name);
    printf("Type %d\n", file_info[1]->type);
    printf("File Name %s\n", file_info[2]->file_name);
    printf("Type %d\n", file_info[2]->type);
    printf("File Name %s\n", file_info[3]->file_name);
    printf("Type %d\n", file_info[3]->type);

    //file_info[0] = NULL;

    char    **tab_option;
    tab_option = malloc(3 * sizeof(char *));
    if ( tab_option == NULL)
        return (NULL);

    tab_option[0] = ft_strdup("/bin/cat");
    tab_option[1] = ft_strdup("-e");
    tab_option[2] = NULL;

    head->pre_redir = 0;
    head->command = ft_strdup("/bin/cat");
    head->option = tab_option;
    head->tab_file = file_info;
    head->subshell = NULL;
    head->enviroment = envp;
    head->mypipe[0] = -1;
    head->mypipe[1] = -1;
    head->next = NULL;
    head->previous = NULL;

    
    printf("\nRes\n");
    printf("Command %s\n", head->command);
    printf("File Name %s\n", head->tab_file[0]->file_name);
    printf("Type %d\n", head->tab_file[0]->type);
    printf("File Name %s\n", head->tab_file[1]->file_name);
    printf("Type %d\n", head->tab_file[1]->type);
    printf("File Name %s\n", head->tab_file[2]->file_name);
    printf("Type %d\n", head->tab_file[2]->type);
    printf("File Name %s\n", head->tab_file[3]->file_name);
    printf("Type %d\n", head->tab_file[3]->type);
    return (head);
}