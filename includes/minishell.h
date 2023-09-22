/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:32 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/22 23:21:05 by lperroti         ###   ########.fr       */
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

# define SHELL_NAME "Minoushell"
# define SPACERS " \t"
# define EXPAND_SPECIAL_PARAMETERS "@*-#?!0"

// =========================
//     PRINT WITH COLORS
// =========================
# define COLOR_OFF "\033[0m"       // Text Reset
// Regular Colors
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"    
# define GREEN "\033[0;32m"        
# define YELLOW "\033[0;33m"       
# define BLUE "\033[0;34m"         
# define PURPLE "\033[0;35m"       
# define CYAN "\033[0;36m"         
# define WHITE "\033[0;37m"        
// Bold
# define BBLACK "\033[1;30m"       // BLACK
# define BRED "\033[1;31m"         // RED
# define BGREEN "\033[1;32m"       // GREEN
# define BYELLOW "\033[1;33m"      // YELLOW
# define BBLUE "\033[1;34m"        // BLUE
# define BPURPLE "\033[1;35m"      // PURPLE
# define BCYAN "\033[1;36m"        // CYAN
# define BWHITE "\033[1;37m"       // WHITE
// Underline
# define UBLACK "\033[4;30m"       // BLACK
# define URED "\033[4;31m"         // RED
# define UGREEN "\033[4;32m"       // GREEN
# define UYELLOW "\033[4;33m"      // YELLOW
# define UBLUE "\033[4;34m"        // BLUE
# define UPURPLE "\033[4;35m"      // PURPLE
# define UCYAN "\033[4;36m"        // CYAN
# define UWHITE "\033[4;37m"       // WHITE
// Background
# define BG_BLACK "\033[40m"       // BLACK
# define BG_RED "\033[41m"         // RED
# define BG_GREEN "\033[42m"       // GREEN
# define BG_YELLOW "\033[43m"      // YELLOW
# define BG_BLUE "\033[44m"        // BLUE
# define BG_PURPLE "\033[45m"      // PURPLE
# define BG_CYAN "\033[46m"        // CYAN
# define BG_WHITE "\033[47m"       // WHITE
// High Intensity
# define IBLACK "\033[0;90m"       // BLACK
# define IRED "\033[0;91m"         // RED
# define IGREEN "\033[0;92m"       // GREEN
# define IYELLOW "\033[0;93m"      // YELLOW
# define IBLUE "\033[0;94m"        // BLUE
# define IPURPLE "\033[0;95m"      // PURPLE
# define ICYAN "\033[0;96m"        // CYAN
# define IWHITE "\033[0;97m"       // WHITE
// Bold High Intensity
# define BIBLACK "\033[1;90m"      // BLACK
# define BIRED "\033[1;91m"        // RED
# define BIGREEN "\033[1;92m"      // GREEN
# define BIYELLOW "\033[1;93m"     // YELLOW
# define BIBLUE "\033[1;94m"       // BLUE
# define BIPURPLE "\033[1;95m"     // PURPLE
# define BICYAN "\033[1;96m"       // CYAN
# define BIWHITE "\033[1;97m"      // WHITE
// High Intensity backgrounds
# define BG_IBLACK "\033[0;100m"   // BLACK
# define BG_IRED "\033[0;101m"     // Red
# define BG_IGREEN "\033[0;102m"   // Green
# define BG_IYELLOW "\033[0;103m"  // YELLOW
# define BG_IBLUE "\033[0;104m"    // Blue
# define BG_IPURPLE "\033[0;105m"  // PURPLE
# define BG_ICYAN "\033[0;106m"    // Cyan
# define BG_IWHITE "\033[0;107m"   // White

typedef struct s_app
{
	bool	exit;
	t_array	env;
	char	lastcode;
}	t_app;

int		start(void);

// ---- ./BUILTINS
int		builtin_echo(char *str);
void	builtin_env(char **env_array);

// ---- ./DEBUG
void	print_str_array(char **words_list);
int		print_tree(t_node node);

// ---- ./EXEC
int		exec(t_node *node);
pid_t	exec_cmd(t_cmd_data data);
t_array	*exec_pipe(t_node_links node_links);
// ---- ./EXEC_UTIS
char	*get_cmd_path(char *name);

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

// ---- ./UTILS
t_app	*get_app_data(void);
bool	copy_str(void *pelem, void *dest);
void	destroy_str(void *pelem);
size_t	is_operator(char *str);
size_t	get_left_length(char **words, char *limiter);

#endif