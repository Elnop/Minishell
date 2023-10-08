/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:42:36 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/08 00:42:37 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	push_pwd(int index_pwd, int index_opwd, char *pwd)
{
	char	cwd[PATH_MAX];
	char	*c_pwd;
	char	*old_pwd;

	if (!getcwd(cwd, PATH_MAX))
		return (false);
	c_pwd = cat_key_value("PWD=", cwd);
	if (!c_pwd)
		return (false);
	array_remove(get_app_data()->env, index_pwd);
	if (!array_pushfront(&get_app_data()->env, &c_pwd))
		return (free(c_pwd), false);
	if (index_opwd != -1)
	{
		index_opwd = get_env_index("OLDPWD=");
		old_pwd = cat_key_value("OLDPWD=", pwd);
		if (!old_pwd)
			return (free(c_pwd), false);
		array_remove(get_app_data()->env, index_opwd);
		if (!array_pushfront(&get_app_data()->env, &old_pwd))
			return (free(c_pwd), false);
		free(old_pwd);
	}
	return (free(c_pwd), true);
}

bool	set_pwds(char *pwd)
{
	int		index_pwd;
	int		index_opwd;

	index_pwd = get_env_index("PWD=");
	index_opwd = get_env_index("OLDPWD=");
	if (index_pwd == -1)
	{
		if (index_opwd != -1)
			array_remove(get_app_data()->env, index_opwd);
		return (false);
	}
	else
	{
		if (!push_pwd(index_pwd, index_opwd, pwd))
			return (false);
	}
	return (true);
}

int	relative_path(char *args)
{
	if (!checking_relative_path(args))
	{
		if (chdir(args))
			return (lp_putendl_fd("minishell: cd: no such file or directory"
					, 2));
	}
	else
	{
		if (chdir(args + 2))
			return (lp_putendl_fd("minishell: cd: no such file or directory"
					, 2));
	}
	return (EXIT_FAILURE);
}

int	builtin_cd(char **args)
{
	size_t	ac;
	char	*home;
	char	*pwd;

	ac = lp_strtab_size(args);
	if (ac > 2)
		return (lp_putendl_fd("minishell: cd: too many arguments", 2));
	if (ac == 1)
	{
		home = get_env_var_value("HOME");
		if (chdir(home))
			return (free(home), lp_putendl_fd("minishell: HOME is not set", 2));
		free(home);
	}
	else
		relative_path(args[1]);
	pwd = get_env_var_value("PWD");
	if (!set_pwds(pwd))
	{
		free(pwd);
		return (124);
	}
	free(pwd);
	return (255);
}
