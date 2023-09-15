/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:01:20 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/15 20:06:16 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_operator(char	*str)
{
	return (!lp_strncmp(str, "&&", 2)
		|| !lp_strncmp(str, "||", 2)
		|| !lp_strncmp(str, "|", 1)
		|| !lp_strncmp(str, "<", 1)
		|| !lp_strncmp(str, ">", 1)
		|| !lp_strncmp(str, "<<", 2)
		|| !lp_strncmp(str, ">>", 2));
}
