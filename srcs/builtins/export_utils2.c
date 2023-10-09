/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:56:28 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/09 20:56:31 by tschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sort_str_tab(char **tab, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				swap_str(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
}

void	print_key_value(char *env)
{
	int	i;
	int	is_value;

	i = 0;
	is_value = 0;
	while (env[i])
	{
		write(1, &env[i], 1);
		if (env[i] == '=' && is_value == 0)
		{
			write(1, "\"", 1);
			is_value = 1;
		}
		i++;
	}
	if (is_value == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void	print_export(char **export, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		lp_putstr_fd("export ", 1);
		print_key_value(export[i]);
		i++;
	}
}

bool	got_value(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

char	*get_key(char *args)
{
	char	*key;
	int		i;
	int		j;

	i = 0;
	while (args[i] && args[i] != '=')
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (j < i)
	{
		key[j] = args[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}
