/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:45:15 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/30 17:33:29 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*dlist_pop_front(t_list *pop_head)
{
	t_list	*new_head;

	if (pop_head == NULL)
		return (NULL);
	printf("POP %p \n", pop_head);	
	new_head = pop_head->next;
	printf("NEW %p \n", new_head);	

	printf("ADRESS OPT %p \n", pop_head->option);
	printf("ADRESS TAB %p \n", pop_head->tab_file);
	
	tab_char_clear(pop_head->option);
	tab_info_clear(pop_head->tab_file);
	
	if (pop_head->mypipe[0] > 2)
		close(pop_head->mypipe[0]);
	if (pop_head->mypipe[0] > 2)
		close(pop_head->mypipe[1]);
		
	//free(pop_head->subshell);
	pop_head->subshell = NULL;
	pop_head->next = NULL;
	pop_head->previous = NULL;
	
	free(pop_head);
	pop_head = NULL;
	if (new_head != NULL)
		new_head->previous = NULL;
	return (new_head);
}

t_list	*dlist_clear(t_list *dlist)
{
	t_list *head;
	head = dlist_get_top(dlist);
	while (head != NULL)
		head = dlist_pop_front(head);
	return (NULL);
}
