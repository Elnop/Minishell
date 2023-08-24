/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:12:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/08/22 19:45:12 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	init_app(t_app	*app, char **env)
{
	app->env = env_to_array(env);
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_app	app;

	(void)ac;
	(void)av;
	init_app(&app, env);
	return (0);
}
