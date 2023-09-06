/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/06 19:10:36 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_valid_line(char	*line)
{
	return (
		line
		&& lp_strlen(line)
		&& !(
			lp_strlen(line) - 1
			&& !lp_strncmp(line, "exit", lp_strlen(line) - 1)
		)
	);
}

int	start(void)
{
	char	*line;

	line = readline("Minish: ");
	while (line)
	{
		input_to_fggtr(line);
		free(line);
		line = readline("Minish: ");
	}
	return (true);
}
