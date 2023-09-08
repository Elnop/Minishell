/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:06 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/08 16:30:45 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_array	env_array)
{
	size_t	i;

	i = 0;
	while (i < array_size(env_array))
		lp_putendl_fd(((char **)env_array)[i++], 1);
}
