#include "../../includes/minishell.h"

void	handler_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_exec(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		//rl_redisplay();
		get_app_data()->lastcode = sig + 128;

	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		write(1, "Quit\n", 5);
		rl_replace_line("", 0);
		//rl_redisplay();
		get_app_data()->lastcode = sig + 128;
	}
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(1);
		rl_on_new_line();
		write(2, "\nno end of file nana", 20);
		rl_replace_line("", 0);
		rl_redisplay();
		clean_garbage();
	}
}


void	signal_handler(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, handler_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, handler_exec);
		signal(SIGQUIT, handler_exec);
	}
	else if (mode == 2)
	{
		get_app_data()->here_sigint = true;
		signal(SIGINT, handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
