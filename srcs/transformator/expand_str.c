/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 07:16:20 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 05:44:25 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_str(char *str)
{
	char	*new_str;
	t_array	buff;
	char	*start_str;

	if (!str)
		return (NULL);
	start_str = str;
	buff = array_new(lp_strlen(str), sizeof(char), NULL, NULL);
	if (!buff)
		return (NULL);
	while (*str)
	{
		while (*str && *str != '$')
			if (!array_pushback(&buff, str++))
				return (array_free(buff), NULL);
		if (!replace_var(&str, &buff))
			return (array_free(buff), NULL);
	}
	if (!array_pushback(&buff, "\0"))
		return (array_free(buff), NULL);
	new_str = lp_strdup(buff);
	free(start_str);
	array_free(buff);
	return (new_str);
}
