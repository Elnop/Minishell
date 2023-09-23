/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 08:35:06 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	new_input(char **line)
{
	*line = readline(SHELL_NAME": ");
	while (*line && !**line)
	{
		free(*line);
		*line = readline(SHELL_NAME": ");
	}
	if (!*line)
		return (false);
	return (true);
}

void	start(void)
{
	t_app	*app;
	char	*line;
	t_node	*first_node;

	app = get_app_data();
	while (!app->exit && new_input(&line))
	{
		first_node = make_tree(line);
		if (first_node)
		{
			if (app->debug)
				print_tree(*first_node);
			else
				app->lastcode = exec(first_node);
		}
		else
			printf("Syntux error\n");
		free(line);
	}
}
