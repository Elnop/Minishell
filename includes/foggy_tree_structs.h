/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foggy_tree_structs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:37:29 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/21 00:10:34 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOGGY_TREE_STRUCTS_H
# define FOGGY_TREE_STRUCTS_H

# include "minishell.h"

enum e_tree_node_type
{
	EXEC,
	AND_NODE,
	OR,
	PIPE,
	REDIR_IN,
	REDIR_IN_APPEND,
	REDIR_OUT,
	REDIR_OUT_APPEND,
};

typedef struct s_tree_root {
	e_tree_node_type	next_type;
	void				*next_type;
}	t_tree_root;

typedef struct s_exec_cmd {
	pid_t	fd_in;
	pid_t	fd_out;
	pid_t	cmd_name;
	pid_t	cmd_args;
}	t_exec_cmd;

t_tree_root	foggy_tree_init(t_array words);

#endif