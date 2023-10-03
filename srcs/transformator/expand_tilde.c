/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:15:35 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/29 02:32:27 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	expand_tilde_while(char *str, t_array *pbuff)
{
	size_t		i;
	const char	*home_path = get_env_var_value("HOME");

	i = 0;
	if (!home_path)
		return (false);
	while (str[i])
	{
		while (str[i] && str[i] != '~')
			if (!array_pushback(pbuff, str + i++))
				return (false);
		if (str[i] && str[i + 1] == '~')
			while (str[i] == '~')
				if (!array_pushback(pbuff, str + i++))
					return (false);
		if (str[i] != '~')
			continue ;
		i++;
		if (!array_pushback_tab(pbuff, (void *)home_path, lp_strlen(home_path)))
			return (false);
		if (str[i] && str[i] != '/' && !array_pushback(pbuff, "/"))
			return (false);
	}
	free((char *)home_path);
	return (true);
}

char	*expand_tilde(char *str)
{
	char		*out;
	t_array		buff;

	if (lp_strchr(str, '\'') || lp_strchr(str, '\"'))
		return (str);
	buff = array_new(lp_strlen(str), sizeof(char), NULL, NULL);
	if (!expand_tilde_while(str, &buff))
		return (array_free(buff), NULL);
	if (!array_pushback(&buff, "\0"))
		return (NULL);
	out = lp_strdup(buff);
	return (array_free(buff), free(str), out);
}
