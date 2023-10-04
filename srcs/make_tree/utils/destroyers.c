/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 07:10:19 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/04 15:51:18 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	redir_data_destructor(void	*pelem)
{
	t_redir_data	*data;

	data = (t_redir_data *)(*(t_node **)pelem)->data;
	free(data->file_name);
	free(data);
	free(*(t_node **)pelem);
}

void	destroy_cmd(void *pelem)
{
	t_cmd_data	*data;

	data = (t_cmd_data *)(*(t_node **)pelem)->data;
	array_free(data->args);
	free(data);
	free(*(t_node **)pelem);
}

void	destroy_pipeline(void *pelem)
{
	array_free((t_array)(*(t_node **)pelem)->data);
	free(*(t_node **)pelem);
}

void	destroy_tree_node(void *pelem)
{
	if ((*(t_node **)pelem)->type == CMD_NODE)
		destroy_cmd(pelem);
	else if ((*(t_node **)pelem)->type == PIPE_NODE)
		destroy_pipeline(pelem);
	else if ((*(t_node **)pelem)->type == AND_NODE
		|| (*(t_node **)pelem)->type == OR_NODE)
	{
		free((*(t_node **)pelem)->data);
		free(*(t_node **)pelem);
	}
	else if ((*(t_node **)pelem)->type == REDIR_NODE)
		redir_data_destructor(pelem);
}
