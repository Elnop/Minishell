#include "../../includes/minishell.h"

int	get_env_index(char *to_find)
{
	int	i;
	const char	**env = get_app_data()->env;

	i = 0;
	while (env[i])
	{
		if (lp_strncmp(env[i], to_find, lp_strlen(to_find)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*cat_key_value(char *key, char *value)
{
	char *var_env;

	var_env = lp_strdup(key);
	if (!var_env)
		return (NULL);
	if (!lp_strcat(&var_env, value))
		return (free(var_env), NULL);
	return (var_env);
}

bool	checking_relative_path(char	*str)
{
	if (str[0] == '.' && str[1] == '/')
		return (true);
	else
		return (false);
}
