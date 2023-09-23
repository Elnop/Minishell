/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_garbage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 07:20:57 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 07:28:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	add_to_garbage(void *ptr, t_garbage_item_type type)
{
	return (
		!array_pushback(&get_app_data()->garbage, &(t_garbage_item){ptr, type})
		);
}
