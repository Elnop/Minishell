/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elnop <elnop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:48:19 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/30 11:33:39 by elnop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <sys/wait.h>
# include "../libs/liblp_c/liblp.h"

enum e_node_type
{
	CMD_NODE,
	AND_NODE,
	OR_NODE,
	PIPE_NODE,
	REDIR_NODE
};

typedef enum e_logical_operators
{
	AND_OPERATOR,
	OR_OPERATOR,
	NO_OPERATOR
}	t_logical_operators;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND
}	t_redir_type;

typedef struct s_node
{
	void				*data;
	enum e_node_type	type;
}	t_node;

typedef struct s_node_links {
	t_node	*left;
	t_node	*right;
}	t_node_links;

typedef struct s_cmd_data {
	int		fd_in;
	int		fd_out;
	bool	is_piped;
	int		close_fd;
	t_array	args;
}	t_cmd_data;

typedef struct s_redir_data {
	t_redir_type	type;
	char			*file_name;
	t_node			*next;
}	t_redir_data;

#endif