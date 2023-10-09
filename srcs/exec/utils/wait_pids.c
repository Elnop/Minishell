/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:20:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/07 21:48:23 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	wait_pids(t_array *pids)
{
	int		status;
	size_t	i;

	status = 0;
	i = 0;
	signal_handler(1);
	if (!pids)
		return (get_app_data()->lastcode);
	while (i < array_size(pids))
	{
		if (((pid_t *)pids)[i] != -1)
		{
			waitpid(((pid_t *)pids)[i], &status, 0);
			get_app_data()->lastcode = WEXITSTATUS(status);
		}
		i++;
	}
	if (array_size(pids) == 1 && get_app_data()->sig_code)
	{
		get_app_data()->lastcode = get_app_data()->sig_code;
		get_app_data()->sig_code = 0;
	}
	return (get_app_data()->lastcode);
}
