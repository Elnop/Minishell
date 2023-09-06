/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:17:00 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/06 20:02:51 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_array	line_to_array(char *line)
{
	t_array	words_array;
	size_t	i;
	char	*str_tmp;

	words_array = array_new(1, sizeof(char *), copy_str, destroy_str);
	if (!words_array)
		return (NULL);
	i = 0;
	while (line)
	{
		while (lp_strchr(SPACERS, line[i]))
			line++;
		i = 0;
		while (line[i] && !lp_strchr(SPACERS, line[i]))
			i++;
		str_tmp = lp_substr(line, 0, i);
		if (!array_pushback(words_array, str_tmp))
			return (NULL);
	}
	return (words_array);
}
