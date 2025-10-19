/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:58:14 by florent           #+#    #+#             */
/*   Updated: 2025/10/19 22:10:41 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *remove_quote_utils(char *tmp1, char *after)
{
    char    *before;
    
    if (tmp1 == NULL)
		return (NULL);
    before = ft_strjoin(tmp1, after);
    free(tmp1);
    if (before == NULL)
		return (NULL);
    return (before);
}

char *remove_quote(char *string)
{
    char    *before;
    char    *middle;
    char    *after;
    char    *tmp1;
    
    tmp1 = ft_strchr(string, '\'');
    before = ft_substr(string, 0, ft_strlen(string) - ft_strlen(tmp1));
    if (before == NULL)
		return (NULL);
    after = ft_strchr(tmp1+1, '\'');
    middle = ft_substr(tmp1, 1, ft_strlen(tmp1) - ft_strlen(after) -1);
    if (middle == NULL)
    {
        free(before);
       return (NULL); 
    }
    tmp1 = ft_strjoin(before, middle);
    free(before);
    free(middle);
    before = remove_quote_utils(tmp1, after+1);
    if (before == NULL)
        return (NULL);
    return(before);
}
