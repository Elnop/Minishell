/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:51:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/12 14:15:07 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef int	(*t_buildin_func)(char **args);

static t_buildin_func	get_builtin_function(char *cmd_name)
{
	if (!lp_strncmp(cmd_name, "env", 4))
		return (builtin_env);
	if (!lp_strncmp(cmd_name, "cd", 3))
		return (builtin_cd);
	if (!lp_strncmp(cmd_name, "exit", 5))
		return (builtin_exit);
	if (!lp_strncmp(cmd_name, "echo", 5))
		return (builtin_echo);
	if (!lp_strncmp(cmd_name, "export", 7))
		return (builtin_export);
	if (!lp_strncmp(cmd_name, "pwd", 4))
		return (builtin_pwd);
	if (!lp_strncmp(cmd_name, "unset", 6))
		return (builtin_unset);
	else
		return (NULL);
}

static void	child_or_not(t_cmd_data data, char **args, t_buildin_func run_b)
{
	int		code;

	dup_fds(data.fd_in, data.fd_out);
	(data.close_fd != -1 && close(data.close_fd));
	get_app_data()->lastcode = run_b(args);
	code = get_app_data()->lastcode;
	if (data.is_piped)
	{
		close(get_app_data()->s_in);
		close(get_app_data()->s_out);
		lp_free_strtab(args, lp_strtab_size(args));
		destroy_app();
		exit(code);
	}
}

pid_t	exec_builtin(char *cmd_name, t_cmd_data data)
{
	pid_t			child_pid;
	t_buildin_func	run_b;
	int				*save_std_fds;
	char			**args;

	run_b = get_builtin_function(cmd_name);
	if (!run_b)
		return (0);
	args = array_to_strtab(data.args);
	if (!args)
		return (-1);
	child_pid = -1;
	if (data.is_piped)
		child_pid = fork();
	else
		save_std_fds = (int [2]){dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	if (!child_pid || child_pid == -1)
		child_or_not(data, args, run_b);
	if (!data.is_piped)
		dup_fds(save_std_fds[0], save_std_fds[1]);
	return (lp_free_strtab(args, lp_strtab_size(args)), child_pid);
}
