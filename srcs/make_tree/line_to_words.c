/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:17:00 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/07 21:43:58 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long	count_quoted(char *line)
{
	if (*line == '\'')
	{
		if (!lp_strchr(line + 1, '\''))
			return (-1);
		return (lp_strchr(line + 1, '\'') - line + 1);
	}
	else if (*line == '"')
	{
		if (!lp_strchr(line + 1, '"'))
			return (-1);
		return (lp_strchr(line + 1, '"') - line + 1);
	}
	else if (*line == '(')
	{
		if (!lp_strchr(line + 1, ')'))
			return (-1);
		return (lp_strchr(line + 1, ')') - line + 1);
	}
	return (0);
}

static char	*get_next_word(char *line)
{
	size_t	wl;
	long	quoted_sequence;

	if (!line)
		return (NULL);
	wl = is_operator(line);
	if (wl)
		return (lp_substr(line, 0, wl));
	while (line[wl] && !lp_strchr(SPACERS, line[wl]) && !is_operator(line + wl))
	{
		quoted_sequence = count_quoted(line + wl);
		if (quoted_sequence == -1)
			return ((void)lp_dprintf(2, "Parsing Error: Quote not closed\n"),
				NULL);
		else if (quoted_sequence)
			wl += quoted_sequence;
		else
			wl++;
	}
	return (lp_substr(line, 0, wl));
}

static void	skip_white_spaces(char **p_line)
{
	while (**p_line && lp_strchr(SPACERS, **p_line))
		(*p_line)++;
}

static bool	push_next_word(t_array *p_words_array, char *line)
{
	char	*word;

	word = get_next_word(line);
	if (!word)
		return (false);
	if (!array_pushback(p_words_array, &word))
		return (false);
	free(word);
	return (true);
}

t_array	line_to_words(char *line)
{
	t_array	words;

	words = array_new(100, sizeof(char *), copy_str, destroy_str);
	if (!words)
		return (NULL);
	while (line && *line)
	{
		skip_white_spaces(&line);
		if (!*line)
			break ;
		if (!push_next_word(&words, line))
			return (array_free(words), NULL);
		line += lp_strlen(((char **)words)[array_size(words) - 1]);
	}
	if (!array_pushback(&words, NULL))
		return (array_free(words), NULL);
	return (words);
}
