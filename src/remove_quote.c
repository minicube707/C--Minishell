/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:58:14 by florent           #+#    #+#             */
/*   Updated: 2025/10/26 20:01:09 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quote1(char *string, char *tmp1, char **after)
{
	char	*before;
	char	*middle;
	char	*tmp2;

	before = ft_substr(string, 0, ft_strlen(string) - ft_strlen(tmp1));
	if (before == NULL)
	{
		free(string);
		return (NULL);
	}
	*after = ft_strchr(tmp1 + 1, '\'');
	middle = ft_substr(tmp1, 1, ft_strlen(tmp1) - ft_strlen(*after) - 1);
	if (middle == NULL)
	{
		free(before);
		free(string);
		return (NULL);
	}
	tmp2 = ft_strjoin(before, middle);
	free(before);
	free(middle);
	if (tmp2 == NULL)
		free(string);
	return (tmp2);
}

static char	*remove_quote2(char *string, char *tmp2, char *after)
{
	char	*new_string;

	new_string = ft_strjoin(tmp2, after + 1);
	free(tmp2);
	free(string);
	if (new_string == NULL)
		return (NULL);
	string = ft_strdup(new_string);
	free(new_string);
	if (string == NULL)
		return (NULL);
	return (string);
}

char	*remove_quote(t_shell *shell, char *string)
{
	char	*after;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strchr(string, '\'');
	while (tmp1 != NULL)
	{
		after = NULL;
		tmp2 = remove_quote1(string, tmp1, &after);
		if (tmp2 == NULL)
		{
			print_error(shell, "Error malloc");
			return (NULL);
		}
		string = remove_quote2(string, tmp2, after);
		if (string == NULL)
		{
			print_error(shell, "Error malloc");
			return (NULL);
		}
		tmp1 = ft_strchr(string, '\'');
	}
	return (string);
}
