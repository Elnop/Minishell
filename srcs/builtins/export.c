#include "../../includes/minishell.h"


bool	is_alpha_num(char c)
{
	if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return (true);
	else
		return (false);
}

bool	check_key(char *key)
{
	int	i;

	if (key[0] >= '0' && key[0] <= '9')
	{
		lp_dprintf(2, "minishell: export: `%s': not a valid identifier\n", key);
		return (false);
	}
	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (!is_alpha_num(key[i]))
		{
			lp_dprintf(2, "minishell: export: `%s': not a valid identifier\n", key);
			return (false);
		}
		i++;
	}
	return (true);
}

int	env_cmp(char *env, char *key)
{
	int	i;

	i = 0;
	while (env[i] && key[i] && env[i + 1] != '=' && key[i + 1] != '=' && key[i] == env[i])
		i++;
	return (env[i] - key[i]);
}


bool	is_in_env(char	*key, char **dup_env)
{
	char	i;

	i = 0;
	while (dup_env[i])
	{
		if (env_cmp(dup_env[i], key) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}


int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_tab_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	swap_str(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_str_tab(char **tab, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				swap_str(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
}

void	print_key_value(char *env)
{
	int	i;
	int	is_value;

	i = 0;
	is_value = 0;
	while (env[i])
	{
		write(1, &env[i], 1);
		if (env[i] == '=' && is_value == 0)
		{
			write(1, "\"", 1);
			is_value = 1;
		}
		i++;
	}
	if (is_value == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
}


void	print_export(char **export, int	count)
{
	int	i;
	
	i = 0;
	while (i < count)
	{
		lp_putstr_fd("export ", 1);
		print_key_value(export[i]);
		i++;
	}
}

bool	got_value(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

char	*get_key(char *args)
{
	char *key;
	int	i;
	int	j;

	i = 0;
	while (args[i] && args[i] != '=')
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (j < i)
	{
		key[j] = args[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}


int	builtin_export(char **args)
{
	char **env_cpy;
	size_t	ac;
	int	count;
	size_t	i;
	char	*key;

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
	i = 1;
	while (i < ac)
	{
	//	dprintf(2, "yo\n");
		if (check_key(args[i]) && !is_in_env(args[i], env_cpy))
		{
			array_pushfront(&get_app_data()->env, &args[i]);
		//	{
		//		dprintf(2, "yaaaa\n");
		//		return (lp_free_strtab(env_cpy, count), EXIT_FAILURE);
		//	}
		}
		if (is_in_env(args[i], env_cpy) && got_value(args[i]))
		{
			key = get_key(args[i]);
			if (!key)
				return (false);
			array_remove(get_app_data()->env, get_env_index(key));
			array_pushfront(&get_app_data()->env, &args[i]);
//				return (lp_free_strtab(env_cpy, count), free(key), EXIT_FAILURE);
			free(key);
		}
		i++;
	}
	return (lp_free_strtab(env_cpy, count), EXIT_SUCCESS);
}

