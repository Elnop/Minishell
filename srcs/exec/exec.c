/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 23:11:05 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/22 02:47:46 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd(t_cmd_data data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(((char **)data.args)[0]);
	if (!cmd_path)
		return (printf(RED"%s: '%s': command not found\n"COLOR_OFF,
				(char *)SHELL_NAME, ((char **)data.args)[0]), 127);
	printf("---> %p\n", cmd_path);
	// exec cmd
	return (1);
}

int	exec(t_node *node)
{
	if (node->type == CMD_NODE)
		exec_cmd(*(t_cmd_data *)node->data);
	return (1);
}
