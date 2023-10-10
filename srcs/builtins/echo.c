/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:56:42 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/10 03:31:09 by tschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	builtin_echo(char **args)
{
	int	i;
	int	n_arg;

	i = 1;
	n_arg = 0;
	if (count_args(args) > 1)
	{
		while (args[i] && lp_strncmp(args[i], "-n", 2) == 0)
		{
			n_arg = 1;
			i++;
		}
		while (args[i])
		{
			lp_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] == '\0')
				write(1, " ", 1);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (n_arg == 0)
		write(1, "\n", 1);
	return (0);
}
