/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:04:55 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/20 14:58:03 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lenght_expand(char *string)
{
	int	i;
	
	if (ft_strncmp(string, "?",  1) == 0)
		return (2);
	i = 1;
	while (norme_env(string, i) && i < ft_strlen(string) + 1)
		i++;
	return (i);
}

static char	*add_expand_utils(t_shell *shell, char *str, char *bef, char *cha)
{
	char	*expand;
	char	*new_expand;
	char	*cp_pwd;
	int		i;

	i = lenght_expand(str + 1);
	expand = ft_substr(str, 0, i);
	new_expand = expand_dollard(shell, expand);
	if (expand == NULL || new_expand == NULL)
	{
		print_error("Error malloc\n");
		return (NULL);
	}
	if (ft_strncmp(new_expand, expand, ft_strlen(new_expand)) != 0)
		cp_pwd = ft_strjoin(bef, new_expand);
	else
		cp_pwd = ft_strjoin(bef, cha);
	free(expand);
	free(new_expand);
	return (cp_pwd);
}

int	add_expand(t_shell *shell, char **pwd, char *string, char *change)
{
	char	*after;
	int		i;
	char	*cp_pwd;
	char	*before;

	before = ft_substr(*pwd, 0, ft_strlen(*pwd) - ft_strlen(string));
	if (before == NULL)
		return (print_error("Error malloc"));
	i = lenght_expand(string + 1);
	cp_pwd = add_expand_utils(shell, string, before, change);
	free(before);
	if (cp_pwd == NULL)
		return (print_error("Error malloc"));
	after = ft_substr(string, i, ft_strlen(string) + 1);
	if (after == NULL)
		return (print_error("Error malloc"));
	free(*pwd);
	*pwd = ft_strjoin(cp_pwd, after);
	free(after);
	free(cp_pwd);
	return (0);
}

static 	char *search_dollars(char *string)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while(string[i] != '\0')
	{
		if (string[i] == '\'')
			count++;
		if (string[i] == '$' && count % 2 == 0)
			return(&string[i]);
		i++;
	}
	return (NULL);
}

char	*expand_path(t_shell *shell, char *pwd, char *change)
{
	char	*string;
	char    *new_string;
	
	string = search_dollars(pwd);
	while (string != NULL)
	{
		add_expand(shell, &pwd, string, change);
		if (pwd == NULL)
		{
			print_error("Error malloc");
			return (NULL);
		}
		string = search_dollars(pwd);
	}
	new_string = remove_quote(pwd);
	if (new_string == NULL)
	{
		print_error("Error malloc");
		return (NULL);
	}
	return (new_string);
}
