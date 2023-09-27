/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 14:56:55 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_tilde(char *str)
{
	t_array		buff;
	const char	*home_path = get_env_var_value("HOME");
	char		*out;
	size_t		i;

	if (!home_path || lp_strchr(str, '\'') || lp_strchr(str, '\"'))
		return (str);
	buff = array_new(lp_strlen(str), sizeof(char), NULL, NULL);
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '~')
			if (!array_pushback(&buff, str + i++))
				return (NULL);
		if (str[i] && str[i + 1] == '~')
			while (str[i] == '~')
				if (!array_pushback(&buff, str + i++))
					return (NULL);
		if (str[i] != '~')
			continue ;
		i++;
		if (!array_pushback_tab(&buff, (void *)home_path, lp_strlen(home_path)))
			return (NULL);
		if (str[i] && str[i] != '/')
			if (!array_pushback(&buff, "/"))
				return (NULL);
	}
	if (!array_pushback(&buff, "\0"))
		return (NULL);
	out = lp_strdup(buff);
	return (array_free(buff), free((char *)home_path), out);
}

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
		tmp = expand_split_str(expand_tilde(((char **)*list)[i]));
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
