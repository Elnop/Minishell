/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 06:31:56 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/26 06:33:51 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	has_quote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (str[i] == '\'' || str[i++] == '"')
			return (true);
	return (false);
}
