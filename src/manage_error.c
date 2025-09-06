/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:34:24 by florent           #+#    #+#             */
/*   Updated: 2025/09/06 14:09:56 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *string)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd("\n", 2);
}

void	print_error_unknow_cmd(char *string)
{
	ft_putstr_fd("error: command doesn't exist: ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd("\n", 2);
}