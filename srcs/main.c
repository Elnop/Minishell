/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:12:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/02 07:42:35 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// bool	init_app(t_app	*app, char **env)
// {
// 	app->env = env_to_array(env);
// 	return (true);
// }

int	main(int ac, char **av, char **env)
{
	(void)env;
	// t_app	app;
	(void)ac;
	(void)av;
	//init_app(&app, env);
	return (start());
}