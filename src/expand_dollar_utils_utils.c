/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:03:30 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/24 15:30:29 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_path_all(t_shell *shell, char *change)
{
	int i;
    char    *string;
    
    i = 1;
    while (shell->head->option[i] != NULL)
    {
        printf("Expand %s \n", shell->head->option[i]);
        string = expand_path(shell, shell->head->option[i], change);
        if (string == NULL)
        {
            tab_char_clear(shell->head->option);
            return ;
        }
        else
            shell->head->option[i] = string;
        i++;
    }
}
