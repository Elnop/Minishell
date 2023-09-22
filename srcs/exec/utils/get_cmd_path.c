/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 01:08:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/22 23:54:40 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**get_path_list(void)
{
	size_t	i;
	t_array	env;

	env = get_app_data()->env;
	i = 0;
	while (((char **)env)[i] && lp_strncmp(((char **)env)[i], "PATH=", 5))
		i++;
	if (!((char **)env)[i])
		return (NULL);
	return (lp_split(((char **)env)[i], ':'));
}

char	*get_cmd_path(char *name)
{
	char	**path_list;
	size_t	i;
	char	*cmd_path;

	if (!name || !*name)
		return (NULL);
	path_list = get_path_list();
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		cmd_path = path_list[i];
		lp_strcat(&cmd_path, lp_strjoin("/", name));
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		i++;
	}
	return (NULL);
}
