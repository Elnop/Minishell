/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:19:21 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/16 06:18:58 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long	count_quoted(char *line)
{
	size_t	wl;

	wl = 0;
	if (line[wl] == '\'')
	{
		wl++;
		while (line[wl] && line[wl] != '\'')
			wl++;
		if (!line[wl])
			return (-1);
		wl++;
	}
	else if (line[wl] == '"')
	{
		wl++;
		while (line[wl] && line[wl] != '"')
			wl++;
		if (!line[wl])
			return (-1);
		wl++;
	}
	return (wl);
}

char	*get_next_word(char *line)
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
			return ((void)printf("Parsing Error: Quote not closed\n"), NULL);
		else if (quoted_sequence)
			wl += quoted_sequence;
		else
			wl++;
	}
	return (lp_substr(line, 0, wl));
}
