/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/20 22:01:43 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start(t_app *p_app)
{
	char	*line;

	(void)p_app;
	line = readline("Minish: ");
	while (line)
	{
		line_to_tree(line);
		free(line);
		line = readline("Minish: ");
	}
	return (true);
}
