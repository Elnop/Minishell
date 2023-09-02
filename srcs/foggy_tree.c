/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foggy_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 08:16:03 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/02 08:43:56 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*input_to_fggtr(char *line)
{
	char	**words;
	size_t	words_index;

	line[lp_strlen(line) - 1] = 0;
	words = lp_pool_split(line, " \t\r\v\f");
	words_index = 0;
	while (words[words_index])
	{
		lp_printf("%s\n", words[words_index]);
		words_index++;
	}
	while (words_index)
	{
		words_index--;
		free(words[words_index]);
	}
	free(words);
	return (NULL);
}
