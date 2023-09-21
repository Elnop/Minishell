/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_to_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:41:27 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/20 02:13:16 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_logical_operators	has_logical_operator(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
	{
		if (!lp_strncmp(words[i], "&&", 2))
			return (AND_OPERATOR);
		if (!lp_strncmp(words[i], "||", 2))
			return (OR_OPERATOR);
		i++;
	}
	return (NO_OPERATOR);
}

t_node	*words_to_tree(char **words)
{
	t_logical_operators	next_logical_operator;

	next_logical_operator = has_logical_operator(words);
	if (next_logical_operator == NO_OPERATOR)
		return (make_cmd_node(words)); // replace by pipeline
	if (next_logical_operator == AND_OPERATOR)
		return (make_and_node(words));
	if (next_logical_operator == OR_OPERATOR)
		return (make_or_node(words));
	return (NULL);
}
