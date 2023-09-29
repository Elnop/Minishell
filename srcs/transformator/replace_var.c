/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titilamenace <titilamenace@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:srcs/expands/expand.c
/*   Created: 2023/09/11 19:34:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/26 18:59:36 by titilamenac      ###   ########.fr       */
=======
/*   Created: 2023/09/25 23:06:42 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 14:02:11 by lperroti         ###   ########.fr       */
>>>>>>> master:srcs/transformator/replace_var.c
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_end_of_var(char *str)
{
	return (!str || !*str || *str == '$' || is_operator(str) || *str == '"'
		|| lp_strchr(SPACERS, *str));
}

static char	*get_env_var_name(char *str)
{
	char	i;

	i = 0;
	while (!is_end_of_var(str + i))
		i++;
	return (lp_substr(str, 0, i));
}

char	*get_env_var_value(char *var_name)
{
	char	**env;

	env = get_app_data()->env;
	if (!var_name || !lp_strlen(var_name))
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

bool	replace_var(char **p_str, t_array *p_buff)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	if (!**p_str)
		return (true);
	(*p_str)++;
	var_name = get_env_var_name(*p_str);
	*p_str += lp_strlen(var_name);
	var_value = get_env_var_value(var_name);
	free(var_name);
	i = 0;
	while (var_value && var_value[i])
		if (!array_pushback(p_buff, var_value + i++))
			return (false);
	free(var_value);
	return (true);
}
