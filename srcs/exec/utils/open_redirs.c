/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 02:01:58 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/12 14:11:53 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_print_errors(char *fn)
{
	if (!errno)
		return (false);
	(errno == EACCES && lp_dprintf(2, SHELL_NAME": %s:Perm denied\n", fn));
	(errno == EFAULT && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == EFBIG && lp_dprintf(2, SHELL_NAME": %s: file too big\n", fn));
	(errno == EINTR && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == EISDIR && lp_dprintf(2, SHELL_NAME": %s: Is a directory\n", fn));
	(errno == ELOOP && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == EMFILE && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENAMETOOLONG && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENFILE && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENODEV && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENOENT && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENOMEM && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENOSPC && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENOTDIR && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == ENXIO && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == EPERM && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == EROFS && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	(errno == EROFS && lp_dprintf(2, SHELL_NAME": %s: Perm denied\n", fn));
	(errno == ETXTBSY && lp_dprintf(2, SHELL_NAME":%s:Perm denied\n", fn));
	(errno == EWOULDBLOCK && lp_dprintf(2, SHELL_NAME": %s: error\n", fn));
	return (true);
}

static void	replace_fd(int *fd_dest, int new_fd)
{
	if (*fd_dest != -1)
		close(*fd_dest);
	*fd_dest = new_fd;
}

bool	open_and_replace(t_redir_data redir, t_node *p_cmd)
{
	int	file_fd;

	file_fd = -1;
	errno = 0;
	if (redir.type == REDIR_IN)
		file_fd = open(redir.file_name, O_RDONLY);
	if (redir.type == REDIR_OUT)
		file_fd = open(redir.file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (redir.type == REDIR_OUT_APPEND)
		file_fd = open(redir.file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (!p_cmd)
	{
		(void)(!check_print_errors(redir.file_name)
			&& file_fd != -1 && (close(file_fd), 1));
		return (true);
	}
	if (check_print_errors(redir.file_name))
		return (false);
	if (redir.type == REDIR_OUT || redir.type == REDIR_OUT_APPEND)
		replace_fd(&((t_cmd_data *)p_cmd->data)->fd_out, file_fd);
	if (redir.type == REDIR_IN)
		replace_fd(&((t_cmd_data *)p_cmd->data)->fd_in, file_fd);
	return (true);
}

bool	is_last_heredoc(t_node *node)
{
	while (node && node->type != CMD_NODE)
	{
		if (node->type == HEREDOC_NODE)
			return (false);
		node = ((t_redir_data *)node->data)->next;
	}
	return (true);
}

bool	open_redirs(t_node *node, t_node *p_cmd, t_array *pids)
{
	t_redir_data	*redir;

	while (node && node->type != CMD_NODE)
	{
		if (node->type == HEREDOC_NODE)
		{
			if (p_cmd && is_last_heredoc(((t_heredoc_data *)node->data)->next)
				&& !array_pushback(pids, (pid_t []){pipe_heredoc_and_cmd(
						*(t_heredoc_data *)node->data, p_cmd->data)}))
				return (false);
			node = ((t_heredoc_data *)node->data)->next;
			continue ;
		}
		redir = (t_redir_data *)node->data;
		if (!expand_unquote(&redir->file_name))
			return (false);
		if (!open_and_replace(*redir, p_cmd))
			return (false);
		node = redir->next;
	}
	if (!node)
		return (false);
	return (true);
}
