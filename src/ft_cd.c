/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:05:40 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/09 13:48:14 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if directory doesn't exit
 //bash: cd: ewrerf5r: No such file or directory
//g_status = 1
    
//if directory is file  
//bash: cd: Makefile: Not a directory
//g_status = 1

//cd - use oldpwd

void    cd_only(t_shell *shell)
{
    char    *pwd;
    
    pwd = expand_dollard(shell, ft_strdup("$HOME"));
    if (ft_strncmp("$HOME", pwd, 5) == 0)
        print_error_env_not_set("cd", "HOME");
    else
        chdir2(pwd);
    if (pwd != NULL)
        free(pwd);
}

void    cd_else(char **tab_option,  char **pwd)
{   
    char	buff[1024];
    char    *cp_pwd;
    
    *pwd = getcwd(buff, 1024);
    if (*pwd == NULL)
        return ((void) print_error("Cannot get current working directory path\n")) ;
    cp_pwd = ft_strjoin(*pwd, "/");
    if (cp_pwd == NULL)
        return ((void) print_error("Error malloc\n"));
    *pwd = ft_strjoin(cp_pwd, tab_option[1]);
    free(cp_pwd);
}

int    cd_expand_home(t_shell *shell, char **tab_option, char **pwd)
{
    char    *target;
    int     i;
    
    i = 0;
    if (tab_option[1][0] == '$')
        target = ft_strdup(tab_option[1]);
    else
        target = ft_strdup("$HOME");
    if (target == NULL)
       return (print_error("Error malloc\n"));
    *pwd = expand_dollard(shell, ft_strdup(target));
    if (ft_strncmp(target, *pwd, ft_strlen(target)) == 0)
    {
        free(*pwd);
        *pwd = expand_dollard(shell, ft_strdup("$HOME"));
        if (ft_strncmp("$HOME", *pwd, 5) == 0)
        {
            print_error_env_not_set("cd", "HOME");
            free(*pwd);
            *pwd =  NULL;
            i = 1;
        }
    }
    free(target);
    return (i);
}

void    cd_minus(t_shell *shell, char **tab_option)
{
    char    *pwd;
    
    if (tab_option[1][1] != '\0')
    {
        print_error_invalide_option("cd", tab_option[1]);
        return ;
    }
    pwd = expand_dollard(shell, ft_strdup("$OLDPWD"));
    if (ft_strncmp("$OLDPWD", pwd, 7) == 0)
        print_error_env_not_set("cd", "OLDPWD");
    else
    {
        chdir2(pwd);
        printf("%s\n", pwd);
    }  
    if (pwd != NULL)
        free(pwd);
}

void    ft_cd(t_shell *shell, char **tab_option)
{
    char    *pwd;
    
    pwd = NULL;
    printf("CD \n");
    if (tab_option[1] != NULL && tab_option[2] != NULL)
    {
        print_error_to_much("cd");
        g_status = 1;
        return ;
    }
    if (tab_option[1] == NULL)
        return (cd_only(shell));
    else if (tab_option[1][0] == '-')
        return (cd_minus(shell, tab_option)); 
    else if (tab_option[1][0] == '$' || ft_strncmp(tab_option[1], "~", ft_strlen(tab_option[1])) == 0)
    {
        if (cd_expand_home(shell, tab_option, &pwd))
            return ;
    } 
    else if (tab_option[1][0] == '/')
        pwd = ft_strdup(tab_option[1]);
    else
        cd_else(tab_option, &pwd);
    if (pwd == NULL)
        return ((void) print_error("Error malloc\n"));
    
    printf("CHDIR %s \n", pwd);

    /*
    char    *expand;
    char    *string;
    char    *before;
    char    *after;
    char    *cp_pwd;
    
    string = ft_strchr(pwd, '$');
	before = ft_substr(pwd, 0, ft_strlen(pwd) - ft_strlen(string));         //Malloc
    after = ft_strdup(ft_strchr(string, '/'));                              //Malloc
    expand = ft_substr(string, 0, ft_strlen(string) - ft_strlen(after));    //Malloc
    expand = expand_dollard(shell, expand);
    
    
    printf("");
    printf("STRING %s \n", string);
    printf("BEFORE %s \n", before);
    printf("AFTER %s \n", after);
    printf("EXPAND %s \n", expand);
    
    cp_pwd = ft_strjoin(before, expand);
    free(pwd);
    pwd = ft_strjoin(cp_pwd, after);
    printf("PWD %s \n", pwd);
    */
   
    chdir2(pwd);
    free(pwd);
    
    //Expot PWD et OLDPWD
}
