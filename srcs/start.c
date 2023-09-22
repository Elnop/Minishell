/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/22 02:02:12 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start(void)
{
	char	*line;
	t_node	*first_node;

	line = readline(SHELL_NAME": ");
	while (line)
	{
		first_node = make_tree(line);
		free(line);
		exec(first_node);
		line = readline(SHELL_NAME": ");
	}
	return (true);
}
