/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:49:09 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/28 15:26:33 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "get_next_line_bonus.h"

static void	truncation(char *stock, char *res, char *occ)
{
	int	len_occ;
	int	len_res;
	int	len_to_copy;

	len_res = ft_strlen(res);
	len_occ = ft_strlen(occ);
	len_to_copy = len_res - len_occ + 1;
	ft_strncpy(stock, occ + 1, ft_strlen(occ + 1));
	stock[ft_strlen(occ + 1)] = '\0';
	res[len_to_copy] = '\0';
}

static void	reset_stock(char *stock, char **res)
{
	int		len_sto;
	int		len_to_copy;
	char	*occ;
	char	*tmp;

	occ = ft_strchr(stock, '\n');
	if (occ == NULL)
	{
		tmp = ft_strjoin(*res, stock);
		free(*res);
		*res = tmp;
		stock[0] = '\0';
		return ;
	}
	len_sto = ft_strlen(stock);
	len_to_copy = len_sto - ft_strlen(occ) + 1;
	free(*res);
	*res = malloc(len_to_copy + 1);
	if (*res == NULL)
		return ;
	ft_strncpy(*res, stock, len_to_copy);
	(*res)[len_to_copy] = '\0';
	ft_strncpy(stock, occ + 1, ft_strlen(occ + 1));
	stock[ft_strlen(occ + 1)] = '\0';
}

char	*end_loop(char *res, char *buffer, char *stock, int *first_loop)
{
	char	*tmp;
	char	*occ;

	occ = ft_strchr(buffer, '\n');
	if (occ != NULL)
		truncation(stock, buffer, occ);
	tmp = ft_strjoin(res, buffer);
	free(buffer);
	if (tmp == NULL)
	{
		free(res);
		return (NULL);
	}
	free(res);
	res = tmp;
	*first_loop = 1;
	return (res);
}

char	*loop(t_shell *shell, t_two_int *two_int, t_struc var, int first_loop)
{
	char	*buffer;

	set_signal_kill(sigintheredoc);
	while (!ft_strchr(var.string1, '\n')
		&& shell->exit_code == 0 && var.string1 != NULL)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		two_int->int2 = read(two_int->int1, buffer, BUFFER_SIZE);
		shell->exit_code = g_status;
		if (two_int->int2 <= 0)
		{
			free(buffer);
			if (two_int->int2 == 0 && first_loop == 1)
				return (var.string1);
			free(var.string1);
			return (NULL);
		}
		buffer[two_int->int2] = '\0';
		var.string1 = end_loop(var.string1, buffer, var.string2, &first_loop);
		if (var.string1 == NULL)
			return (NULL);
	}
	return (var.string1);
}

char	*get_next_line(t_shell *shell, t_two_int *two_int)
{
	int			first_loop;
	static char	stock[1024][BUFFER_SIZE + 1];
	char		*res;
	t_struc		easter_egg;

	if (two_int->int1 < 0)
		return (NULL);
	first_loop = 0;
	res = malloc(1);
	if (res == NULL)
		return (NULL);
	ft_strncpy(res, "", 1);
	if (ft_strlen(stock[two_int->int1]) != 0)
	{
		reset_stock(stock[two_int->int1], &res);
		first_loop = 1;
	}
	easter_egg.string1 = res;
	easter_egg.string2 = stock[two_int->int1];
	res = loop(shell, two_int, easter_egg, first_loop);
	return (res);
}
