/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:12:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 16:44:35 by titilamenace     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	int	last_code;

	if (!init_app(ac, av, env))
		return (1);
	signal_handler();
	start();
	last_code = get_app_data()->lastcode;
	destroy_app();
	return (last_code);
}
