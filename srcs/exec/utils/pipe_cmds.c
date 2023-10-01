/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elnop <elnop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:07:58 by elnop             #+#    #+#             */
/*   Updated: 2023/09/30 15:29:33 by elnop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	new_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("can't create pipe\n");
		return (false);
	}
	return (true);
}

static bool	first_cmd(t_node *node, int pipe_fds[2])
{
	if (!new_pipe(pipe_fds))
		return (false);
	if (node)
		((t_cmd_data *)node->data)->fd_out = pipe_fds[1];
	else
		close(pipe_fds[1]);
	if (node)
		((t_cmd_data *)node->data)->close_fd = pipe_fds[0];
	return (true);
}

static bool	last_cmd(t_node *node, int pipe_fds[2])
{
	if (node)
		((t_cmd_data *)node->data)->fd_in = pipe_fds[0];
	else
		close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (true);
}

static bool	middle_cmds(t_node	*node, int pipe_fds[2])
{
	close(pipe_fds[1]);
	if (node)
		((t_cmd_data *)node->data)->fd_in = pipe_fds[0];
	else
		close(pipe_fds[0]);
	if (!new_pipe(pipe_fds))
		return (false);
	if (node)
		((t_cmd_data *)node->data)->fd_out = pipe_fds[1];
	else
		close(pipe_fds[1]);
	if (node)
		((t_cmd_data *)node->data)->close_fd = pipe_fds[0];
	return (true);
}

bool	pipe_cmds(t_node *node, int pipe_fds[2], size_t i, size_t cmds_nb)
{
	if (node)
		((t_cmd_data *)node->data)->is_piped = false;
	if (cmds_nb == 1)
		return (true);
	if (node)
		((t_cmd_data *)node->data)->is_piped = true;
	if (!i)
	{
		if (!first_cmd(node, pipe_fds))
			return (false);
	}
	else if (i == cmds_nb - 1)
	{
		if (!last_cmd(node, pipe_fds))
			return (false);
	}
	else if (!middle_cmds(node, pipe_fds))
		return (false);
	return (true);
}
