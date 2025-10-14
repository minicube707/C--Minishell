/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:39:03 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/14 11:52:34 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(int op)
{
	if (op >= 0 && op <= 3)
		return (1);
	return (0);
}

int	is_operator(int op)
{
	if (op >= 4 && op <= 8)
		return (1);
	return (0);
}
