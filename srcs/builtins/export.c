#include "../../includes/minishell.h"

bool	export_loop(size_t ac, char **env_cpy, char **args)
{
	size_t	i;
	char	*key;

	i = 1;
	while (i < ac)
	{
		if (check_key(args[i]) && !is_in_env(args[i], env_cpy))
			array_pushfront(&get_app_data()->env, &args[i]);
		if (is_in_env(args[i], env_cpy) && got_value(args[i]))
		{
			key = get_key(args[i]);
			if (!key)
				return (false);
			array_remove(get_app_data()->env, get_env_index(key));
			array_pushfront(&get_app_data()->env, &args[i]);
			free(key);
		}
		i++;
	}
	return (true);
}

int	builtin_export(char **args)
{
	char	**env_cpy;
	size_t	ac;
	int		count;

	ac = lp_strtab_size(args);
	env_cpy = array_to_strtab(get_app_data()->env);
	if (!env_cpy)
		return (EXIT_FAILURE);
	count = lp_strtab_size(env_cpy);
	ft_sort_str_tab(env_cpy, count);
	if (!args[1])
	{
		print_export(env_cpy, count);
		return (lp_free_strtab(env_cpy, count), EXIT_SUCCESS);
	}
	if (!export_loop(ac, env_cpy, args))
		return (lp_free_strtab(env_cpy, count), EXIT_FAILURE);
	return (lp_free_strtab(env_cpy, count), EXIT_SUCCESS);
}
