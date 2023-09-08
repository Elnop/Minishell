/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:19:21 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/08 17:16:49 by lperroti         ###   ########.fr       */
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

char	*get_next_word(char **p_line)
{
	char	*word;
	size_t	i;

	if (**p_line == '\'')
		word = get_simple_quote(p_line);
	else if (**p_line == '"')
		word = get_double_quote(p_line);
	else
	{
		i = 0;
		while ((*p_line)[i] && !lp_strchr(SPACERS, (*p_line)[i]))
			i++;
		word = lp_substr(*p_line, 0, i);
		*p_line += i;
	}
	return (word);
}
