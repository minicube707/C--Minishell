/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_add_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:45:22 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/17 18:28:45 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  size_tab(t_shell **tab)
{
    int i;
    
    if (tab == NULL)
        return (0);
    i = 0;
    while (tab[i] != NULL)
        i++;
    return (i);
    
} 

void tab_add_shell(t_shell *shell, t_shell *subshell)
{
    t_shell **tab;
    int     size;
    int     i;
    
    size = size_tab(shell->tab_shell);
    tab = malloc((size + 2 ) * sizeof(t_shell *));
    if (tab == NULL)
    {
        print_error("Error Malloc");
        return ;
    }
    subshell->tab_shell = tab;
    tab[0] = shell;
    i = 1;
    while (i < size)
    {
       tab[i] = shell->tab_shell[i-1];
       i++;
    }
    tab[i] = NULL;
}
