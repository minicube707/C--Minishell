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
    
    t_list          *head1;
    t_file_info     **file_info1;
    t_channel       *in_out1;
    char            **tab_option1;

    t_list          *head2;
    t_file_info     **file_info2;
    t_channel       *in_out2;
    char            **tab_option2;

    t_list          *head3;
    t_file_info     **file_info3;
    t_channel       *in_out3;
    char            **tab_option3;

    t_list          *head4;
    t_file_info     **file_info4;
    t_channel       *in_out4;
    char            **tab_option4;

    t_list          *head5;
    t_file_info     **file_info5;
    t_channel       *in_out5;
    char            **tab_option5;

    /*
    t_file_info     *element1;
    t_file_info     *element2;
    t_file_info     *element3;
    t_file_info     *element4;
    */
    t_file_info     *element5;

    /*
        PREMIER NOEUD
    */
    /*Creation de la strucuture*/
    head1 = malloc(sizeof(t_list));
    if (head1 == NULL)
        return (NULL);
    
    /*Creation du tableau*/
    file_info1 = malloc(1 * sizeof(t_file_info *));
    if (file_info1 == NULL)
        return (NULL);

    file_info1[0] = NULL;

    tab_option1 = malloc(3 * sizeof(char *));
    if ( tab_option1 == NULL)
        return (NULL);

    in_out1 = malloc(sizeof(t_channel));
    if ( in_out1 == NULL)
        return (NULL);

    tab_option1[0] = ft_strdup("/usr/bin/cat");
    tab_option1[1] = ft_strdup("doc/definition.txt");
    tab_option1[2] = NULL;

    head1->pre_redir = EMPTY;
    head1->command = ft_strdup("/usr/bin/cat");
    head1->option = tab_option1;
    head1->tab_file = file_info1;
    head1->subshell = NULL;
    head1->enviroment = envp;
    head1->in_out = in_out1;
    head1->next = NULL;
    head1->previous = NULL;


    /*
    DEUXIEME NOEUD
    */
    /*Creation de la strucuture*/
    head2 = malloc(sizeof(t_list));
    if (head2 == NULL)
        return (NULL);
    
    /*Creation du tableau*/
    file_info2 = malloc(1 * sizeof(t_file_info *));
    if (file_info2 == NULL)
        return (NULL);

    file_info2[0] = NULL;

    tab_option2 = malloc(4 * sizeof(char *));
    if ( tab_option2 == NULL)
        return (NULL);

    in_out2 = malloc(sizeof(t_channel));
    if ( in_out2 == NULL)
        return (NULL);


    tab_option2[0] = ft_strdup("/usr/bin/tr");
    tab_option2[1] = ft_strdup("' '");
    tab_option2[2] = ft_strdup("'\n'");
    tab_option2[3] = NULL;

    head2->pre_redir = PIPE;
    head2->command = ft_strdup("/usr/bin/tr");
    head2->option = tab_option2;
    head2->tab_file = file_info2;
    head2->subshell = NULL;
    head2->enviroment = envp;
    head2->in_out = in_out2;
    head2->next = NULL;
    head2->previous = head1;

    head1->next = head2;

    /*
    TROISIME NOEUD
    */
    /*Creation de la strucuture*/
    head3 = malloc(sizeof(t_list));
    if (head3 == NULL)
        return (NULL);
    
    /*Creation du tableau*/
    file_info3 = malloc(1 * sizeof(t_file_info *));
    if (file_info3 == NULL)
        return (NULL);

    file_info3[0] = NULL;

    tab_option3 = malloc(2 * sizeof(char *));
    if ( tab_option3 == NULL)
        return (NULL);

    in_out3 = malloc(sizeof(t_channel));
    if ( in_out3 == NULL)
        return (NULL);


    tab_option3[0] = ft_strdup("/usr/bin/sort");
    tab_option3[1] = NULL;

    head3->pre_redir = PIPE;
    head3->command = ft_strdup("/usr/bin/sort");
    head3->option = tab_option3;
    head3->tab_file = file_info3;
    head3->subshell = NULL;
    head3->enviroment = envp;
    head3->in_out = in_out3;
    head3->next = NULL;
    head3->previous = head2;

    head2->next = head3;


    /*
    Quatrieme NOEUD
    */
    /*Creation de la strucuture*/
    head4 = malloc(sizeof(t_list));
    if (head4 == NULL)
        return (NULL);
    
    /*Creation du tableau*/
    file_info4 = malloc(1 * sizeof(t_file_info *));
    if (file_info4 == NULL)
        return (NULL);

    file_info4[0] = NULL;

    tab_option4 = malloc(3 * sizeof(char *));
    if ( tab_option4 == NULL)
        return (NULL);

    in_out4 = malloc(sizeof(t_channel));
    if ( in_out4 == NULL)
        return (NULL);


    tab_option4[0] = ft_strdup("/usr/bin/uniq");
    tab_option4[1] = ft_strdup("-c");
    tab_option4[2] = NULL;

    head4->pre_redir = PIPE;
    head4->command = ft_strdup("/usr/bin/uniq");
    head4->option = tab_option4;
    head4->tab_file = file_info4;
    head4->subshell = NULL;
    head4->enviroment = envp;
    head4->in_out = in_out4;
    head4->next = NULL;
    head4->previous = head3;

    head3->next = head4;

    /*
    Cinquieme NOEUD
    */
    /*Creation de la strucuture*/
    head5 = malloc(sizeof(t_list));
    if (head5 == NULL)
        return (NULL);
    
    /*Creation du tableau*/
    file_info5 = malloc(2 * sizeof(t_file_info *));
    if (file_info5 == NULL)
        return (NULL);

    element5 = malloc(sizeof(t_file_info));
    if ( element5 == NULL)
        return (NULL);

    element5->file_name = ft_strdup("outfile");
    element5->type = APPEND;

    file_info5[0] = element5;
    file_info5[1] = NULL;

    tab_option5 = malloc(3 * sizeof(char *));
    if ( tab_option5 == NULL)
        return (NULL);

    in_out5 = malloc(sizeof(t_channel));
    if ( in_out5 == NULL)
        return (NULL);


    tab_option5[0] = ft_strdup("/usr/bin/sort");
    tab_option5[1] = ft_strdup("-nr");
    tab_option5[2] = NULL;

    head5->pre_redir = PIPE;
    head5->command = ft_strdup("/usr/bin/sort");
    head5->option = tab_option5;
    head5->tab_file = file_info5;
    head5->subshell = NULL;
    head5->enviroment = envp;
    head5->in_out = in_out5;
    head5->next = NULL;
    head5->previous = head4;

    head4->next = head5;

    printf("\nRes\n");
    printf("Head1\n");
    printf("Adrress %p \n", head1);
    printf("Command %s\n", head1->command);
    printf("Previous redirection %d\n", head1->pre_redir);
    printf("Previous noeud %p\n", head1->previous);
    printf("Next noeud %p\n", head1->next);

    printf("\nRes\n");
    printf("head2\n");
    printf("Adrress %p \n", head2);
    printf("Command %s\n", head2->command);
    printf("Previous redirection %d\n", head2->pre_redir);
    printf("Previous noeud %p\n", head2->previous);
    printf("Next noeud %p\n", head2->next);

    printf("\nRes\n");
    printf("head3\n");
    printf("Adrress %p \n", head3);
    printf("Command %s\n", head3->command);
    printf("Previous redirection %d\n", head3->pre_redir);
    printf("Previous noeud %p\n", head3->previous);
    printf("Next noeud %p\n", head3->next);

    printf("\nRes\n");
    printf("head4\n");
    printf("Adrress %p \n", head4);
    printf("Command %s\n", head4->command);
    printf("Previous redirection %d\n", head4->pre_redir);
    printf("Previous noeud %p\n", head4->previous);
    printf("Next noeud %p\n", head4->next);

    printf("\nRes\n");
    printf("head5\n");
    printf("Adrress %p \n", head5);
    printf("Command %s\n", head5->command);
    printf("Previous redirection %d\n", head5->pre_redir);
    printf("Previous noeud %p\n", head5->previous);
    printf("Next noeud %p\n", head5->next);
    printf("\n");
    return (head1);
}