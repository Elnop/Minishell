#include "../../includes/minishell.h"

int	builtin_pwd(char **str)
{
	char	cwd[PATH_MAX];

	(void)str;
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
