/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:18:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/09/14 20:45:40 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line_bonus.h"
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

/*REDIRECTION*/
# define INPUT 0		// <
# define OUTPUT 1		// >
# define HERE_DOC 2		// <<
# define APPEND 3		// >>

/*CONTROL OPERATOR*/
# define EMPTY 4
# define PIPE 5 		// |
# define AND 6			// &&
# define OR 7			// ||

// STRUCTURE
// Structure to containt the file info
typedef struct s_file_info
{
	int					type;
	char				*file_name;
	int					fd;
}						t_file_info;

// Strucuture to containt the environnement
typedef struct s_list_env
{
	char				*name;
	char				*content;
	struct s_list_env	*next;
}						t_list_env;

// Strucuture to containt the input/ouput of a bloc
typedef struct s_channel
{
	int					in;
	int					out;
}						t_channel;

typedef struct s_token
{
	int				op;
	char			*content;
	struct s_token	*next;
}						t_token;

// Strucuture to containt the info of the commande line
typedef struct s_list
{
	char				**environment; // -> (changemnt temporaire besion pour test a remettre t_list_env)
	t_list_env			*env;
	int					pre_redir;
	int					mypipe[2];
	char				*command;
	char				**option;
	t_file_info			**tab_file;
	t_channel 			*in_out;
	char				*subshell;
	struct s_list		*next;
	struct s_list		*previous;
}						t_list;

/*===================*/
/*====Temporaire=====*/
/*===================*/
t_list  				*tmp_parsing(int argc, char **argv, char **envp);


/*===================*/
/*=======COMMUN======*/
/*===================*/

/*Manage Error*/
void					print_error(char *string);
void					print_error_unknow_cmd(char *string);
void					print_error_file(char *file);

/*===================*/
/*=====EXECUTION=====*/

/*===================*/
/*Here_doc*/
int						here_doc(int *file_fd, char *limiter);

/*Execute_here_doc*/
void					execute_here_doc(t_list *head);

/*Execute_close_file*/
void    				execute_close_fd(t_list *head);

/*Execute_open_file*/
int						execute_open_file(t_list *head	);

/*Execution Command*/
int 					execute_command(t_list *head);

/*Main Execution*/
void					execution(t_list *head, int subshell,
							t_channel *shell_channel);

/*===================*/
/*======PARSING======*/
/*===================*/

/*Parsing*/
t_list					*parsing(char *line, char **envp);

/*Lexer*/
t_token	*lexer(char *str);

/*Token Utils*/
t_token	*end_list(t_token *lst);
t_token *new_token(char *content, int op);
int	add_back(t_token **head, char *content,  int op);

/*Free Utils*/
void	free_env(t_list_env *head);
void	free_token(t_token *head);
#endif
