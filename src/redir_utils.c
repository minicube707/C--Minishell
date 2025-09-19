/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:02:45 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/17 17:21:49 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file_info	*new_redir(int type, char *filename)
{
	t_file_info	*new;

	new = malloc(sizeof(t_file_info));
	if (!new)
		return (NULL);
	new->type = type;
	new->file_name = filename;
	return (new);
}
