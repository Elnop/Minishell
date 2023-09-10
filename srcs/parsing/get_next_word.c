/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:19:21 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/10 04:00:40 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_simple_quote(char **p_line)
{
	size_t	i;
	char	*word;

	i = 0;
	*p_line += 1;
	while ((*p_line)[i] && (*p_line)[i] != '\'')
		i++;
	if (!(*p_line)[i])
		return (NULL);
	word = lp_substr(*p_line, 0, i);
	*p_line += i + 1;
	return (word);
}

static char	*get_double_quote(char **p_line)
{
	size_t	i;
	char	*word;

	i = 0;
	*p_line += 1;
	while ((*p_line)[i] && (*p_line)[i] != '\"')
		i++;
	if (!(*p_line)[i])
		return (NULL);
	word = lp_substr(*p_line, 0, i);
	*p_line += i + 1;
	return (word);
}

static char	*get_word(char **p_line)
{
	char	*word;
	size_t	i;

	i = 0;
	while ((*p_line)[i] && !lp_strchr(SPACERS"\"'", (*p_line)[i]))
		i++;
	word = lp_substr(*p_line, 0, i);
	*p_line += i;
	return (word);
}

char	*get_next_word(char **p_line)
{
	char	*word;
	char	*sub_word;
	char	*tmp_word;

	word = NULL;
	while (**p_line && !lp_strchr(SPACERS, **p_line))
	{
		if (**p_line == '\'')
			sub_word = get_simple_quote(p_line);
		else if (**p_line == '"')
			sub_word = get_double_quote(p_line);
		else
			sub_word = get_word(p_line);
		if (!sub_word)
			return (NULL);
		tmp_word = lp_strjoin(word, sub_word);
		if (!tmp_word)
			return (NULL);
		free(word);
		free(sub_word);
		word = tmp_word;
	}
	return (word);
}
