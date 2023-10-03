/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elnop <elnop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:32 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/30 15:19:06 by elnop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "fcntl.h"
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libs/liblp_c/liblp.h"
# include "tree.h"
# include "colors.h"

# define SHELL_NAME "Minoushell"
# define SPACERS " \t"
# define EXPAND_SPECIAL_PARAMETERS "@*-#?!0"

typedef struct s_app
{
	bool	exit;
	t_array	env;
	bool	debug;
	char	lastcode;
	t_array	garbage;
}	t_app;

typedef enum e_garbage_item_type
{
	GRBG_ARRAY,
	GRBG_SIMPLE,
	GRBG_TREE_NODE
}	t_garbage_item_type;

typedef struct s_garbage_item
{
	void				*ptr;
	t_garbage_item_type	type;
}	t_garbage_item;

void	start(void);
bool	init_app(int ac, char **av, char **env);
void	destroy_app(void);
bool	clean_garbage(void);

// ---- ./BUILTINS
int		builtin_env(char **args);
int		builtin_cd(char **args);
int		builtin_exit(char **args);
int		builtin_export(char **args);
int		builtin_pwd(char **str);
int		builtin_unset(char **str);

// ---- ./DEBUG
void	print_str_array(char **words_list);
int		print_and(t_node_links data);
int		print_or(t_node_links data);
int		print_pipeline(t_array data);
int		print_cmd(t_cmd_data data);
void	print_redirs(t_redir_data *redirs);
int		print_tree(t_node node);

// ---- ./EXEC
int		exec(t_node *node);
pid_t	exec_cmd(t_cmd_data *data);
pid_t	exec_builtin(char *cmd_name, t_cmd_data data);
t_array	exec_pipeline(t_array nodes);
int		exec_and(t_node_links data);
int		exec_or(t_node_links data);
// ---- ./EXEC_UTILS
bool	open_redirs(t_node *node, t_node *p_cmd);
char	*get_cmd_path(char *name);
int		wait_pids(t_array *pids);
void	dup_fds(int fd_in, int fd_out);
bool	pipe_cmds(t_node *node, int pipe_fds[2], size_t i, size_t cmds_nb);

// ---- ./TRANSFORMATOR
char	*expand_parameters(char *str);
bool	replace_var(char **p_str, t_array *p_buff);
bool	expand_split_push(t_array *p_splited, char	**p_str);
bool	transform_list(t_array *list);
char	*get_env_var_value(char *var_name);
char	*expand_tilde(char *str);
char	*get_subword(char **p_str, char *limiters);
char	*expand_unquote(char **p_str);

// ---- ./MAKE_TREE
t_node	*make_tree(char *line);
t_array	line_to_words(char *line);
t_node	*words_to_tree(char **words);
// ---- ./MAKE_TREE_NODES
t_node	*make_and_node(char **words);
t_node	*make_cmd_node(char **words);
t_node	*make_or_node(char **words);
t_node	*make_pipeline_node(char **words);
t_node	*make_redir_node(char **words);
// ---- ./MAKE_TREE_UTILS
bool	is_redir_operator(char *word);
bool	has_redir_operator(char **words);
void	destroy_cmd(void *pelem);
void	destroy_pipeline(void *pelem);
void	destroy_tree_node(void *pelem);
void	redir_data_destructor(void	*pelem);

// ---- ./UTILS
t_app	*get_app_data(void);
bool	copy_str(void *pelem, void *dest);
void	destroy_str(void *pelem);
void	p_array_destroyer(void *pelem);
size_t	is_operator(char *str);
size_t	get_left_length(char **words, char *limiter);
bool	add_to_garbage(void *ptr, t_garbage_item_type type);
bool	has_quote(char *str);

#endif
