/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:32 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 17:16:39 by titilamenace     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "fcntl.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
	int		exit_status;
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

// ---- ./BUILTINS
int		builtin_echo(char *str);
void	builtin_env(char **env_array);

// ---- ./DEBUG
void	print_str_array(char **words_list);
int		print_and(t_node_links data);
int		print_or(t_node_links data);
int		print_pipeline(t_array data);
int		print_cmd(t_cmd_data data);
int		print_tree(t_node node);

// ---- ./EXEC
int		exec(t_node *node);
pid_t	exec_cmd(t_cmd_data data);
t_array	exec_pipeline(t_array nodes);
int		exec_and(t_node_links data);
int		exec_or(t_node_links data);
// ---- ./EXEC_UTIS
char	*get_cmd_path(char *name);
int		wait_pids(t_array *pids);

// ---- ./EXPANDS
char	*expand(char **env, char *str);

// ---- ./MAKE_TREE
t_array	make_tree(char *line);
t_array	line_to_words(char *line);
t_node	*words_to_tree(char **words);
// ---- ./MAKE_TREE_NODES
t_node	*make_and_node(char **words);
t_node	*make_cmd_node(char **words);
t_node	*make_or_node(char **words);
t_node	*make_pipeline_node(char **words);
void	destroy_cmd(void *pelem);
void	destroy_pipeline(void *pelem);
void	destroy_tree_node(void *pelem);

// ---- ./UTILS
t_app	*get_app_data(void);
bool	copy_str(void *pelem, void *dest);
void	destroy_str(void *pelem);
size_t	is_operator(char *str);
size_t	get_left_length(char **words, char *limiter);
bool	add_to_garbage(void *ptr, t_garbage_item_type type);
void	handler_sig(int sig);
void	signal_handler();

#endif
