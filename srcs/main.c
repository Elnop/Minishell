/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:12:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/08 00:50:02 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// if (!isatty(0) || !isatty(1) || !isatty(2))
// {
// 	lp_putstr_fd("stdin, stdout or stderr have been changed\n", 2);
// 	return (ENOTTY);
// }

char	*lp_strjoin_tab(char	**tab, char *splitter)
{
	char	*buff;

	if (!tab)
		return (NULL);
	buff = lp_strdup(*tab);
	while (buff && *(++tab))
		if (!lp_strcat(&buff, splitter) || !lp_strcat(&buff, *tab))
			return (NULL);
	return (buff);
}

int	exec_params(char **av)
{
	t_node	*first_node;
	char	*line;

	line = lp_strjoin_tab(av + 1, " ");
	if (!line)
	{
		lp_printf(RED"Subshell error"COLOR_OFF);
		return (1);
	}
	first_node = make_tree(line);
	free(line);
	if (first_node)
		get_app_data()->lastcode = exec(first_node);
	destroy_app();
	return (get_app_data()->lastcode);
}

int	main(int ac, char **av, char **env)
{
	int	last_code;

	if (!init_app(ac, av, env))
		return (1);
	if (ac > 1 && ft_strcmp(av[1], "--debug"))
		return (exec_params(av));
	start();
	last_code = get_app_data()->lastcode;
	destroy_app();
	if (isatty(0))
		lp_putendl_fd("exit", 1);
	return (last_code);
}
