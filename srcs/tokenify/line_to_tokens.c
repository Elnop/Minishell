/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:41:40 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/20 00:42:27 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_str_array(char **words_list)
{
	size_t	i;

	i = 0;
	lp_putstr_fd((char *)"==== WORD LIST ====", 2);
	lp_putstr_fd((char *)"\n", 2);
	while (i < array_size(words_list))
	{
		lp_putstr_fd(words_list[i], 2);
		lp_putstr_fd((char *)"\n", 2);
		i++;
	}
}

t_array	line_to_tokens(char *line)
{
	t_array	words;
	t_array	tokens;

	if (!line)
		return (NULL);
	words = line_to_words(line);
	tokens = words_to_tokens(words);
	print_str_array((char **)words);
	return (tokens);
}
