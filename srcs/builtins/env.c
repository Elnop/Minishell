/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:06 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/16 02:36:06 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(char **env)
{
	size_t	i;

	i = 0;
	while (i < array_size(env))
		lp_putendl_fd(env[i++], 1);
}
