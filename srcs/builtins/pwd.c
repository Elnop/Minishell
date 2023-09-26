int	pwd(void)
{
	char	cwd[PATH_MAX];

	// variable de exit status probablement a changer egalement
	if (!get_cwd(cwd, PATH_MAX));
		return (0); //pas sur des retours il faut voir la gestion d'erreur
	else
	{
		lp_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		return (1) // pareil valeur de retour
	}
}
