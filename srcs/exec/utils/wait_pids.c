/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:20:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 03:04:10 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	wait_pids(t_array *pids)
{
	int		status;
	size_t	i;

	status = 0;
	i = 0;
	if (!pids)
		return (0);
	while (i < array_size(pids))
	{
		if (((pid_t *)pids)[i] != -1)
			waitpid(((pid_t *)pids)[i], &status, 0);
		i++;
	}
	array_free(pids);
	return (WIFEXITED(status) & WEXITSTATUS(status));
}
