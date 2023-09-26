#include "../../includes/minishell.h"

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
	*b = temp;
}


char **dup_env(char **env)
{
	char	env_cpy

	env_cpy = malloc(sizeof(ft_tab_len(env) + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_cpy = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

void	ft_sort_str_tab(char **tab, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				ft_swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}

}

void	print_export(char **export, int	count)
{
	int	i;
	
	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(export[i], 1);
		i++;
	}
}


int	export(char **env, char **args)
{
	char **env_cpy;
	int	count;

	env_cpy = dup_env(env);
	count = ft_tab_len(env_cpy);
	ft_sort_str_tab(env_cpy, count);
	if (!args[1])
	{
		print_export(env_cpy, count);
		return (free(env_cpy), EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	main()
{
	char	*tab[] = {
		"pomme",
		"banane",
		"abricot",
		"cerise"
	};
	char	*cmd[] = {
		"export"
	}
	export(tab, cmd);
	return (0);
}
