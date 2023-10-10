/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:15:38 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/10 04:46:48 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_and(t_node_links data)
{
	get_app_data()->lastcode = exec(data.left);
	if (get_app_data()->sig_code)
	{
		get_app_data()->lastcode = get_app_data()->sig_code;
		get_app_data()->sig_code = 0;
	}
	if (!get_app_data()->lastcode)
		return (exec(data.right));
	return (get_app_data()->lastcode);
}
