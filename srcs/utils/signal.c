#include "../../includes/minishell.h"

void	handler_sig_pars(int	sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_sig_exec(int	sig)
{
	if (sig == SIGINT)
	{
		get_app_data()->exit_status = 131;
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(int type)
{
	
	if (type == 0)
	{
		signal(SIGINT, handler_sig_pars);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == 1)
	{	
		signal(SIGINT, handler_sig_exec);
	}
	
}
