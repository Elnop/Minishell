/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_app_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:06:51 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/03 21:00:14 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_app	*get_app_data(void)
{
	static t_app	data;

	return (&data);
}
