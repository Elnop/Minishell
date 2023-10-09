/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:56:55 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/09 20:56:57 by tschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(char **args)
{
	char	cwd[PATH_MAX];

	(void)args;
	if (!getcwd(cwd, PATH_MAX))
		return (0);
	else
	{
		lp_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		return (1);
	}
}
