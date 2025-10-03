/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:27:57 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/03 14:05:24 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_built_in(char *command)
{
    int     i;
    char    *tab_buit_in[7];

    tab_buit_in[0] = "echo";
    tab_buit_in[1] = "cd";
    tab_buit_in[2] = "pwd";
    tab_buit_in[3] = "export";
    tab_buit_in[4] = "unset";
    tab_buit_in[5] = "env";
    tab_buit_in[6] = "exit";

    i = 0;
    while (i < 7)
    {
        if (ft_strncmp(tab_buit_in[i], command, ft_strlen(command)) == 0)
            return (1);
        i++;
    }
    return (0);
}

void    ft_echo(char **tab_option)
{
    int     add_back_slash;
    int     i;
    
    add_back_slash = 1;
    printf("MY ECHO\n");
    
    /*Do a functionn to pass -n*/
    if (ft_strncmp(tab_option[1], "-n", ft_strlen(tab_option[1])) == 0)
        add_back_slash = 0;
    else
        write(1, tab_option[1], ft_strlen(tab_option[1]));
    i = 2;
    while (tab_option[i] != NULL)
    {
        write(1, tab_option[i], ft_strlen(tab_option[i]));
        i++;
    }
    if (add_back_slash)
        write(1, "\n", 1);
}

void    ft_pwd(t_shell *shell)
{
    t_list_env *tmp;
    char        buff[1024];
    
    tmp = shell->env;
    printf("MY PWD\n");
    while(ft_strncmp(tmp->name, "PWD", ft_strlen(tmp->name)))
        tmp = tmp->next;
    if (ft_strncmp(tmp->name, "PWD", ft_strlen(tmp->name)) == 0)
    {
        write(1, tmp->content, ft_strlen(tmp->content));
        write(1, "\n", 1);
        return;
    }
    if (getcwd(buff, 1024 ) == NULL)
    {
        print_error("Cannot get current working directory path\n");
        return;
    }
    write(1, buff, 1024);
    write(1, "\n", 1);
}
