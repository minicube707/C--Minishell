/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:55:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/07 15:19:43 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *expand_dollard(t_shell *shell, char *string)
{
    char        *suffix;
    t_list_env  *noeud;
    
    noeud = shell->env;
    if (*string != '$')
        return (string);
    suffix = ft_substr(string, 1, ft_strlen(string)-1);
    if (suffix[0] == '?' && suffix[1] == '\0')
    {
       free(string);
       free(suffix);
       return(ft_strdup(ft_itoa(g_status))); 
    }
    while (noeud != NULL)
    {
        if (ft_strncmp(noeud->name, suffix, ft_strlen(suffix))== 0)
        {   
            free(string);
            free(suffix);
            return(ft_strdup(noeud->content));
        }
        noeud = noeud->next;
    }
    free(suffix);
    return (string);
}
