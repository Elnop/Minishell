/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 16:35:39 by titilamenace     ###   ########.fr       */
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
	{
		printf("exit\n");
		return (false);
	}
	return (true);
}

void	start(void)
{
	char	*line;
	t_node	*first_node;

	while (new_input(&line))
	{
		first_node = make_tree(line);
		if (first_node)
		{
			if (get_app_data()->debug)
				print_tree(*first_node);
			else
				get_app_data()->lastcode = exec(first_node);
		}
		else
			printf("Syntux error\n");
		free(line);
	}
}
