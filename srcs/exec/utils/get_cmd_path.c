/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 01:08:37 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/09 21:43:33 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_strtab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

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

static char	*test_env_paths(char *name)
{
	char	**path_list;
	size_t	i;
	char	*cmd_path;
	char	*tmp;

	path_list = get_path_list();
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		cmd_path = lp_strdup(path_list[i]);
		tmp = lp_strjoin("/", name);
		lp_strcat(&cmd_path, tmp);
		free(tmp);
		if (!access(cmd_path, F_OK))
			return (free_strtab(path_list), cmd_path);
		free(cmd_path);
		i++;
	}
	free_strtab(path_list);
	return (NULL);
}

char	*get_cmd_path(char *name)
{
	if (!name || !*name || !lp_strncmp(name, ".", 2)
		|| !lp_strncmp(name, "/", 2) || !lp_strncmp(name, "./", 3))
		return (NULL);
	if (lp_strlen(name) > 2 && !access(name, F_OK))
		return (lp_strdup(name));
	return (test_env_paths(name));
}
