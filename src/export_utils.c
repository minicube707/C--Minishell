/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:58:34 by lupayet           #+#    #+#             */
/*   Updated: 2025/11/11 16:54:21 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return (((unsigned char)(s1[i])) - ((unsigned char)(s2[i])));
}

int	size_t_list_env(t_list_env *env)
{
	int			size;
	t_list_env	*curr;

	curr = env;
	size = 0;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

t_list_env	**set_export_list(t_list_env *env, int size)
{
	t_list_env	*curr;
	t_list_env	**list;
	int			i;

	list = malloc((size + 1) * sizeof(t_list_env *));
	list[size] = NULL;
	curr = env;
	i = 0;
	while (curr)
	{
		list[i++] = curr;
		curr = curr->next;
	}
	return (list);
}

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

int	error_id(char *arg, char **name_value)
{
	free(name_value[0]);
	free(name_value[1]);
	free(name_value);
	ft_putstr_fd("minishell: export '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("' is not a valid identifier\n", 2);
	return (1);
}
