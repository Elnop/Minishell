/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:51:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/28 23:56:26 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef int	(*t_buildin_func)(t_cmd_data data);

static t_buildin_func	get_builtin_function(char *cmd_name)
{
	if (!lp_strncmp(cmd_name, "env", lp_strlen(cmd_name)))
		return (builtin_env);
	else
		return (NULL);
}

pid_t	exec_builtin(char *cmd_name, t_cmd_data data)
{
	pid_t			child_pid;
	t_buildin_func	run_builtin;
	int				*save_std_fds;

	run_builtin = get_builtin_function(cmd_name);
	if (!run_builtin)
		return (0);
	child_pid = 0;
	if (data.is_piped)
		child_pid = fork();
	else
		save_std_fds = (int [2]){dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	if (!child_pid)
	{
		dup_fds(data.fd_in, data.fd_out);
		close(data.close_fd);
		if (data.is_piped)
			exit(run_builtin(data));
		run_builtin(data);
		dup_fds(save_std_fds[0], save_std_fds[1]);
		return (-1);
	}	
	return (child_pid);
}
