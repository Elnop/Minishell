/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:15:38 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 04:07:34 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_and(t_node_links data)
{
	int	code;

	code = wait_pids(exec_pipeline((t_array)data.left->data));
	if (!code)
		return (wait_pids(exec_pipeline((t_array)data.right->data)));
	return (code);
}
