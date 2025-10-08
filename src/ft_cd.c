/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:05:40 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/08 18:28:04 by fmotte           ###   ########.fr       */
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
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void    chdir2(char *pwd)
{
    if (chdir(pwd))
    {
        if (errno == EACCES)
            print_error_access_denied("cd", pwd);
        if (errno == ENOTDIR)
            print_error_not_directory("cd", pwd);
        if (errno == ENOENT)
            print_error_file("cd", pwd);
    }
}
void    ft_cd(t_shell *shell, char **tab_option)
{
    char    *pwd;
    char    *cp_pwd;
    //char    **tab_pwd;
    char	buff[1024];
    
    //copier l'ancien PWD
    
    printf("CD \n");
    if (tab_option[1] != NULL && tab_option[2] != NULL)
    {
        print_error_to_much("cd");
        g_status = 1;
        return ;
    }

    // NULL
    if (tab_option[1] == NULL)
    {
        pwd = expand_dollard(shell, ft_strdup("$HOME"));
        if (ft_strncmp("$HOME", pwd, 5) == 0)
            print_error_env_not_set("cd", "HOME");
        else
        chdir2(pwd);
        free(pwd);
        return ;
    }

    //-
    if (tab_option[1][0] == '-')
    {
        if (tab_option[1][1] != '\0')
        {
            //bash: cd: tab_option[1]: invalid option
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
        free(pwd);
        return ;
    }
    
    //~
    if (ft_strncmp(tab_option[1], "~", ft_strlen(tab_option[1])) == 0)
    {
        pwd = expand_dollard(shell, ft_strdup("$HOME"));
        if (ft_strncmp("$HOME", pwd, 5) == 0)
        {
            print_error_env_not_set("cd", "HOME");
            free(pwd);
            return ;
        }
    }
    //$
    else if (tab_option[1][0] == '$')
    {
        pwd = expand_dollard(shell, ft_strdup(tab_option[1]));
        printf("EXPAND %s \n", pwd);
        if (ft_strncmp(tab_option[1], pwd, ft_strlen(tab_option[1])) == 0)
        {
            printf("NOT FOUND \n");
            pwd = expand_dollard(shell, ft_strdup("$HOME"));
            if (ft_strncmp("$HOME", pwd, 4) == 0)
            {
                print_error_env_not_set("cd", "HOME");
                free(pwd);
                return ;
            }
        }
    }
    // /
    else if (tab_option[1][0] == '/')
        pwd = ft_strdup(tab_option[1]);
    // else
    else
    {
        pwd = getcwd(buff, 1024);
        if (pwd == NULL)
	    {
		    print_error("Cannot get current working directory path\n");
		    return ;
	    }
        cp_pwd = ft_strjoin(pwd, "/");
        pwd = ft_strjoin(cp_pwd, tab_option[1]);
        free(cp_pwd);
    }

    
    char    *expand;
    char    *string;
    char    *before;
    char    *after;
    
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
    
    chdir2(pwd);
    free(pwd);

    
    //Expot PWD et OLDPWD
}
