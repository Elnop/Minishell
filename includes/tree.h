/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:48:19 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 02:26:19 by lperroti         ###   ########.fr       */
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

enum e_redir_type
{
	IN,
	IN_APPEND,
	OUT,
	OUT_APPEND,
};

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
	int		close_fd;
	t_array	args;
}	t_cmd_data;

typedef struct s_redir_data {
	enum e_redir_type	type;
	char				*file_name;
	t_node				*cmd;
}	t_redir_data;

#endif