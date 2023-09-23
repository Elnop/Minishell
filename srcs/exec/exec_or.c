/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:01:18 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 04:07:27 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_or(t_node_links data)
{
	int	code;

	code = wait_pids(exec_pipeline((t_array)data.left->data));
	if (code)
		return (wait_pids(exec_pipeline((t_array)data.right->data)));
	return (code);
}
