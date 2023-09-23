/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:13:47 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 03:09:27 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_strtab(char **strtab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(strtab[i++]);
	}
	free(strtab);
}

char	**array_to_strtab(t_array arr)
{
	char	**strtab;
	size_t	i;

	if (!arr)
		return (NULL);
	strtab = malloc(array_size(arr) * sizeof(char *));
	if (!strtab)
		return (NULL);
	i = 0;
	while (i < array_size(arr) - 1)
	{
		strtab[i] = lp_strdup(((char **)arr)[i]);
		if (!strtab[i])
			return (free_strtab(strtab, i), NULL);
		i++;
	}
	strtab[i] = NULL;
	return (strtab);
}

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
}

void	close_fds(t_cmd_data cmd_data)
{
	if (cmd_data.close_fd != -1)
		close(cmd_data.close_fd);
}


pid_t	exec_cmd(t_cmd_data data)
{
	char	*cmd_path;
	char	**cmd_args;
	char	**env;
	pid_t	child_pid;

	cmd_path = get_cmd_path(((char **)data.args)[0]);
	if (!cmd_path)
		return (printf(RED"%s: '%s': command not found\n"COLOR_OFF,
				(char *)SHELL_NAME, ((char **)data.args)[0]), 127);
	child_pid = fork();
	if (!child_pid)
	{
		dup_fds(data);
		close_fds(data);
		cmd_args = array_to_strtab(data.args);
		env = array_to_strtab(get_app_data()->env);
		execve(cmd_path, cmd_args, env);
	}
	return (child_pid);
}
