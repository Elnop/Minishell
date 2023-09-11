/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:32 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/11 20:10:07 by lperroti         ###   ########.fr       */
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

# define SPACERS " \a\t\r\v\f\n\b"

typedef char	*(*t_lexchar_function)(char **p_line);

typedef struct s_lexing_option
{
	char				character;
	t_lexchar_function	run;
}	t_lexing_option;

typedef struct s_app
{
	bool	exit;
	t_array	env;
}	t_app;

int		start(t_app *p_app);

// ---- BUILTINS
int		builtin_echo(char *str);
void	builtin_env(t_array	env_array);

// ---- PARSING
bool	copy_str(void *pelem, void *dest);
void	destroy_str(void *pelem);
t_array	line_to_array(char *line);
char	*get_next_word(char **p_line);
char	*expand(char *str, char next_char);

// ---- FOGGY TREE
void	*input_to_foggy_tree(char *line, t_app *p_app);

#endif