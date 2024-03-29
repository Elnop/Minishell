/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:23:05 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/07 23:40:28 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_and(t_node_links data)
{
	int	code;

	lp_printf(GREEN"====> AND OPERATOR <====\n"COLOR_OFF);
	lp_printf(GREEN"====> AND LEFT \n"COLOR_OFF);
	code = print_tree(*(t_node *)data.left);
	lp_printf(GREEN"====> AND RIGHT\n"COLOR_OFF);
	if (!code)
		code = print_tree(*(t_node *)data.right);
	else
		lp_printf("no exec\n");
	return (code);
}

int	print_or(t_node_links data)
{
	int	code;

	lp_printf(YELLOW"====> OR OPERATOR <====\n"COLOR_OFF);
	lp_printf(YELLOW"====> OR LEFT\n"COLOR_OFF);
	code = print_tree(*(t_node *)data.left);
	lp_printf(YELLOW"====> OR RIGHT\n"COLOR_OFF);
	if (code)
		code = print_tree(*(t_node *)data.right);
	else
		lp_printf("no exec\n"COLOR_OFF);
	return (code);
}

int	print_pipeline(t_array data)
{
	size_t	i;
	size_t	last_code;

	last_code = 0;
	lp_printf(BLUE"====> PIPELINE <====\n"COLOR_OFF);
	i = 0;
	while (i < array_size(data))
	{
		lp_printf(BLUE"====> ROW %u\n"COLOR_OFF, i);
		last_code = print_tree(*((t_node **)data)[i++]);
	}
	return (last_code);
}

int	print_redir(t_redir_data data)
{
	lp_printf(RED"====> REDIR <====\n"COLOR_OFF);
	if (data.type == REDIR_IN)
		lp_printf(RED"type : REDIR_IN\n"COLOR_OFF);
	if (data.type == REDIR_OUT)
		lp_printf(RED"type : REDIR_OUT\n"COLOR_OFF);
	if (data.type == REDIR_OUT_APPEND)
		lp_printf(RED"type : REDIR_OUT_APPEND\n"COLOR_OFF);
	lp_printf(RED"file_name : %s\n"COLOR_OFF, data.file_name);
	lp_printf(RED"↓↓↓ next ↓↓↓\n"COLOR_OFF);
	if (data.next)
		print_tree(*data.next);
	else
		lp_printf(RED"NULL\n"COLOR_OFF);
	return (0);
}

int	print_tree(t_node node)
{
	lp_printf("====> PRINT TREE <====\n");
	if (node.type == PIPELINE_NODE)
		return (print_pipeline((t_array)node.data));
	if (node.type == REDIR_NODE)
		return (print_redir(*(t_redir_data *)node.data));
	if (node.type == CMD_NODE)
		return (print_cmd(*(t_cmd_data *)node.data));
	if (node.type == AND_NODE)
		return (print_and(*(t_node_links *)node.data));
	if (node.type == OR_NODE)
		return (print_or(*(t_node_links *)node.data));
	if (node.type == HEREDOC_NODE)
	{
		lp_printf(RED"====> HERE_DOC <====\n"COLOR_OFF);
		lp_printf(RED"buffer : %s\n"COLOR_OFF,
			(*(t_heredoc_data *)node.data).buff);
		lp_printf(RED"↓↓↓ next ↓↓↓\n"COLOR_OFF);
		if ((*(t_heredoc_data *)node.data).next)
			print_tree(*(*(t_heredoc_data *)node.data).next);
		else
			lp_printf(RED"NULL\n"COLOR_OFF);
	}
	return (1);
}
