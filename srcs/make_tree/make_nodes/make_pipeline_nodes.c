/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 05:21:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/21 06:03:30 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	has_pipe_operator(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
		if (!lp_strncmp(words[i++], "|", 2))
			return (true);
	return (false);
}

t_node	*make_pipeline_nodes(char **words)
{
	if (has_pipe_operator(words))
		return (make_pipe_node(words));
	return (make_cmd_node(words));
}
