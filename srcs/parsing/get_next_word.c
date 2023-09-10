/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:19:21 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/10 20:55:40 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_quoted(char **p_line, char quote)
{
	size_t	i;
	char	*word;

	i = 0;
	*p_line += 1;
	while ((*p_line)[i] && (*p_line)[i] != quote)
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

static char	*expand(char *str, char next_char)
{
	t_array	tmp_buff;
	char	*new_str;

	if (!str)
		return (NULL);
	tmp_buff = array_new(lp_strlen(str), sizeof(char), NULL, NULL);
	if (!tmp_buff || !array_pushback_tab(&tmp_buff, str, lp_strlen(str) + 1))
		return (NULL);
	if (next_char && ((char *)tmp_buff)[array_size(tmp_buff) - 2] == '$')
		array_remove(tmp_buff, array_size(tmp_buff) - 2);
	new_str = lp_strdup(tmp_buff);
	free(str);
	array_free(tmp_buff);
	return (new_str);
}

char	*fusion_strs(char *s1, char *s2)
{
	char	*fusion;

	fusion = lp_strjoin(s1, s2);
	if (!fusion)
		return (NULL);
	free(s1);
	free(s2);
	return (fusion);
}

char	*get_next_word(char **p_line)
{
	char	*word;
	char	*sub_word;

	word = NULL;
	while (**p_line && !lp_strchr(SPACERS, **p_line))
	{
		if (**p_line == '\'')
			sub_word = get_quoted(p_line, '\'');
		else if (**p_line == '"')
		{
			sub_word = get_quoted(p_line, '\"');
			sub_word = expand(sub_word, **p_line);
		}
		else
		{
			sub_word = get_word(p_line);
			sub_word = expand(sub_word, **p_line);
		}
		if (!sub_word)
			return (NULL);
		word = fusion_strs(word, sub_word);
	}
	return (word);
}
