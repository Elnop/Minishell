/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:01:20 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 05:23:16 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	is_operator(char *str)
{
	if (!lp_strncmp(str, "&&", 2))
		return (2);
	if (!lp_strncmp(str, "||", 2))
		return (2);
	if (!lp_strncmp(str, "<<", 2))
		return (2);
	if (!lp_strncmp(str, ">>", 2))
		return (2);
	if (!lp_strncmp(str, ">", 1))
		return (1);
	if (!lp_strncmp(str, "<", 1))
		return (1);
	if (!lp_strncmp(str, "|", 1))
		return (1);
	return (0);
}
