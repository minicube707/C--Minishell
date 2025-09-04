/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:18:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/04 18:37:29 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// STRUCTURE
typedef struct s_list
{
	t_list_env		**enviroment;
	int				next_redir;
	int				mypipe[2];
	char			*command;
	char			**option;
	t_file_info		**tab_file;
	struct s_list	*next;
	struct s_list	*previous;
}					t_list;

typedef struct s_file_info
{
	int				type;
	char			*file_name;
	int				fd;
}					t_file_info;

typedef struct s_list_env
{
	int				type;
	char			*file_name;
	int				fd;
}					t_list_env;

#endif