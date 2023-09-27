/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:32 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 13:48:57 by lperroti         ###   ########.fr       */
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
int		builtin_echo(char *str);
void	builtin_env(char **env_array);

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
t_array	exec_pipeline(t_array nodes);
int		exec_and(t_node_links data);
int		exec_or(t_node_links data);
// ---- ./EXEC_UTIS
bool	open_dup_redirs(t_cmd_data *cmd_data, t_redir_data *redirs);
char	*get_cmd_path(char *name);
int		wait_pids(t_array *pids);

// ---- ./TRANSFORMATOR
char	*expand_parameters(char *str);
bool	replace_var(char **p_str, t_array *p_buff);
bool	expand_split_push(t_array *p_splited, char	**p_str);
bool	transform_list(t_array *list);
char	*get_env_var_value(char *var_name);

// ---- ./MAKE_TREE
t_array	make_tree(char *line);
t_array	line_to_words(char *line);
t_node	*words_to_tree(char **words);
// ---- ./MAKE_TREE_NODES
t_node	*make_and_node(char **words);
t_node	*make_cmd_node(char **words);
t_node	*make_or_node(char **words);
t_node	*make_pipeline_node(char **words);
t_array	make_redirs_array(char **words);
void	redir_data_destructor(void	*pelem);
void	destroy_cmd(void *pelem);
void	destroy_pipeline(void *pelem);
void	destroy_tree_node(void *pelem);

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