/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:06 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/03 19:26:46 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(char **args)
{
	size_t		i;
	const char	**env = get_app_data()->env;

	(void)args;
	i = 0;
	while (i < array_size(env) - 1)
	{
		if (lp_strchr((char *)env[i], '='))
			lp_putendl_fd((char *)env[i], 1);
		i++;
	}
	return (0);
}
