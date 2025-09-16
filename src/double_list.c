/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:45:15 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/16 18:28:28 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Insert*/

t_list *dlist_pop_front(t_list *head)
{
    t_list *new_head;
    t_list *pop_head;

    if (head == NULL)
        return (NULL);
    pop_head = dlist_get_top(head);
    new_head = pop_head->next;
    printf("POP %p \n", pop_head);
    
    /*If last noeud free list environement*/
    
    /*Free commande*/
    free(pop_head->command);
    pop_head->command = NULL;

    /*Free option*/
    tab_char_clear(pop_head->option);
    
    /*Free tab of fd*/
    tab_info_clear(pop_head->tab_file);
    
    /*Free struct in_out*/
    free(pop_head->in_out);
    pop_head->in_out = NULL;
    
    /*Free struct subshell*/
    free(pop_head->subshell);
    pop_head->subshell = NULL;
    
    pop_head->next = NULL;
    pop_head->previous = NULL;
    free(pop_head);
    pop_head = NULL;
    if (new_head != NULL)
        new_head->previous = NULL;
    
    return(new_head);
}

t_list *dlist_clear(t_list *head)
{
    while(head != NULL)  
        head = dlist_pop_front(head);
        
    return (NULL);
}
