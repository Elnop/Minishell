#include "../../includes/minishell.h"

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


char **dup_env(char **env)
{
	char	**env_cpy;
	int	i;

	env_cpy = malloc(sizeof(char *) * (ft_tab_len(env) + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_cpy[i] = lp_strdup(env[i]);
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

void	print_export(char **export, int	count)
{
	int	i;
	
	i = 0;
	while (i < count)
	{
		lp_putstr_fd("export ", 1);
		lp_putendl_fd(export[i], 1);
		i++;
	}
}


int	builtin_export(char **args)
{
	char **env_cpy;
	size_t	ac;
	int	count;

	ac = lp_strtab_size(args);
	env_cpy = dup_env(get_app_data()->env);
	count = ft_tab_len(env_cpy);
	ft_sort_str_tab(env_cpy, count);
	if (!args[1])
	{
		print_export(env_cpy, count);
		return (free(env_cpy), lp_free_strtab(args, ac), EXIT_SUCCESS);
	}
	return (lp_free_strtab(args, ac), EXIT_SUCCESS);
}

