/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_grb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 07:20:57 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/03 21:38:34 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*add_grb(void *ptr, t_garbage_item_type type)
{
	if (!ptr || !array_pushback(
			&get_app_data()->garbage, &(t_garbage_item){ptr, type}))
		return (NULL);
	return (ptr);
}
