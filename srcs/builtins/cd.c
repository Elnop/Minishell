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

void	ft_cd(t_array args)
{
	size_t	ac;
	char	**tmp_args;

	tmp_args = array_to_strtab(args);
	ac = array_size(args);
	if (ac > 2)
		return (ft_pudendl_fd("minishell: cd: too many arguments", 2));
	if (ac == 1)
	{
		if (chdir(get_env_var_value("HOME")))
			return (ft_pudendl_fd("minishell: HOME is not set", 2));
	}
	else
	{
		if (!checking_relative_path(tmp_args[1]));
		{
			if (chdir(tmp_args[1])
					return (ft_putendl_fd("minishell: cd: no such file or directory"), 2);
		}
		else
		{
			chdir(relative_to_absolute(get_env_var_value("PWD"), tmp_args[1]));
					return (ft_putendl_fd("minishell: cd: no such file or directory"), 2);
		}
	}
	// set le exit status
	// changer la var pwd
}
