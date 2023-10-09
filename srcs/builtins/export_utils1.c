/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:55:39 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/09 20:55:43 by tschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_alpha_num(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (true);
	else
		return (false);
}

bool	check_key(char *key)
{
	int	i;

	if ((key[0] >= '0' && key[0] <= '9') || key[0] == '=')
	{
		lp_dprintf(2, "minishell: export: `%s': not a valid identifier\n", key);
		return (false);
	}
	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (!is_alpha_num(key[i]))
		{
			lp_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
				key);
			return (false);
		}
		i++;
	}
	return (true);
}

int	env_cmp(char *env, char *key)
{
	int	i;

	i = 0;
	while (env[i] && key[i] && env[i + 1] != '=' && key[i + 1] != '='
		&& key[i] == env[i])
		i++;
	return (env[i] - key[i]);
}

bool	is_in_env(char	*key, char **dup_env)
{
	int	i;

	i = 0;
	while (dup_env[i])
	{
		if (env_cmp(dup_env[i], key) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
