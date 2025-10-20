/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:51:49 by lupayet           #+#    #+#             */
/*   Updated: 2025/10/20 18:10:54 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	name_is_valid(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (0);
	arg++;
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (0);
		arg++;
	}
	return (1);
}

static int	error_id(char *arg)
{
	ft_putstr_fd("minishell: export '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("' is not a valid identifier\n", 2);
	return (1);
}
/*
static void	set_new_env(t_list_env *new, char *arg)
{
	size_t	l;

	l = strlenc(arg, '=');
	new->name = ft_substr(arg, 0, l);
	if (arg[l] == '=')
		l++;
	new->content = ft_strdup(&arg[l]);
	new->next = NULL;
}*/

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
	i = -1;
	while (++i < size)
		printf("export %s=%s\n", arr[i]->name, arr[i]->content);
	free(arr);
}
/*
void	export_arg(char *arg, t_list_env *curr)
{
	while (*arg)
	{
		curr = shell->env;
		if (!name_is_valid(*arg))
			return (error_id(*arg));
		while (curr->next)
		{
			if (ft_strcmp(curr->name, ))
			
			curr = curr->next;
		}
		curr->next = malloc(sizeof(t_list_env));
		set_new_env(curr->next, *arg);
		arg++;
	}
}
*/
t_list_env	*update_env_value(t_list_env *target, char **name_val)
{
	if (!target)
	{
		target = malloc(sizeof(t_list_env *));
		if (!target)
			free_shell(NULL, 1);
		target->name = name_val[0];
		target->content = NULL;
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
	if (arg[l] && arg[l + 1])
	{
		result[1] = ft_strdup(&arg[l + 1]);
		if (!result[0])
			free_shell(NULL, 1);
	}
	else
		result[1] = NULL;
	return (result);
}

int	ft_export(t_shell *shell, char **arg)
{
	t_list_env	*curr;
	int			size;
	char		**name_value;

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
		name_value = get_name_value(*arg);
		printf("%s => %s\n", name_value[0], name_value[1]);
		if (!name_is_valid(name_value[0]))
			return (error_id(*arg));
		while (curr)
		{
			if (!ft_strcmp(curr->name, name_value[0]))
			{
				printf("test\n");
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
	shell->environment = make_env(shell, shell->env);
	return (0);
}
