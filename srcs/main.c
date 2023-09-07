/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:12:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/07 21:22:58 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_array	strtab_to_array(char **str_tab)
{
	t_array	my_env;

	my_env = array_new(10, sizeof(char *), copy_str, destroy_str);
	while (*str_tab)
	{
		array_pushback(&my_env, str_tab);
		str_tab++;
	}
	return (my_env);
}

bool	init_app(t_app	*app, char **env)
{
	app->env = strtab_to_array(env);
	if (!app->env)
		return (false);
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_app	app;

	(void)ac;
	(void)av;
	if (!init_app(&app, env))
		return (0);
	return (start(&app));
}
