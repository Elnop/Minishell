/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 07:48:32 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/03 14:48:07 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	strtab_size(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*get_subword(char **p_str, char *limiters)
{
	t_array	buff;
	char	*subword;

	buff = array_new(10, sizeof(char), NULL, NULL);
	while (**p_str && !lp_strchr(limiters, **p_str))
		if (!array_pushback(&buff, (*p_str)++))
			return (array_free(buff), NULL);
	if (!array_pushback(&buff, "\0"))
		return (array_free(buff), NULL);
	subword = lp_strdup(buff);
	return (array_free(buff), subword);
}

bool	expand_split_push_unquoted(t_array *p_splited, char **p_str)
{
	char	**tab_tmp;
	char	*subword;

	subword = get_subword(p_str, "\"'");
	subword = expand_parameters(subword);
	if (!subword)
		return (NULL);
	tab_tmp = lp_pool_split(subword, SPACERS);
	free(subword);
	lp_strcat(((char **)*p_splited) + array_size(*p_splited) - 1, *tab_tmp);
	if (!((char **)*p_splited)[array_size(*p_splited) - 1])
		return (lp_free_strtab(tab_tmp, strtab_size(tab_tmp)), false);
	if (strtab_size(tab_tmp) > 1 && !array_pushback_tab(p_splited,
			tab_tmp + 1, strtab_size(tab_tmp) - 1))
		return (lp_free_strtab(tab_tmp, strtab_size(tab_tmp)), false);
	lp_free_strtab(tab_tmp, strtab_size(tab_tmp));
	return (true);
}

bool	expand_split_push(t_array *p_splited, char	**p_str)
{
	char	*subword;

	if (**p_str == '\'')
	{
		(*p_str)++;
		subword = get_subword(p_str, "'");
		(*p_str)++;
		if (!subword)
			return (false);
		lp_strcat((char **)(*p_splited) + array_size(*p_splited) - 1, subword);
		free(subword);
	}
	else if (**p_str == '"')
	{
		(*p_str)++;
		subword = expand_parameters(get_subword(p_str, "\""));
		(*p_str)++;
		lp_strcat((char **)*p_splited + array_size(*p_splited) - 1, subword);
	}
	else
		expand_split_push_unquoted(p_splited, p_str);
	if (!((char **)(*p_splited))[array_size(*p_splited) - 1])
		return (false);
	return (true);
}
