bool	arg_is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_is_digit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}


void	get_exit_code(char **args)
{
	if (!args[1])
		//set la valeur d'exit a 0 par defaut quand y a pas d'arg
	else if (arg_is_digit(args[1]))
		//set la valeur d'exit a atoi(arg[1], on peut donner la valeur d'exit en argument
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument is required\n", STDERR_FILENO);
		// set la valeur d'exit a 255 par defaut
	}
}


int	ft_exit(char **args)
{	
	// on appelle la fonction exit et ensuite on exit avec la valeur d'exit que on a recup, avec le message d'erreur approprie
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] && args[2])
	{
		lp_putstr_fd("minishell : exit : too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	get_exit_code(args); // pour recup le code d'erreur
	return (EXIT_SUCCESS);
	
}
