/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:13:47 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/07 23:00:55 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_fds(t_cmd_data cmd_data)
{
	if (cmd_data.fd_in != -1)
		close(cmd_data.fd_in);
	if (cmd_data.fd_out != -1)
		close(cmd_data.fd_out);
}

static pid_t	normal_exec(t_cmd_data data)
{
	pid_t	child_pid;
	char	*cmd_path;
	char	**cmd_args;
	char	**cmd_env;

	if (!*((char **)data.args)[0])
		return (-1);
	cmd_path = get_cmd_path(((char **)data.args)[0]);
	if (!cmd_path && lp_dprintf(2, RED"%s: '%s': command not found\n"COLOR_OFF,
			(char *)SHELL_NAME, ((char **)data.args)[0]))
	{
		get_app_data()->lastcode = 127;
		return (-1);
	}
	child_pid = fork();
	if (!child_pid)
	{
		dup_fds(data.fd_in, data.fd_out);
		(data.close_fd != -1 && close(data.close_fd));
		cmd_args = array_to_strtab(data.args);
		cmd_env = array_to_strtab(get_app_data()->env);
		execve(cmd_path, cmd_args, cmd_env);
	}
	free(cmd_path);
	return (child_pid);
}

pid_t	exec_cmd(t_cmd_data *pdata)
{
	pid_t	child_pid;

	if (!transform_list(&pdata->args))
		return (lp_dprintf(2, RED"Error expand\n"COLOR_OFF), -1);
	child_pid = exec_builtin(*(char **)pdata->args, *pdata);
	if (!child_pid)
		child_pid = normal_exec(*pdata);
	close_fds(*pdata);
	return (child_pid);
}
