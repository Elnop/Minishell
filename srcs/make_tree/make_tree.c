/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:41:40 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/20 02:04:51 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*make_tree(char *line)
{
	t_array	words;
	t_node	*first_node;

	if (!line)
		return (NULL);
	words = line_to_words(line);
	if (!words)
		return (lp_dprintf(2, "Tokenify error\n"), NULL);
	if (!*(char **)words)
		return (NULL);
	// check sig ctr c dans appdata return NULL
	first_node = words_to_tree(words);
	if (!first_node)
		return ((void)lp_dprintf(2, "Syntux error\n"), NULL);
	array_free(words);
	return (first_node);
}
