/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 10:48:36 by elnop             #+#    #+#             */
/*   Updated: 2023/10/05 17:08:04 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_redir_operator(char *word)
{
	return (!lp_strncmp(word, "<", 2) || !lp_strncmp(word, ">", 2)
		|| !lp_strncmp(word, ">>", 3));
}

bool	has_redir_operator(char **words)
{
	while (*words && !is_operator(*words))
		words++;
	if (*words && is_redir_operator(*words))
		return (true);
	return (false);
}

bool	has_heredoc_operator(char **words)
{
	while (*words && !is_operator(*words))
		words++;
	if (*words && !lp_strncmp(*words, "<<", 3))
		return (true);
	return (false);
}
