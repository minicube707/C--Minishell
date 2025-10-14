/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 02:26:42 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/14 11:47:20 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_op(int op, int fd)
{
	if (op == 0)
		ft_putstr_fd("<", fd);
	else if (op == 1)
		ft_putstr_fd(">", fd);
	else if (op == 2)
		ft_putstr_fd("<<", fd);
	else if (op == 3)
		ft_putstr_fd(">>", fd);
	else if (op == 5)
		ft_putstr_fd("|", fd);
	else if (op == 6)
		ft_putstr_fd("&&", fd);
	else if (op == 7)
		ft_putstr_fd("||", fd);
	else if (op == 8)
		ft_putstr_fd(";", fd);
}

int	error_token(int	op)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (op != -1)
		print_op(op, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("\'\n", 2);
	return (0);
}
