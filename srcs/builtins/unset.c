
#include "../../includes/minishell.h"

int	builtin_unset(char **args)
{
	size_t	ac;
	size_t	i;
	char	**env_cpy;
	int		count;

	if (!args[1])
		return (EXIT_SUCCESS);
	ac = lp_strtab_size(args);
	env_cpy = array_to_strtab(get_app_data()->env);
	count = lp_strtab_size(env_cpy);
	if (!env_cpy)
		return (EXIT_FAILURE);
	i = 1;
	while (i < ac)
	{
		if (is_in_env(args[i], env_cpy))
			array_remove(get_app_data()->env, get_env_index(args[i]));
		i++;
	}
	return (lp_free_strtab(env_cpy, count), EXIT_SUCCESS);
}
