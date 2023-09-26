/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 04:44:31 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 23:12:25 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	redir_data_copy(void *pelem, void *dest)
{
	*(t_redir_data *)dest = (t_redir_data){
		((t_redir_data *)pelem)->type,
		lp_strdup(((t_redir_data *)pelem)->file_name)};
	return (true);
}

static bool	is_redir_operator(char *word)
{
	return (!lp_strncmp(word, "<", 2) || !lp_strncmp(word, ">", 2)
		|| !lp_strncmp(word, ">>", 3));
}

bool	has_redir_operator(char **words)
{
	while (*words && !is_operator(*words))
		words++;
	if (*words && is_redir_operator(*words))
		return (true);
	return (false);
}

static bool	push_next_redir(t_array	*p_nodes, char **words, size_t i)
{
	if (!lp_strncmp(words[i], "<", 2))
	{
		if (!array_pushback(p_nodes,
				&(t_redir_data){REDIR_IN, words[i + 1]}))
			return (array_free(*p_nodes), false);
		array_remove((t_array)words, i);
		array_remove((t_array)words, i);
	}
	else if (!lp_strncmp(words[i], ">", 2))
	{
		if (!array_pushback(p_nodes,
				&(t_redir_data){REDIR_OUT, words[i + 1]}))
			return (array_free(*p_nodes), false);
		array_remove((t_array)words, i);
		array_remove((t_array)words, i);
	}
	else if (!lp_strncmp(words[i], ">>", 2))
	{
		if (!array_pushback(p_nodes,
				&(t_redir_data){REDIR_OUT_APPEND, words[i + 1]}))
			return (array_free(*p_nodes), false);
		array_remove((t_array)words, i);
		array_remove((t_array)words, i);
	}
	return (true);
}

t_array	make_redirs_array(char **words)
{
	t_array	nodes;
	size_t	i;

	nodes = array_new(1, sizeof(t_redir_data), redir_data_copy,
			redir_data_destructor);
	while (has_redir_operator(words))
	{
		i = 0;
		while (words[i] && !is_operator(words[i]))
			i++;
		if (!words[i] || !is_redir_operator(words[i]))
			return (nodes);
		if (is_redir_operator(words[i])
			&& (!words[i + 1] || is_operator(words[i + 1])))
			return (array_free(nodes), NULL);
		if (!push_next_redir(&nodes, words, i))
			return (NULL);
	}
	return (nodes);
}
