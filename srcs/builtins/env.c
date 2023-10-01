/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:06 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/28 21:15:56 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	builtin_env(t_cmd_data data)
{
	size_t		i;
	const char	**env = get_app_data()->env;

	(void)data;
	i = 0;
	while (i < array_size(env))
		lp_putendl_fd((char *)env[i++], 1);
	return (-1);
}
