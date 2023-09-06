/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:17:00 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/07 01:27:49 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_str_array(t_array words_array)
{
	size_t	i;

	i = 0;
	lp_putstr_fd("==== WORD LIST ====", 2);
	lp_putstr_fd("\n", 2);
	while (i < array_size(words_array))
	{
		lp_putchar_fd('"', 2);
		lp_putstr_fd(((char **)words_array)[i], 2);
		lp_putchar_fd('"', 2);
		lp_putstr_fd("\n", 2);
		i++;
	}
}

t_array	line_to_array(char *line)
{
	t_array	words_array;
	size_t	i;
	char	*str_tmp;

	words_array = array_new(10, sizeof(char *), copy_str, destroy_str);
	if (!words_array)
		return (NULL);
	while (*line)
	{
		while (*line && lp_strchr(SPACERS, *line))
			line++;
		i = 0;
		while (line[i] && line[i] && !lp_strchr(SPACERS, line[i]))
			i++;
		str_tmp = lp_substr(line, 0, i);
		if (!str_tmp)
			return (NULL);
		if (!array_pushback(&words_array, &str_tmp))
			return (NULL);
		free(str_tmp);
		line += i;
	}
	print_str_array(words_array);
	return (words_array);
}
