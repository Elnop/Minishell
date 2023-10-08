/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:15:38 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/07 21:51:14 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_and(t_node_links data)
{
	int	code;

	code = exec(data.left);
	if (!code)
		return (exec(data.right));
	return (code);
}
