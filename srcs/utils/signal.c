/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:57:24 by tschecro          #+#    #+#             */
/*   Updated: 2023/10/12 14:14:44 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler_prompt(int sig)
{
	if (sig == SIGINT)
	{
		get_app_data()->lastcode = 130;
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_exec(int sig)
{
	get_app_data()->sig_code = 128 + sig;
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		get_app_data()->sig_code = 130;
		get_app_data()->here_sigint = true;
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
		get_app_data()->sig_code = 0;
		signal(SIGINT, handler_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == 2)
	{
		signal(SIGINT, handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 3)
	{
		signal(SIGINT, handler_exec);
		signal(SIGQUIT, handler_exec);
	}
}
