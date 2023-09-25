/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 05:25:00 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 03:41:47 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_array	strtab_to_array(char **str_tab)
{
	t_array	array;

	array = array_new(10, sizeof(char *), copy_str, destroy_str);
	while (*str_tab)
	{
		if (!array_pushback(&array, str_tab))
			return (array_free(array), NULL);
		str_tab++;
	}
	if (!array_pushback(&array, str_tab))
		return (array_free(array), NULL);
	return (array);
}

void	garbage_destroy(void *pelem)
{
	t_garbage_item	grbg_item;

	grbg_item = *(t_garbage_item *)pelem;
	if (grbg_item.type == GRBG_SIMPLE)
		free(grbg_item.ptr);
	if (grbg_item.type == GRBG_ARRAY)
		array_free((t_array)grbg_item.ptr);
	if (grbg_item.type == GRBG_TREE_NODE)
		destroy_tree_node(pelem);
}

bool	init_app(int ac, char **av, char **env)
{
	t_app	*app;

	app = get_app_data();
	app->env = strtab_to_array(env);
	if (!app->env)
		return (false);
	app->garbage = array_new(10, sizeof(t_garbage_item), NULL, garbage_destroy);
	if (!app->garbage)
		return (array_free(app->env), false);
	if (ac > 1 && !lp_strncmp(av[1], "--debug", 7))
		app->debug = true;
	return (true);
}

void	destroy_app(void)
{
	t_app	*app;

	app = get_app_data();
	array_free(app->garbage);
	array_free(app->env);
}

bool	clean_garbage(void)
{
	array_free(get_app_data()->garbage);
	(get_app_data()->garbage) = array_new(10, sizeof(t_garbage_item), NULL,
			garbage_destroy);
	if (!get_app_data()->garbage)
		return (false);
	return (true);
}
