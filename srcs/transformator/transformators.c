/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/09 20:24:24 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_unquote(char **p_str)
{
	char	*out;
	char	*subword;
	char	*to_free;

	to_free = *p_str;
	out = lp_strdup("");
	while (**p_str)
	{
		if (**p_str == '\'' && ++(*p_str))
		{
			subword = get_subword(p_str, "'");
			(*p_str)++;
		}
		else if (**p_str == '"' && ++(*p_str))
		{
			subword = expand_parameters(get_subword(p_str, "\""));
			(*p_str)++;
		}
		else
			subword = expand_parameters(get_subword(p_str, "\"'"));
		lp_strcat(&out, subword);
		free(subword);
	}
	*p_str = out;
	return (free(to_free), out);
}

t_array	expand_split_str(char *str)
{
	t_array	splited;
	char	*str_to_free;

	str_to_free = str;
	if (!str)
		return (NULL);
	splited = array_new(5, sizeof(char *),
			copy_str, destroy_str);
	if (!splited)
		return (NULL);
	if (!array_pushback(&splited, (char *[]){""}))
		return (array_free(splited), NULL);
	while (*str)
		expand_split_push(&splited, &str);
	free(str_to_free);
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
		tmp = expand_split_str(expand_tilde(lp_strdup(((char **)*list)[i])));
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
