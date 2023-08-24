/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:49:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/08/22 17:50:08 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

typedef struct s_fork_cmd_params {
	char	*cmd_name;
	char	**cmd_args;
	char	**envp;
	int		close_fd;
	int		fd_in;
	int		fd_out;
}	t_fork_cmd_params;

#endif