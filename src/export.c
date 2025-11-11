/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:51:49 by lupayet           #+#    #+#             */
/*   Updated: 2025/11/11 16:50:19 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	print_sort(arr, size, i);
	free(arr);
}

t_list_env	*update_env_value(t_list_env *target, char **name_val)
{
	if (!target)
	{
		target = malloc(sizeof(t_list_env));
		if (!target)
			free_shell(NULL, 1);
		target->name = name_val[0];
		target->content = NULL;
		target->next = NULL;
	}
	else
		free(name_val[0]);
	if (target->content)
		free(target->content);
	target->content = name_val[1];
	free(name_val);
	return (target);
}

char	**get_name_value(char *arg)
{
	char	**result;
	size_t	l;

	l = strlenc(arg, '=');
	result = malloc(sizeof(char *) * 2);
	if (!result)
		free_shell(NULL, 1);
	result[0] = ft_substr(arg, 0, l);
	if (!result[0])
		free_shell(NULL, 1);
	if (arg[l])
	{
		if (arg[l + 1])
			result[1] = ft_strdup(&arg[l + 1]);
		else
			result[1] = ft_strdup("");
		if (!result[0])
			free_shell(NULL, 1);
	}
	else
		result[1] = NULL;
	return (result);
}

int	handle_arg(t_shell *shell, char **arg, t_list_env *curr, char **name_value)
{
	while (*arg)
	{
		curr = shell->env;
		name_value = get_name_value(*arg);
		if (!name_is_valid(name_value[0]))
			return (error_id(*arg, name_value));
		while (curr)
		{
			if (!ft_strcmp(curr->name, name_value[0]))
			{
				curr = update_env_value(curr, name_value);
				break ;
			}
			if (curr->next)
				curr = curr->next;
			else
			{
				curr->next = update_env_value(curr->next, name_value);
				break ;
			}
		}
		arg++;
	}
	return (0);
}

int	ft_export(t_shell *shell, char **arg)
{
	int			size;
	char		**name_value;
	t_list_env	*curr;
	int			err;

	shell->exit_code = 0;
	name_value = NULL;
	curr = NULL;
	if (!arg[1])
	{
		size = size_t_list_env(shell->env);
		sort_list(set_export_list(shell->env, size), size);
		return (0);
	}
	arg++;
	err = handle_arg(shell, arg, curr, name_value);
	if (err)
		return (err);
	shell->environment = make_env(shell, shell->env);
	return (0);
}
