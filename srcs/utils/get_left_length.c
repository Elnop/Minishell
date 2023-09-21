/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_left_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:28:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/21 01:53:13 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_left_length(char **words, char *limiter)
{
	size_t	i;

	i = 0;
	while (words[i]
		&& lp_strncmp(words[i], limiter, lp_strlen(limiter)))
		i++;
	return (i);
}
