/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titilamenace <titilamenace@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/23 08:35:06 by lperroti         ###   ########.fr       */
=======
/*   Updated: 2023/09/23 17:17:13 by titilamenac      ###   ########.fr       */
>>>>>>> 65743376c329f451b1fb3541f5bcd81793b7ae27
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
	t_app	*app;
	char	*line;
	t_node	*first_node;

<<<<<<< HEAD
	app = get_app_data();
	while (!app->exit && new_input(&line))
=======
	
	while (new_input(&line))
>>>>>>> 65743376c329f451b1fb3541f5bcd81793b7ae27
	{
		signal_handler(1);
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
