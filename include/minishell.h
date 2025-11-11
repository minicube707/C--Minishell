/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupayet <lupayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:18:58 by fmotte            #+#    #+#             */
/*   Updated: 2025/11/11 16:49:00 by lupayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line_bonus.h"
# include "libft.h"
# include <dirent.h>
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
# define PIPE 5 // |
# define AND 6 // &&
# define OR 7 // ||
# define SEMICOL 8 // ;

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
	t_token				*token;
	struct s_shell		*parent_shell;
	int					exit_code;
}						t_shell;

typedef struct s_escape_utils
{
	size_t				i;
	size_t				len;
	size_t				buff;
	char				*arg;
}						t_escape_utils;

typedef struct s_struc
{
	char				*string1;
	char				*string2;
}						t_struc;

typedef struct s_two_int
{
	int					int1;
	int					int2;
}						t_two_int;

/*===================*/
/*=====TAB_CHAR======*/
/*===================*/
void					tab_char_clear(char **tab);
int						lenght_tab(char **tab);
void					sort_tab(char **tab);

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

/*===================*/
/*=======SHELL=======*/
/*===================*/
void					free_shell(t_shell *shell, int exit_code);
void					init_shell(t_shell *shell, char **envp,
							t_shell *parent_shell, int exit_code);
t_shell					*get_shell(t_shell *shell);

/*Manage Error*/
int						print_error(t_shell *shell, char *string);
int						print_error_unknow_cmd(char *string);
int						print_error_file(t_shell *shell, char *cmd, char *file,
							int exit_code);
int						print_error_is_directory(t_shell *shell, char *file);
int						print_error_not_directory(t_shell *shell, char *cmd,
							char *file);
int						print_error_to_much(t_shell *shell, char *file);
int						print_error_env_not_set(t_shell *shell, char *file,
							char *env);
int						print_error_access_denied(t_shell *shell, char *file,
							char *path, int exit_code);
int						print_error_invalide_option(t_shell *shell, char *cmd,
							char *file);
int						print_error_nuremic_re(t_shell *shell, char *cmd,
							char *file);

/*===================*/
/*=====EXECUTION=====*/
/*===================*/

/*Here_doc*/
int						here_doc(t_shell *shell, int *file_fd, char *limiter);
int						here_doc_loop_end(t_shell *shell, int fd, char *input,
							char *limiter);

/*Execute_close_file*/
int						manage_path(t_shell *shell, int change);

/*Execute_here_doc*/
int						execute_here_doc(t_shell *shell, t_list *head);

/*Execute_close_file*/
void					execute_close_fd(t_list *head);
void					execute_close_all_fd(t_shell *shell);

/*Execute_open_file*/
int						execute_open_file(t_shell *shell, t_list *head);

/*Execution Command*/
int						execute_command(t_shell *shell);

/*Execution Built In*/
int						execute_built_in(t_shell *shell);

/*Main Execution*/
void					execution(t_shell *shell, int shell_channel[2]);
int						execution_middle(t_shell *shell);

/*Expand dollar*/
char					*expand_path_wildcard_utils_utils(t_shell *shell,
							char *tmp, char **string, int *j);
char					*expand_dollard(t_shell *shell, char *string);
int						expand_path_all(t_shell *shell, char *change);

/*Remove quote*/
char					*remove_single_quote(t_shell *shell, char *string,
							char *tmp1);
char					*remove_double_quote(t_shell *shell, char *string,
							char *tmp1);

/*Wildcard*/
char					**wilcard(t_shell *shell, char *string);
void					backtracking(char *path, char *wilcard, char *path_file,
							char ***tab_file);
void					backtracking_loop(char ***tab_file,
							char *content_folder, char *path_file,
							t_struc painfull);
int						check_expand(char *string, char *wilcard);
char					**ft_realloc_flo(char **tab, char *string, int before);
char					*bactracking_stat(char *path, char *content_folder);
char					**ft_realloc_flo(char **tab, char *string, int before);
int						wildcard_init(t_shell *shell, char *string, char **path,
							char **expand);
void					wildcard_add_path(t_shell *shell, char **tab_file,
							char *path);
char					**wildcard_end(t_shell *shell, char *string,
							char *path);
int						expand_path_wildcard_i_want_to_die(char *tmpsq,
							char *tmpdq);

/*===================*/
/*======BUILTIN======*/
/*===================*/

int						ft_cd_change_env_utils(t_shell *shell, t_list_env *curr,
							char **tmp);
int						ft_is_built_in(char *command);
void					ft_echo(t_shell *shell);
void					ft_pwd(t_shell *shell);
int						ft_export(t_shell *shell, char **arg);
void					print_sort(t_list_env **arr, int size, int i);
char					**get_name_value(char *arg);
int						ft_unset(t_shell *shell, char **arg);
void					ft_env(t_shell *shell, char **environment);
int						size_t_list_env(t_list_env *env);
t_list_env				**set_export_list(t_list_env *env, int size);
int						ft_strcmp(const char *s1, const char *s2);
int						name_is_valid(char *arg);
int						error_id(char *arg, char **name_value);
void					ft_exit(t_shell *shell, char **tab_option);
void					ft_cd(t_shell *shell, char **tab_option);
void					chdir2(t_shell *shell, char *pwd);
char					*expand_path(t_shell *shell, char *pwd, char *change);
char					*norme_env(char *env, int n);
char					*cd_expand_home(t_shell *shell, char **tab_option,
							int *i);
int						add_expand(t_shell *shell, char **pwd, char *string,
							char *before);
/*===================*/
/*======PARSING======*/
/*===================*/

/*Environment*/
t_list_env				*set_env(char **envp, t_shell *shell);
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
int						is_delimiter(char *c);
size_t					op_len(int op);
void					in_quote(char *str, int *i);
int						escape_in_double_quote(char *str);
int						escape_in_no_quote(char *str);
int						escape_char_len(char *str);
void					append_escaped_char(char **arg, char *str, size_t *buff,
							size_t s);
char					*duparg(char *str, int *j);
char					*strcdup(char *str, char c);
char					*dup_shell_return(int op, int cl, char *str, int i);
char					*dup_subshell(char *str);

void					append_chars(char *str, t_escape_utils *var);
void					add_escape_char(char *str, int *j, t_escape_utils *var);
char					*free_get_arg(char *res, char *prev, char *new);
char					*get_arg(char *str, int *i);

/*Token Utils*/
t_token					*end_list(t_token *lst);
t_token					*new_token(char *content, int op);
int						add_back(t_token **head, char *content, int op);

/*Syntax*/
int						is_redirection(int op);
int						is_operator(int op);
char					*unclosed_quote(char *arg);
int						check_redirection(char *str);
t_token					*checker(t_token *token);
int						error_token(int op);
int						count_max_redir(char *str);
int						err_multi_redir(char c, int i);

/*Free Utils*/
void					free_env(t_list_env *head);
t_token					*free_token(t_token *head);
t_token					*free_token_all(t_token *head);
void					free_shell(t_shell *shell, int init);
void					free_env_node(t_list_env *env);
char					**free_double_array(char **list);

void					reset_signal_handlers(void);
int						strlenc(char *str, const char c);

/*Utils*/
int						strlenc(char *str, const char c);
void					*ft_realloc(void *ptr, size_t size, size_t oldsize);
char					*ft_strncat(char *dest, char *src, unsigned int nb);
int						ft_isspace(char c);

/*Signal*/
void					set_signal_action(void (*handler)(int));
void					sighandler(int signal);
void					sigintheredoc(int signal);
void					handlexec(int signal);

#endif
