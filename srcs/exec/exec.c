/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 23:11:05 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/12 08:20:15 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(t_node *node)
{
	if (node->type == PIPELINE_NODE)
		wait_pids(exec_pipeline((t_array)node->data));
	if (node->type == AND_NODE)
		get_app_data()->lastcode = exec_and(*(t_node_links *)node->data);
	if (node->type == OR_NODE)
		get_app_data()->lastcode = exec_or(*(t_node_links *)node->data);
	return (get_app_data()->lastcode);
}
