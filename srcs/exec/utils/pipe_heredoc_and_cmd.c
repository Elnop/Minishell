/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc_and_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:21:27 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/12 03:04:31 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	replace_fd(int *fd_dest, int new_fd)
{
	if (*fd_dest != -1)
		close(*fd_dest);
	*fd_dest = new_fd;
}

pid_t	pipe_heredoc_and_cmd(t_heredoc_data heredoc_data, t_cmd_data *p_cmd)
{
	pid_t	c_pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (-1);
	replace_fd(&p_cmd->fd_in, pipe_fds[0]);
	c_pid = fork();
	if (!c_pid && !close(get_app_data()->s_out) && !close(get_app_data()->s_in))
	{
		close(pipe_fds[0]);
		(p_cmd->close_fd != -1 && close(p_cmd->close_fd));
		(p_cmd->fd_out != -1 && close(p_cmd->fd_out));
		write(pipe_fds[1], heredoc_data.buff, lp_strlen(heredoc_data.buff));
		destroy_app();
		close(pipe_fds[1]);
		exit(0);
	}
	close(pipe_fds[1]);
	return (c_pid);
}
