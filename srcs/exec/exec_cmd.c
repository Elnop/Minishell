/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:13:47 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 05:35:32 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_fds(t_cmd_data cmd_data)
{
	if (cmd_data.fd_in != -1)
	{
		dup2(cmd_data.fd_in, STDIN_FILENO);
		close(cmd_data.fd_in);
	}
	if (cmd_data.fd_out != -1)
	{
		dup2(cmd_data.fd_out, STDOUT_FILENO);
		close(cmd_data.fd_out);
	}
	if (cmd_data.close_fd != -1)
		close(cmd_data.close_fd);
}

void	close_fds(t_cmd_data cmd_data)
{
	if (cmd_data.fd_in != -1)
		close(cmd_data.fd_in);
	if (cmd_data.fd_out != -1)
		close(cmd_data.fd_out);
}

pid_t	exec_cmd(t_cmd_data *data)
{
	char	*cmd_path;
	char	**cmd_args;
	char	**env;
	pid_t	child_pid;

	if (!transform_list(&data->args))
		return (lp_dprintf(2, RED"Error"COLOR_OFF), -1);
	if (!open_dup_redirs(data, data->redirs))
		return (-1);
	cmd_path = get_cmd_path(((char **)data->args)[0]);
	if (!cmd_path && lp_dprintf(2, RED"%s: '%s': command not found\n"COLOR_OFF,
			(char *)SHELL_NAME, ((char **)data->args)[0]))
	{
		get_app_data()->lastcode = 127;
		return (-1);
	}
	child_pid = fork();
	if (!child_pid)
	{
		dup_fds(*data);
		cmd_args = array_to_strtab(data->args);
		env = array_to_strtab(get_app_data()->env);
		execve(cmd_path, cmd_args, env);
	}
	close_fds(*data);
	free(cmd_path);
	return (child_pid);
}
