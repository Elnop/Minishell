#include "../../includes/minishell.h"

char	*relative_to_absolute(char *pwd, char *relative)
{
	char *new_path;
	int	i;
	int	j;

	i = 0;
	while (pwd[i])
	{
		new_path[i] = pwd[i];
		i++;
	}
	j = 0;
	while (relative[j] == '.' || relative[j] == '/')
		j++;
	new_path[i] = '/';
	i++;
	while (relative[j])
	{
		new_path[i] = relative[j];
		i++;
		j++;
	}
	new_path = '\0';
	return (new_path);
}


bool	checking_relative_path(char	*str)
{
	if (str[0] == '.' && str[1] == '/')
		return (true);
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
		if (!checking_relative_path(args[1]))
		{
			if (chdir(args[1]))
					return (lp_putendl_fd("minishell: cd: no such file or directory", 2));
		}
		else
		{
			chdir(relative_to_absolute(get_env_var_value("PWD"), args[1]));
					return (lp_putendl_fd("minishell: cd: no such file or directory", 2));
		}
	}
	return (255);	// set le exit status
	// changer la var pwd
}
