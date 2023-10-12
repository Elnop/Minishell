/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:22:18 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/12 03:09:35 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node	*get_cmd(t_node *node)
{
	while (node && node->type != CMD_NODE)
	{
		if (node->type == HEREDOC_NODE)
			node = ((t_heredoc_data *)node->data)->next;
		else
			node = ((t_redir_data *)node->data)->next;
	}
	return (node);
}

static void	close_fds(t_cmd_data cmd_data)
{
	if (cmd_data.fd_in != -1)
		close(cmd_data.fd_in);
	if (cmd_data.fd_out != -1)
		close(cmd_data.fd_out);
}

t_array	exec_pipeline(t_array nodes)
{
	t_array		pids;
	int			pipe_fds[2];
	size_t		i;
	t_node		*pcmd;

	pids = add_grb(array_new(100000, sizeof(pid_t), NULL, NULL), GRBG_ARRAY);
	i = 0;
	while (pids && i < array_size(nodes))
	{
		pcmd = get_cmd(((t_node **)nodes)[i]);
		if (!pipe_cmds(pcmd, pipe_fds, i, array_size(nodes)))
			return (array_free(pids), NULL);
		if (!open_redirs(((t_node **)nodes)[i], pcmd, &pids) && pcmd && ++i)
		{
			close_fds(*(t_cmd_data *)pcmd->data);
			continue ;
		}
		if (pcmd && !array_pushback(&pids,
				(pid_t []){exec_cmd((t_cmd_data *)pcmd->data)}))
			continue ;
		if (pcmd && ((t_cmd_data *)pcmd->data)->fd_in > -1)
			close(((t_cmd_data *)pcmd->data)->fd_in);
		i++;
	}
	return (pids);
}
