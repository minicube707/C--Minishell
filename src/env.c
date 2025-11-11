/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:38:53 by lupayet           #+#    #+#             */
/*   Updated: 2025/11/11 18:12:51 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_new_env(t_list_env *new, char *envp)
{
	new->name = ft_substr(envp, 0, strlenc(envp, '='));
	if (!new->name)
		free_shell(NULL, 1);
	if (ft_strncmp(new->name, "SHLVL", ft_strlen(new->name)) == 0)
		new->content = ft_itoa(ft_atoi(getenv(new->name)) + 1);
	else
		new->content = ft_strdup(getenv(new->name));
}

t_list_env	*set_env(char **envp, t_shell *shell)
{
	t_list_env	*new;

	new = NULL;
	while (*envp)
	{
		if (!shell->env)
		{
			new = malloc(sizeof(t_list_env));
			if (!new)
				free_shell(NULL, 1);
			new->next = NULL;
			shell->env = new;
		}
		else
		{
			new->next = malloc(sizeof(t_list_env));
			if (!new->next)
				free_shell(NULL, 1);
			new = new->next;
			new->next = NULL;
		}
		set_new_env(new, *envp);
		envp++;
	}
	return (shell->env);
}

int	list_size(t_list_env *list)
{
	int	s;

	s = 0;
	while (list)
	{
		s++;
		list = list->next;
	}
	return (s);
}

void	make_env_loop(char **env, t_list_env *list)
{
	int		i;
	char	*p;

	i = 0;
	while (list)
	{
		p = ft_strjoin(list->name, "=");
		if (!p)
			free_shell(NULL, 1);
		if (list->content)
		{
			env[i] = ft_strjoin(p, list->content);
			free(p);
			if (!env[i])
				free_shell(NULL, 1);
		}
		else
			env[i] = p;
		i++;
		list = list->next;
	}
}

char	**make_env(t_shell *shell, t_list_env *list)
{
	int	size;

	shell->environment = free_double_array(shell->environment);
	size = list_size(list);
	shell->environment = ft_calloc(sizeof(char *), (size + 1));
	if (!shell->environment)
		free_shell(NULL, 1);
	make_env_loop(shell->environment, list);
	return (shell->environment);
}
