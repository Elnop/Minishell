/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:18:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/07 00:54:37 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	copy_str(void *pelem, void *dest)
{
	*(char **)dest = lp_strdup(*(char **)pelem);
	if (!dest)
		return (false);
	return (true);
}

void	destroy_str(void *pelem)
{
	free(*(char **)pelem);
}