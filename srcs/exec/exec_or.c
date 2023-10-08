/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:01:18 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/07 21:49:59 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_or(t_node_links data)
{
	int	code;

	code = exec(data.left);
	if (code)
		return (exec(data.right));
	return (code);
}
