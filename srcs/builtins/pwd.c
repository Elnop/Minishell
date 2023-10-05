#include "../../includes/minishell.h"

int	builtin_pwd(char **args)
{
	char	cwd[PATH_MAX];
	size_t	ac;

	ac = lp_strtab_size(args);
	if (!getcwd(cwd, PATH_MAX))
		return (0);
	else
	{
		lp_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		return (1);
	}
}
