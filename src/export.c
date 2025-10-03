/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:51:49 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/03 17:58:56 by fmotte           ###   ########.fr       */
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

static void	sort_list(t_list_env **arr, int size)
{
	t_list_env	*tmp;
	int			i;
	int			j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j]->name, arr[j + 1]->name) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		printf("export %s=%s\n", arr[i]->name, arr[i]->content);
		i++;
	}
	free(arr);
}

int	ft_export(t_shell *shell, char **arg)
{
	t_list_env	*curr;
	int			size;

	if (!arg[1])
	{
		size = size_t_list_env(shell->env);
		sort_list(set_export_list(shell->env, size), size);
		return (0);
	}
	arg++;
	while (*arg)
	{
		curr = shell->env;
		if (!name_is_valid(*arg))
			return (error_id(*arg));
		while (curr->next)
			curr = curr->next;
		curr->next = malloc(sizeof(t_list_env));
		set_new_env(curr->next, *arg);
		arg++;
	}
	shell->environment = make_env(shell, shell->env);
	return (0);
}
