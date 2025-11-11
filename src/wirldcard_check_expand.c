/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wirldcard_check_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:13:26 by fmotte            #+#    #+#             */
/*   Updated: 2025/11/11 18:13:53 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_next_wildcards(char *wilcard, int i, char **wild1, char **wild2)
{
	*wild1 = ft_strchr(&wilcard[i], '*');
	*wild2 = ft_strchr(&wilcard[i + 1], '*');
}

int	check_expand_middle_loop(t_struc hate, char *tmp, int *i, int *j)
{
	int	not_ok;

	not_ok = 1;
	while (ft_strlen(hate.string2) > (*i) + 1 && hate.string2[(*i) + 1] != '*'
		&& hate.string2[(*i) + 1] != '\0' && not_ok)
	{
		while (hate.string1[(*j)] != '\0' && hate.string2[(*i) + 1]
			!= hate.string1[(*j)])
			(*j)++;
		if (ft_strncmp(&(hate.string1)[(*j)], tmp, ft_strlen(tmp)) == 0)
			not_ok = 0;
		else
		{
			(*i)--;
			(*j)++;
		}
		if ((*j) >= ft_strlen(hate.string1))
		{
			free(tmp);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	check_expand_middle(t_struc pain, int i)
{
	int		j;
	char	*tmp;
	char	*wild1;
	char	*wild2;
	char	*wild3;

	wild1 = NULL;
	wild2 = NULL;
	wild3 = ft_strrchr(&(pain.string2)[i], '*');
	find_next_wildcards(pain.string2, i, &wild1, &wild2);
	j = i;
	while (ft_strncmp(wild1, wild3, ft_strlen(wild1)) != 0)
	{
		while (ft_strlen(wild1) - ft_strlen(wild2) == 1)
			find_next_wildcards(pain.string2, ++i, &wild1, &wild2);
		tmp = ft_substr(&(pain.string2)[i], 1, ft_strlen(wild1)
				- ft_strlen(wild2) - 1);
		if (check_expand_middle_loop(pain, tmp, &i, &j))
			return (1);
		i += ft_strlen(tmp);
		free(tmp);
		if (pain.string2[i] != '\0')
			find_next_wildcards(pain.string2, i, &wild1, &wild2);
	}
	return (0);
}

int	check_expand_last(char *string, char *wilcard)
{
	int	i;
	int	j;

	i = ft_strlen(wilcard);
	j = ft_strlen(string);
	while (wilcard[i] != '*' && i >= 0 && j >= 0)
	{
		if (wilcard[i] != string[j])
			return (1);
		i--;
		j--;
	}
	return (0);
}

int	check_expand(char *string, char *wilcard)
{
	int		i;
	t_struc	help;

	if (ft_strchr(wilcard, '*') == NULL && ft_strncmp(string, wilcard,
			ft_strlen(string)) == 0 && ft_strlen(string) == ft_strlen(wilcard))
		return (1);
	i = 0;
	while (wilcard[i] != '*' && wilcard[i] != '\0' && string[i] != '\0')
	{
		if (wilcard[i] != string[i])
			return (0);
		i++;
	}
	if (wilcard[i] != '*')
		return (0);
	help.string1 = string;
	help.string2 = wilcard;
	if (check_expand_middle(help, i))
		return (0);
	if (check_expand_last(string, wilcard))
		return (0);
	return (1);
}
