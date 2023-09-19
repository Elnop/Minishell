/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_to_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:41:27 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/20 00:48:42 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_array	get_cmd_args(t_array words, size_t *i)
{
	t_array	buff;

	buff = array_new(array_size(words), sizeof(char **), copy_str, destroy_str);
	while (*i < array_size(words) && !is_operator(((char **)words)[*i]))
	{
		array_pushback(&buff, (char **)words + *i);
		(*i)++;
	}
	array_pushback(&buff, NULL);
	return (buff);
}

bool	add_cmd_token(t_array *p_tokens, t_array words, size_t *i)
{
	t_token	token;

	token.infos = malloc(sizeof(t_cmd_infos));
	((t_cmd_infos *)token.infos)->fd_in = 0;
	((t_cmd_infos *)token.infos)->fd_out = 0;
	((t_cmd_infos *)token.infos)->cmd_args = get_cmd_args(words, i);
	array_pushback(p_tokens, &token);
	return (true);
}

t_array	words_to_tokens(t_array words)
{
	t_array	tokens;
	size_t	i;

	tokens = array_new(array_size(words), sizeof(t_token), NULL, NULL);
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < array_size(words))
	{
		if (!add_cmd_token(&tokens, words, &i))
			return (array_free(tokens), NULL);
	}
	return (tokens);
}
