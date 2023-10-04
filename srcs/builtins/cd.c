#include "../../includes/minishell.h"


int	get_env_index(char *to_find)
{
	int	i;
	const char	**env = get_app_data()->env;

	i = 0;
	while (env[i])
	{
		if (lp_strncmp(env[i], to_find, lp_strlen(to_find)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*cat_key_value(char *key, char *value)
{
	char *var_env;

	var_env = lp_strdup(key);
	if (!var_env)
		return (NULL);
	if (!lp_strcat(&var_env, value))
		return (free(var_env), NULL);
	return (var_env);
}

bool	set_pwds(char *pwd)
{
	int		index_pwd;
	int		index_opwd;
	char	*old_pwd;
	char	*c_pwd;
	char	cwd[PATH_MAX];

	index_pwd = get_env_index("PWD=");
	index_opwd = get_env_index("OLDPWD=");
	if (index_pwd == -1)
	{
		if (index_opwd != - 1)
			array_remove(get_app_data()->env, index_opwd);
		return (false);
	}
	else
	{
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
			dprintf(2, "opwd :%s\n", old_pwd);
			if (!old_pwd)
				return (free(c_pwd), false);
			array_remove(get_app_data()->env, index_opwd);
			if(!array_pushfront(&get_app_data()->env, &old_pwd))
				return (free(c_pwd), false);
		}
	}
	return (free(old_pwd), free(c_pwd),true);
}

bool	checking_relative_path(char	**str)
{
	if ((*str)[0] == '.' && (*str)[1] == '/')
		return (true);
	else
		return (false);
}

int	builtin_cd(char **args)
{
	size_t	ac;
	char	*home;
	char	*pwd;
	char	*rel_path;

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
	{
		rel_path = lp_strdup(args[1]);
		if(!checking_relative_path(&rel_path))
		{
			if (chdir(rel_path))
				return (free(rel_path), lp_putendl_fd("minishell: cd: no such file or directory", 2));
		}
		else
		{
			if (chdir(rel_path + 2))
				return (free(rel_path), lp_putendl_fd("minishell: cd: no such file or directory", 2));
		}
		free(rel_path);
	}
	pwd = get_env_var_value("PWD");
	if (!set_pwds(pwd))
	{
		free(pwd);
		return (124);
	}
	free(pwd);
	return (255);
}
