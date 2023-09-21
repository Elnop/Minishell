/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:32 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/21 04:41:39 by lperroti         ###   ########.fr       */
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

# include "../libs/liblp_c/liblp.h"
# include "tree.h"

# define SPACERS " \t"
# define EXPAND_SPECIAL_PARAMETERS "@*-#?!0"

typedef struct s_app
{
	bool	exit;
	t_array	env;
}	t_app;

int		start(t_app *p_app);

// ---- BUILTINS
int		builtin_echo(char *str);
void	builtin_env(char **env_array);

// ---- PARSING
bool	copy_str(void *pelem, void *dest);
void	destroy_str(void *pelem);
size_t	is_operator(char *str);
size_t	get_left_length(char **words, char *limiter);
char	*expand(char **env, char *str);

// ---- MAKE TREE
t_node	*make_and_node(char **words);
t_node	*make_cmd_node(char **words);
t_node	*make_or_node(char **words);
t_node	*make_pipe_node(char **words);
t_array	line_to_words(char *line);
t_node	*words_to_tree(char **words);
t_array	line_to_tree(char *line);

// ---- DEBUG
void	print_str_array(char **words_list);
int		print_tree(t_node node);

#endif