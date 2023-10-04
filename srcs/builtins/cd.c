#include "../../includes/minishell.h"


int	get_env_index(char *to_find)
{
	int	i;
	const char	**env = get_app_data()->env;

	i = 0;
	while (env[i])
	{
		if (lp_strncmp(env[i], to_find, lp_strlen(to_find) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*cat_key_value(char *key, char *value)
{
	char *var_env;

	var_env = lp_strdup(key);
	if (!lp_strcat(&var_env, value))
		return (NULL);
	return (var_env);
}


bool	set_pwds(char *pwd)
{
	int	index;
	char	*old_pwd;

	index = get_env_index("OLD_PWD=");
	old_pwd = cat_key_value("OLD_PWD", pwd);
	if (!old_pwd)
		return (NULL);
	if (index == -1)
		array_pushback(&(get_app_data()->env), &old_pwd);
	else
	{
		array_remove(get_app_data()->env, index);
		array_pushback(&(get_app_data()->env), &old_pwd);
	}

}

bool	checking_relative_path(char	**str)
{
	if ((*str)[0] == '.' && (*str)[1] == '/')
	{
		(*str)+=2;
		return (true);
	}
	else
		return (false);
}

int	builtin_cd(char **args)
{
	size_t	ac;

	ac = lp_strtab_size(args);
	if (ac > 2)
		return (lp_putendl_fd("minishell: cd: too many arguments", 2));
	if (ac == 1)
	{
		if (chdir(get_env_var_value("HOME")))
			return (lp_putendl_fd("minishell: HOME is not set", 2));
	}
	else
	{
		if (!checking_relative_path(&args[1]))
		{
			if (chdir(args[1]))
				return (lp_putendl_fd("minishell: cd: no such file or directory", 2));
		}
		else
		{
			if (chdir(args[1]))	
				return (lp_putendl_fd("minishell: cd: no such file or directory", 2));
		}
	}
	if (!set_pwds(get_env_var_value("PWD")))
		return (124);
	return (255);	// set le exit status
}
