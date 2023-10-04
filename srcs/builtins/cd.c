#include "../../includes/minishell.h"

int	get_relative_len(char *relative)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (relative[i] == '.' || relative[i] == '/')
		i++;
	while (relative[i])
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_join_path(char *pwd, char *relative)
{
	int	i;
	int j;
	char	*out;

	if (!pwd || !relative)
		return (NULL);
	out = malloc(sizeof(char) * (lp_strlen(pwd) + get_relative_len(relative) + 2));
	if (!out)
		return (NULL);
	i = 0;
	while (pwd[i])



	return (NULL);
}


char	*relative_to_absolute(char *pwd, char *relative)
{
	char *new_path;

	new_path = ft_join_path(pwd, relative);
	if (!new_path)
		return (NULL);
	return (new_path);
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

int	get_index(char *to_find)
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

bool	set_pwds(char *old_pwd, char *pwd)
{
	int	index;
	char	*key_old_pwd;
	char	*key_pwd;
	char	*cat_old_pwd;
	char	*cat_pwd;

	key_old_pwd = "OLD_PWD=";
	key_pwd = "PWD=";
	cat_old_pwd = lp_strdup("OLD_PWD=");
	if (!cat_old_pwd)
		return (false);
	if(!lp_strcat(&cat_old_pwd, old_pwd))
		return (false);
	cat_pwd = lp_strdup("PWD=");
	if (!cat_pwd)
		return (false);
	if (!lp_strcat(&cat_pwd, pwd))
		return (false);
	index = get_index(key_old_pwd);
	if (index == -1)
		array_pushback(&(get_app_data()->env), &cat_old_pwd);
	else
	{
		array_remove(get_app_data()->env, index);
		array_pushback(&(get_app_data()->env), &cat_old_pwd);
	}
	index = get_index(key_pwd);
	if (index == -1)
		array_pushback(&(get_app_data()->env), &cat_pwd);
	else
	{
		array_remove(get_app_data()->env, index);
		array_pushback(&(get_app_data()->env), &cat_pwd);
	}
	return (true);
}

int	builtin_cd(char **args)
{
	size_t	ac;

	ac = lp_strtab_size(args);
	if (ac > 2)
		return (lp_free_strtab(args, ac), lp_putendl_fd("minishell: cd: too many arguments", 2));
	if (ac == 1)
	{
		if (chdir(get_env_var_value("HOME")))
			return (lp_free_strtab(args, ac), lp_putendl_fd("minishell: HOME is not set", 2));
	}
	else
	{
		if (!checking_relative_path(&args[1]))
		{
			if (chdir(args[1]))
				return (lp_free_strtab(args, ac), lp_putendl_fd("minishell: cd: no such file or directory", 2));
		}
		else
		{
		
			dprintf(2, "args : %s\n", args[1]);
			if (chdir(args[1]))	
				return (lp_putendl_fd("minishell: cd: no such file or directory", 2));
		//	if (chdir(relative_to_absolute(get_env_var_value("PWD"), args[1])));
		}
	}
//	if (!set_pwds(get_env_var_value("PWD"), relative_to_absolute(get_env_var_value("PWD"), args[1])))
//		return (143);
	return (255);	// set le exit status
}
