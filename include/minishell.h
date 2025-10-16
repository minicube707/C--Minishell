/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:18:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/16 17:44:39 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line_bonus.h"
# include "libft.h"
# include <errno.h>
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

/*===================*/
/*=======GLOBAL======*/
/*===================*/
extern int				g_status;

/*===================*/
/*=======MACRO=======*/
/*===================*/
/*REDIRECTION*/
# define INPUT 0 // <
# define OUTPUT 1 // >
# define HERE_DOC 2 // <<
# define APPEND 3 // >>

/*CONTROL OPERATOR*/
# define EMPTY 4
# define PIPE 5 		// |
# define AND 6			// &&
# define OR 7			// ||
# define SEMICOL 8		// ;

/*===================*/
/*=====STRUCTURE=====*/
/*===================*/
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

typedef struct s_token
{
	int					op;
	char				*content;
	int					len;
	struct s_token		*next;
}						t_token;

// Strucuture to containt the info of the commande line
typedef struct s_list
{
	int					pre_redir;
	int					mypipe[2];
	char				*command;
	char				**option;
	t_file_info			**tab_file;
	int					in_out[2];
	char				*subshell;
	struct s_list		*next;
	struct s_list		*previous;
}						t_list;

typedef struct s_shell
{
	char				**environment;
	t_list_env			*env;
	t_list				*head;
}						t_shell;

/*===================*/
/*=====TAB_CHAR======*/
/*===================*/
void					tab_char_clear(char **tab);

/*===================*/
/*=====TAB_INFO======*/
/*===================*/
void					tab_info_clear(t_file_info **tab);

/*===================*/
/*=======DLIST=======*/
/*===================*/
t_list					*dlist_clear(t_list *head);
t_list					*dlist_get_top(t_list *head);

/*===================*/
/*=======COMMUN======*/
/*===================*/

/*Free Shell*/
void					free_shell(t_shell *shell, int exit_code);

/*Manage Error*/
int						print_error(char *string);
int						print_error_unknow_cmd(char *string);
int						print_error_file(char *cmd, char *file);
int						print_error_is_directory(char *file);
int						print_error_not_directory(char *cmd, char *file);
int						print_error_to_much(char *file);
int						print_error_env_not_set(char *file, char *env);
int						print_error_access_denied(char *file, char *path);
int						print_error_invalide_option(char *cmd, char *file);
int						print_error_nuremic_re(char *cmd, char *file);

/*===================*/
/*=====EXECUTION=====*/
/*===================*/



void	print_list(t_list *head);	


/*Here_doc*/
int						here_doc(int *file_fd, char *limiter);

/*Execute_close_file*/
int						manage_path(t_shell *shell, int change);

/*Execute_here_doc*/
void					execute_here_doc(t_list *head);

/*Execute_close_file*/
void					execute_close_fd(t_list *head);
void					execute_close_all_fd(t_list *head);

/*Execute_open_file*/
int						execute_open_file(t_list *head);

/*Execution Command*/
int						execute_command(t_shell *shell);

/*Execution Built In*/
int						execute_built_in(t_shell *shell);

/*Main Execution*/
void					execution(t_shell *shell,  int shell_channel[2]);

/*Expand dollar*/
char					*expand_dollard(t_shell *shell, char *string);

/*===================*/
/*======BUILTIN======*/
/*===================*/

int						ft_is_built_in(char *command);
void					ft_echo(t_shell *shell, char **tab_option);
void					ft_pwd(void);
int						ft_export(t_shell *shell, char **arg);
int						ft_unset(t_shell *shell, char **arg);
void					ft_env(char **environment);
int						size_t_list_env(t_list_env *env);
t_list_env				**set_export_list(t_list_env *env, int size);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_exit(t_shell *shell, char **tab_option);
void					ft_cd(t_shell *shell, char **tab_option);
void					chdir2(char *pwd);
char					*expand_path(t_shell *shell, char *pwd, char *change);
char					*norme_env(char *env, int n);
char					*cd_expand_home(t_shell *shell, char **tab_option, int *i);
int 					add_expand(t_shell *shell, char **pwd, char *string, char *before);	
/*===================*/
/*======PARSING======*/
/*===================*/

/*Environment*/
t_list_env				*set_env(char **envp);
char					**make_env(t_shell *shell, t_list_env *list);
char					*ft_getenv(t_shell *shell, char *name);
char					*ft_join_env(char *name, char *content);

/*Parsing*/
t_list					*parsing(char *line);
t_list					*new_node(t_list *curr, t_list *prev, t_token *token);
int						new_tab_file(t_list *curr, t_token **token, int f);
t_list					*new_list(t_token *token, t_list *prev);
int						count_redir(t_token *token);
int						count_option(t_token *token);
void					option_or_subs(t_list *curr, int *o, t_token *token);

/*Lexer*/
t_token					*lexer(char *str);

/*Lexer Utils*/
int						is_op(char *str);
size_t					op_len(int op);
void					in_quote(char *str, int *i);

/*Token Utils*/
t_token					*end_list(t_token *lst);
t_token					*new_token(char *content, int op);
int						add_back(t_token **head, char *content, int op);

/*Syntax*/
int						is_redirection(int op);
int						is_operator(int op);
char					*unclosed_quote(void);
int						check_redirection(char *str);
t_token					*checker(t_token *token);
int						error_token(int op);

/*Free Utils*/
void					free_env(t_list_env *head);
t_token					*free_token(t_token *head);
void					free_shell(t_shell *shell, int init);
void					free_env_node(t_list_env *env);
char					**free_double_array(char **list);

void					reset_signal_handlers(void);
int						strlenc(char *str, const char c);

/*Utils*/
void					*ft_realloc(void *ptr, size_t size, size_t oldsize);
char					*ft_strncat(char *dest, char *src, unsigned int nb);
#endif
