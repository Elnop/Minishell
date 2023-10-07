#include "../../includes/minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	builtin_echo(char **args)
{
	int	i;
	int	n_arg;

	i = 1;
	n_arg = 0;
	if (count_args(args) > 1)
	{
		while (args[i] && lp_strncmp(args[i], "-n", 3) == 0)
		{
			n_arg = 1;
			i++;
		}
		while (args[i])
		{
			lp_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] == '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_arg == 0)
		write(1, "\n", 1);
	return (0);
}
