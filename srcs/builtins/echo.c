/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:56:42 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/13 17:27:47 by lperroti         ###   ########.fr       */
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

void	print_echo(char **args, int *i)
{
	while (args[*i])
	{
		lp_putstr_fd(args[*i], 1);
		if (args[*i + 1] && args[*i][0] == '\0')
			write(1, " ", 1);
		if (args[*i + 1])
			write(1, " ", 1);
		(*i)++;
	}
}

bool	check_n_option(char **args, int *i)
{
	int	j;

	j = 1;
	while (args[*i] && args[*i][j])
	{
		if (args[*i][j] != 'n')
			return (false);
		j++;
	}
	return (true);
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
			if (!check_n_option(args, &i))
				break ;
			n_arg = 1;
			i++;
		}
		print_echo(args, &i);
	}
	if (n_arg == 0)
		write(1, "\n", 1);
	return (0);
}
