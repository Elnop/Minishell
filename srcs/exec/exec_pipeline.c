/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:22:18 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 05:36:00 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	new_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	set_cmd_fds(t_cmd_data *cmd, int pipe_fds[2], size_t i, size_t cmds_nb)
{
	if (cmds_nb == 1)
		return ;
	if (!i)
	{
		new_pipe(pipe_fds);
		cmd->fd_out = pipe_fds[1];
		cmd->close_fd = pipe_fds[0];
	}
	else if (i == cmds_nb - 1)
	{
		cmd->fd_in = pipe_fds[0];
		close(pipe_fds[1]);
	}
	else
	{
		close(pipe_fds[1]);
		cmd->fd_in = pipe_fds[0];
		new_pipe(pipe_fds);
		cmd->fd_out = pipe_fds[1];
		cmd->close_fd = pipe_fds[0];
	}
}

t_array	exec_pipeline(t_array nodes)
{
	t_array		pids;
	int			pipe_fds[2];
	size_t		i;
	t_cmd_data	*p_cmd_data;

	pids = array_new(10, sizeof(pid_t), NULL, NULL);
	i = 0;
	while (i < array_size(nodes))
	{
		p_cmd_data = (t_cmd_data *)((t_node **)nodes)[i]->data;
		set_cmd_fds(p_cmd_data, pipe_fds, i,
			array_size(nodes));
		array_pushback(&pids,
			(pid_t []){exec_cmd(p_cmd_data)});
		if (p_cmd_data->fd_in > -1)
			close(p_cmd_data->fd_in);
		i++;
	}
	return (pids);
}
