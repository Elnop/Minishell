/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:42:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/02 08:33:10 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	line = get_next_line(0);
	while (is_valid_line(line))
	{
		input_to_fggtr(line);
		free(line);
		line = get_next_line(0);
	}
	return (true);
}
