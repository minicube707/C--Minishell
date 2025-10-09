/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:00:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/09 10:15:20 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_getenv(t_shell *shell, char *name)
{
    t_list_env *tmp;

    tmp = shell->env;
    while(tmp != NULL)
    {
        if (ft_strncmp(tmp->name, name, ft_strlen(name))== 0)
            return(tmp->content);
        tmp = tmp->next;
    }
    return (NULL);
}

char    *ft_join_env(char *name, char *content)
{
    char    *res;
    char    *tmp;
    tmp = ft_strjoin(name, "=");
    res = ft_strjoin(tmp, content);
    free(tmp);
    free(name);
    free(content);
    return (res);
}
