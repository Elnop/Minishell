#include "../../includes/minishell.h"

void	handler_sig(int	sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}


void	signal_handler()
{
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, SIG_IGN);
}
