/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:56:17 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/12 02:31:41 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	arg_is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!lp_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

int	get_exit_code(char **args)
{
	if (!args[1])
		return (0);
	else if (arg_is_digit(args[1]))
		return (lp_atoi(args[1]));
	else
	{
		lp_putstr_fd("minishell: exit: ", STDERR_FILENO);
		lp_putstr_fd(args[1], STDERR_FILENO);
		lp_putstr_fd(": numeric argument is required\n", STDERR_FILENO);
		return (255);
	}
}

int	builtin_exit(char **args)
{
	size_t	ac;
	int		test;

	ac = lp_strtab_size(args);
	if (ac > 2)
	{
		lp_putstr_fd("minishell : exit : too many arguments\n", STDERR_FILENO);
		get_app_data()->exit = true;
		return (EXIT_FAILURE);
	}
	test = get_exit_code(args);
	get_app_data()->exit = true;
	return (test);
}
