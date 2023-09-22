/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:23:05 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/21 23:04:19 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_and(t_node_links data)
{
	int	code;

	printf(GREEN"====> AND OPERATOR <====\n"COLOR_OFF);
	printf(GREEN"====> AND LEFT \n"COLOR_OFF);
	code = print_tree(*(t_node *)data.left);
	printf(GREEN"====> AND RIGHT\n"COLOR_OFF);
	if (!code)
		code = print_tree(*(t_node *)data.right);
	else
		printf("no exec\n");
	return (code);
}

int	print_or(t_node_links data)
{
	int	code;

	printf(YELLOW"====> OR OPERATOR <====\n"COLOR_OFF);
	printf(YELLOW"====> OR LEFT\n"COLOR_OFF);
	code = print_tree(*(t_node *)data.left);
	printf(YELLOW"====> OR RIGHT\n"COLOR_OFF);
	if (code)
		code = print_tree(*(t_node *)data.right);
	else
		printf("no exec\n"COLOR_OFF);
	return (code);
}

int	print_pipe(t_node_links data)
{
	printf(BLUE"====> PIPE OPERATOR <====\n"COLOR_OFF);
	printf(BLUE"====> PIPE LEFT\n"COLOR_OFF);
	print_tree(*(t_node *)data.left);
	printf(BLUE"====> PIPE RIGHT\n"COLOR_OFF);
	return (print_tree(*(t_node *)data.right));
}

int	print_cmd(t_cmd_data data)
{
	size_t	i;

	printf("====> EXEC CMD <====\n");
	printf("fd_in: %d\n", data.fd_in);
	printf("fd_out: %d\n", data.fd_out);
	printf("args:\n");
	i = 0;
	while (((char **)data.args)[i])
		printf(" %s\n", ((char **)data.args)[i++]);
	if (!lp_strncmp(((char **)data.args)[0], "false", 5))
		return (1);
	return (0);
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
		return (print_pipe(*(t_node_links *)node.data));
	printf("BOG BOG BOG BOG BOG BOG BOG BOG BOG BOG BOG BOG\n");
	return (1);
}
