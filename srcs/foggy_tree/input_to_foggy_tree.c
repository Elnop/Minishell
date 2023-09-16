/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_foggy_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:30:00 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/16 06:21:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_str_array(char **words_list)
{
	size_t	i;

	i = 0;
	lp_putstr_fd((char *)"==== WORD LIST ====", 2);
	lp_putstr_fd((char *)"\n", 2);
	while (i < array_size(words_list))
	{
		lp_putstr_fd(words_list[i], 2);
		lp_putstr_fd((char *)"\n", 2);
		i++;
	}
}

void	*input_to_foggy_tree(char *line, t_app *p_app)
{
	t_array	words;

	words = line_to_array(line);
	if (!words)
		return (NULL);
	print_str_array((char **)words);
	if (lp_str_isequal(*(char **)words, "env"))
		builtin_env(p_app->env);
	array_free(words);
	return (NULL);
}
