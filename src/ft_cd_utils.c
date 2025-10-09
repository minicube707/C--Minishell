/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:24:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/09 13:46:22 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    chdir2(char *pwd)
{
    if (chdir(pwd))
    {
        if (errno == EACCES)
            print_error_access_denied("cd", pwd);
        if (errno == ENOTDIR)
            print_error_not_directory("cd", pwd);
        if (errno == ENOENT)
            print_error_file("cd", pwd);
    }
}
