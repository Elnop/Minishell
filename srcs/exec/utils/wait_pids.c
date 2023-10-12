/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:20:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/12 14:14:11 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_sigs(t_array	pids)
{
	if ((get_app_data()->lastcode != 130 && get_app_data()->sig_code == 130))
		write(2, "\n", 1);
	if ((get_app_data()->lastcode != 131 && get_app_data()->sig_code == 131))
		write(2, "Quit (core doubpt)\n", 20);
	if (array_size(pids) == 1 && get_app_data()->sig_code)
	{
		get_app_data()->lastcode = get_app_data()->sig_code;
		get_app_data()->sig_code = 0;
	}
}

int	wait_pids(t_array *pids)
{
	int		status;
	size_t	i;

	status = 0;
	i = 0;
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
	check_sigs(pids);
	return (get_app_data()->lastcode);
}
