/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dup_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 02:01:58 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/25 02:41:57 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_print_errors(char *fn)
{
	if (!errno)
		return (false);
	(errno == EACCES && lp_dprintf(2, SHELL_NAME": %s:Permission denied\n", fn));
	(errno == EFAULT && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == EFBIG && lp_dprintf(2, SHELL_NAME": %s: file too big", fn));
	(errno == EINTR && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == EISDIR && lp_dprintf(2, SHELL_NAME": %s: Is a directory", fn));
	(errno == ELOOP && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == EMFILE && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENAMETOOLONG && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENFILE && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENODEV && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENOENT && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENOMEM && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENOSPC && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENOTDIR && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == ENXIO && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == EPERM && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == EROFS && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	(errno == EROFS && lp_dprintf(2, SHELL_NAME": %s: Permission denied\n", fn));
	(errno == ETXTBSY && lp_dprintf(2, SHELL_NAME":%s:Permission denied\n", fn));
	(errno == EWOULDBLOCK && lp_dprintf(2, SHELL_NAME": %s: error", fn));
	return (true);
}

static void	replace_fd(int *fd_dest, int new_fd)
{
	if (*fd_dest != -1)
		close(*fd_dest);
	*fd_dest = new_fd;
}

bool	open_dup_redirs(t_cmd_data *cmd_data, t_redir_data *redirs)
{
	size_t	i;

	i = 0;
	while (i < array_size((t_array)redirs))
	{
		if (redirs[i].type == REDIR_IN)
			replace_fd(&cmd_data->fd_in, open(redirs[i].file_name, O_RDONLY));
		if (redirs[i].type == REDIR_OUT)
			replace_fd(&cmd_data->fd_out, open(redirs[i].file_name,
					O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU));
		if (redirs[i].type == REDIR_OUT_APPEND)
			replace_fd(&cmd_data->fd_out, open(redirs[i].file_name,
					O_WRONLY | O_CREAT | O_APPEND, S_IRWXU));
		if (check_print_errors(redirs[i].file_name))
			return (false);
		i++;
	}
	return (true);
}
