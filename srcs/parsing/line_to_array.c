/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:17:00 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/10 03:45:35 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_white_spaces(char **p_line)
{
	while (**p_line && lp_strchr(SPACERS, **p_line))
		(*p_line)++;
}

static bool	push_next_word(t_array *p_words_array, char **p_line)
{
	char	*word;

	word = get_next_word(p_line);
	if (!word)
		return (false);
	if (!array_pushback(p_words_array, &word))
		return (false);
	free(word);
	return (true);
}

t_array	line_to_array(char *line)
{
	t_array	words;

	words = array_new(100, sizeof(char *), copy_str, destroy_str);
	if (!words)
		return (NULL);
	while (*line)
	{
		skip_white_spaces(&line);
		if (!*line)
			return (words);
		if (!push_next_word(&words, &line))
			return (array_free(words), NULL);

	}
	return (words);
}
