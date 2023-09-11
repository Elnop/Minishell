/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/11 20:15:53 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_array	str_to_buff(char *str)
{
	t_array	buff;

	if (!str)
		return (NULL);
	buff = array_new(lp_strlen(str), sizeof(char), NULL, NULL);
	if (!buff || !array_pushback_tab(&buff, str, lp_strlen(str) + 1))
		return (NULL);
	free(str);
	return (buff);
}

static void	remove_end_dollar(t_array buff, char next_char)
{
	if (next_char && ((char *)buff)[array_size(buff) - 2] == '$')
		array_remove(buff, array_size(buff) - 2);
}

char	*expand(char *str, char next_char)
{
	t_array	buff;
	char	*new_str;

	buff = str_to_buff(str);
	if (!buff)
		return (NULL);
	remove_end_dollar(buff, next_char);
	new_str = lp_strdup(buff);
	array_free(buff);
	return (new_str);
}
