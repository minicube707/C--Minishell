/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:52 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/16 18:10:48 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *dlist_get_top(t_list *head)
{
    t_list *tmp_list;
    
    tmp_list = head;
    if (tmp_list== NULL)
        return (NULL);
    while (tmp_list->previous != NULL)
        tmp_list = tmp_list->previous;
    return (tmp_list);
}
