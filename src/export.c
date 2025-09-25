/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:51:49 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/25 18:38:50 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	name_is_valid(char *arg)
{
	if (!ft_isalpha(*arg) || *arg == '_')
		return (1);
	arg++;
	while (*arg || *arg != '=')
	{
		if (!ft_isalnum(*arg))
			return (1);
		arg++;
	}
	return (0);
}

static int	error_id(char *arg)
{
	ft_putstr_fd("minishell: export '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("' is not a valid identifier\n", 2);
	return (1);
}

static void	set_new_env(t_list_env *new, char *arg)
{
	size_t	l;

	l = strlenc(arg, '=');
	new->name = ft_substr(arg, 0, l);
	if (arg[l] == '=')
		l++;
	new->content = ft_strdup(&arg[l]);
	new->next = NULL;
}

int	ft_export(t_shell *shell, char **arg)
{
	t_list_env  *list;

    if (!arg)
		return (0);
	arg++;
	while (*arg)
	{
		list = shell->env;
		if (!name_is_valid(*arg))
			return (error_id(*arg));
		while (list->next)
			list = list->next;
		list->next = malloc(sizeof(t_list_env));
		set_new_env(list->next, *arg);
		arg++;
	}
	shell->environment = make_env(shell, shell->env);
	return (0);
}
