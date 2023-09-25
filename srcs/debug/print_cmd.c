/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 06:04:28 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 23:54:28 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_redirs(t_redir_data *redirs)
{
	size_t	i;

	i = 0;
	while (i < array_size((t_array)redirs))
	{
		if (redirs[i].type == REDIR_IN)
			lp_printf("- type=REDIR_IN, file=%s\n", redirs[i].file_name);
		if (redirs[i].type == REDIR_OUT)
			lp_printf("type=REDIR_OUT, file=%s\n", redirs[i].file_name);
		if (redirs[i].type == REDIR_OUT_APPEND)
			lp_printf("type=REDIR_OUT_APPEND, file=%s\n", redirs[i].file_name);
		i++;
	}
}

int	print_cmd(t_cmd_data data)
{
	size_t	i;

	lp_printf("====> EXEC CMD <====\n");
	lp_printf("fd_in: %d\n", data.fd_in);
	lp_printf("fd_out: %d\n", data.fd_out);
	lp_printf("redirs:\n");
	print_redirs((t_redir_data *)data.redirs);
	lp_printf("args:\n");
	i = 0;
	while (((char **)data.args)[i])
		lp_printf(" %s\n", ((char **)data.args)[i++]);
	if (!lp_strncmp(((char **)data.args)[0], "false", 5))
		return (1);
	return (0);
}
