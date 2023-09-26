/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titilamenace <titilamenace@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 04:55:13 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/26 18:59:39 by titilamenac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	echo(char **args)
{
	int	i;
	int	n_arg;
	// quand on s'attaquera a $? penser a changer la var dans le built in
	i = 1;
	n_arg = 0;
	if (count_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0) // on doit incrementer avec plusieurs -n
		{	
			n_arg = 1;
			i++;
		}
		while (args[i])
		{
			lp_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] == '\0') // espace si chaine vide
				write(1, " ", 1);
			i++;
		}
	}
	if (n_arg == 0)
		write(1, "\n", 1); // retour a la ligne sans option -n
	return (0);
}
