/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:18:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/26 06:58:19 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	copy_str(void *pelem, void *dest)
{
	if (!pelem || !*(char **)pelem)
		*(char **)dest = NULL;
	else
		*(char **)dest = lp_strdup(*(char **)pelem);
	return (true);
}

void	destroy_str(void *pelem)
{
	free(*(char **)pelem);
}

void	p_array_destroyer(void *pelem)
{
	array_free(*(t_array *)pelem);
}
