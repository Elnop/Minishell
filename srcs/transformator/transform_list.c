/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 05:46:40 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_array	expand_split_str(char *str)
{
	t_array	splited;

	splited = array_new(5, sizeof(char *),
			copy_str, destroy_str);
	if (!splited)
		return (NULL);
	if (!array_pushback(&splited, (char *[]){""}))
		return (array_free(splited), NULL);
	while (*str)
		expand_split_push(&splited, &str);
	return (splited);
}

bool	transform_list(t_array *list)
{
	t_array	out;
	t_array	tmp;
	size_t	i;

	i = 0;
	out = array_new(array_size(*list), sizeof(char *), copy_str, destroy_str);
	while (out && i < array_size(*list) - 1)
	{
		tmp = expand_split_str(((char **)*list)[i]);
		if (!tmp || !array_pushback_tab(&out, tmp, array_size(tmp)))
			return (false);
		array_free(tmp);
		i++;
	}
	if (!array_pushback(&out, (char **){NULL}))
		return (array_free(out), false);
	array_free(*list);
	*list = out;
	return (true);
}
