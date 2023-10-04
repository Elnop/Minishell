#include "../../includes/minishell.h"

bool	arg_is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!lp_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

int	get_exit_code(char **args)
{
	if (!args[1])
		return (0);//set la valeur d'exit a 0 par defaut quand y a pas d'arg
	else if (arg_is_digit(args[1]))
		return (lp_atoi(args[1])); //set la valeur d'exit a atoi(arg[1], on peut donner la valeur d'exit en argument
	else
	{
		lp_putstr_fd("minishell: exit: ", STDERR_FILENO);
		lp_putstr_fd(args[1], STDERR_FILENO);
		lp_putstr_fd(": numeric argument is required\n", STDERR_FILENO);
		return (255);
	}
}

int	builtin_exit(char **args)
{	
	size_t	ac;
	int		test;

	ac = lp_strtab_size(args);
	lp_putendl_fd("exit", STDERR_FILENO);
	if (ac > 2)
	{
		lp_putstr_fd("minishell : exit : too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	test = get_exit_code(args);
	printf("lavaleur de retour %d\n", test);
	return (lp_free_strtab(args, ac), get_exit_code(args)); // pour recup le code d'erreur
}
