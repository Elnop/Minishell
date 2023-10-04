#include "../../includes/minishell.h"

int	builtin_pwd(char **args)
{
	char	cwd[PATH_MAX];
	size_t	ac;

	ac = lp_strtab_size(args);
	lp_free_strtab(args, ac);
	// variable de exit status probablement a changer egalement
	if (!getcwd(cwd, PATH_MAX))
		return (0); //pas sur des retours il faut voir la gestion d'erreur
	else
	{
		lp_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		return (1); // pareil valeur de retour
	}
}
