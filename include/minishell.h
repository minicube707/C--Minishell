/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:18:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/05 15:51:15 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// STRUCTURE
// Structure to containt the file info
typedef struct s_file_info
{
	int				type;
	char			*file_name;
	int				fd;
}					t_file_info;

// Strucuture to containt the environnement
typedef struct s_list_env
{
	char			*name;
	char			*content;
}					t_list_env;

// Strucuture to containt the info of the commande line
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

/*===================*/
/*=====EXECUTION=====*/
/*===================*/

/*Here_doc*/
int					here_doc(int *file_fd, char *limiter);

#endif