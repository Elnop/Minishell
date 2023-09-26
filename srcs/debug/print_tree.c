/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:23:05 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 23:55:14 by lperroti         ###   ########.fr       */
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
		lp_printf(BLUE"====> PIPELINE CMD %lu\n"COLOR_OFF, i);
		last_code = print_tree(*((t_node **)data)[i]);
		i++;
	}
	return (last_code);
}

int	print_tree(t_node node)
{
	if (node.type == CMD_NODE)
		return (print_cmd(*(t_cmd_data *)node.data));
	if (node.type == AND_NODE)
		return (print_and(*(t_node_links *)node.data));
	if (node.type == OR_NODE)
		return (print_or(*(t_node_links *)node.data));
	if (node.type == PIPE_NODE)
		return (print_pipeline((t_array)node.data));
	lp_printf("BOG BOG BOG BOG BOG BOG BOG BOG BOG BOG BOG BOG\n");
	return (1);
}
