/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titilamenace <titilamenace@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 01:53:56 by titilamenac      ###   ########.fr       */
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
		signal_handler(1);
		first_node = make_tree(line);
		print_tree(*first_node);
		/*if (first_node)
		{
			if (get_app_data()->debug)
				print_tree(*first_node);
			else
				get_app_data()->lastcode = exec(first_node);
		}
		else
			printf("Syntux error\n");*/
		free(line);
	}
}
