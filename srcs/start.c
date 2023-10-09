/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/07 21:43:07 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	new_input(char **line)
{
	signal_handler(0);
	*line = readline(BICYAN SHELL_NAME": "COLOR_OFF);
	while (*line && !**line)
	{
		free(*line);
		*line = readline(BICYAN SHELL_NAME": "COLOR_OFF);
	}
	if (!*line)
		return (false);
	add_history(*line);
	return (true);
}

void	start(void)
{
	char	*line;
	t_node	*first_node;

	while (new_input(&line))
	{
		first_node = make_tree(line);
		if (get_app_data()->here_sigint)
		{
			dup2(get_app_data()->save_stdin, 0);
			dup2(get_app_data()->save_stdout, 1);
			get_app_data()->here_sigint = 0;
		}
		else if (first_node)
		{
			if (get_app_data()->debug)
				print_tree(*first_node);
			else
				get_app_data()->lastcode = exec(first_node);
		}
		free(line);
		clean_garbage();
	}
}
