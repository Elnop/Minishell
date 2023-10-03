/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elnop <elnop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 06:04:28 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/30 11:50:23 by elnop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_cmd(t_cmd_data data)
{
	size_t	i;

	lp_dprintf(2, "====> EXEC CMD <====\n");
	lp_dprintf(2, "fd_in: %d\n", data.fd_in);
	lp_dprintf(2, "fd_out: %d\n", data.fd_out);
	lp_dprintf(2, "args:\n");
	i = 0;
	while (((char **)data.args)[i])
		lp_dprintf(2, " %s\n", ((char **)data.args)[i++]);
	if (!lp_strncmp(((char **)data.args)[0], "false", 5))
		return (1);
	return (0);
}
