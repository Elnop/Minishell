/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/15 04:44:05 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_end_of_var(char *str)
{
	return (!str || !*str || *str == '$'
		|| !lp_strncmp(str, "&&", 2)
		|| !lp_strncmp(str, "||", 2)
		|| !lp_strncmp(str, "|", 1)
		|| !lp_strncmp(str, "<", 1)
		|| !lp_strncmp(str, ">", 1)
		|| !lp_strncmp(str, "<<", 2)
		|| !lp_strncmp(str, ">>", 2));
}

static char	*get_var_name(char *str)
{
	char	i;

	i = 0;
	while (!is_end_of_var(str + i))
		i++;
	return (lp_substr(str, 0, i));
}

static char	*get_env_var_value(char **env, char *var_name)
{
	if (!var_name || !*var_name)
		return (NULL);
	while (*env)
	{
		if (!lp_strncmp(*env, var_name, lp_strlen(var_name)))
			return (
				lp_substr(*env, lp_strlen(var_name) + 1,
					lp_strlen(*env) - lp_strlen(var_name) - 1)
			);
		env++;
	}
	return (NULL);
}

static bool	replace_var(t_array env, char **p_str, t_array *p_buff)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	if (!**p_str)
		return (true);
	(*p_str)++;
	var_name = get_var_name(*p_str);
	*p_str += lp_strlen(var_name);
	var_value = get_env_var_value(env, var_name);
	free(var_name);
	i = 0;
	while (var_value && var_value[i])
		if (!array_pushback(p_buff, var_value + i++))
			return (false);
	free(var_value);
	return (true);
}

char	*expand(t_array env, char *str)
{
	char	*new_str;
	t_array	buff;

	buff = array_new(10, sizeof(char), NULL, NULL);
	if (!buff)
		return (NULL);
	while (*str)
	{
		while (*str && *str != '$')
			if (!array_pushback(&buff, str++))
				return (NULL);
		if (!replace_var(env, &str, &buff))
			return (NULL);
	}
	if (!array_pushback(&buff, "\0"))
		return (NULL);
	new_str = lp_strdup(buff);
	array_free(buff);
	return (new_str);
}
