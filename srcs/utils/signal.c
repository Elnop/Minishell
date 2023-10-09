/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschecro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:57:24 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/09 20:57:58 by tschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		get_app_data()->lastcode = sig + 128;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		write(1, "Quit\n", 5);
		rl_replace_line("", 0);
		get_app_data()->lastcode = sig + 128;
	}
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		get_app_data()->here_sigint = true;
		write(2, "\nno end of file", 20);
		close(0);
		close(1);
		rl_on_new_line();
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
		signal(SIGINT, handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
