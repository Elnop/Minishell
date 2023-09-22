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

t_array	make_tree(char *line)
{
	t_array	words;
	t_node	*first_node;

	if (!line)
		return (NULL);
	words = line_to_words(line);
	first_node = words_to_tree(words);
	print_tree(*first_node);
	return (first_node);
}
