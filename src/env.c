/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:38:53 by lupayet           #+#    #+#             */
/*   Updated: 2025/09/30 10:58:43 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlenc(char *str, const char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (*str && *str != c)
	{
		i++;
		str++;
	}
	return (i);
}

static void	set_new_env(t_list_env *new, char *envp)
{
	new->name = ft_substr(envp, 0, strlenc(envp, '='));
	if (!new->name)
		write(1, "Error env-name\n", 15);
	new->content = getenv(new->name);
}

t_list_env	*set_env(char **envp)
{
	t_list_env	*new;
	t_list_env	*head;

	new = NULL;
	head = NULL;
	while (*envp)
	{
		if (!head)
		{
			new = malloc(sizeof(t_list_env));
			new->next = NULL;
			head = new;
		}
		else
		{
			new->next = malloc(sizeof(t_list_env));
			new = new->next;
			new->next = NULL;
		}
		set_new_env(new, *envp);
		envp++;
	}
	return (head);
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

char	**make_env(t_shell *shell, t_list_env *list)
{
    char	**env;
    int		size;
    int		i;
    char	*p;

    i = 0;
	shell->environment = free_double_array(shell->environment);
    size = list_size(list);
    env = malloc(sizeof(char *) * (size + 1));
    if (!env)
        return (NULL);
    env[size] = NULL;
    while (list)
    {
        p = ft_strjoin(list->name, "=");
        env[i] = ft_strjoin(p, list->content);
        free(p);
        i++;
        list = list->next;
    }
    return (env);
}
