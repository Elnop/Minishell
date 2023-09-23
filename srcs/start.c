/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 03:45:47 by lperroti         ###   ########.fr       */
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
		if (!*line)
		{
			free(line);
			line = readline(SHELL_NAME": ");
			continue ;
		}
		first_node = make_tree(line);
		free(line);
		if (first_node)
		{
			//print_tree(*first_node);
			get_app_data()->lastcode = exec(first_node);
		}
		else
			printf("Syntux error\n");
		line = readline(SHELL_NAME": ");
	}
	return (true);
}
