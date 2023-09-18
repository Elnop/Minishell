/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_to_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:41:27 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/18 20:42:01 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_array	words_to_tokens(t_array words)
{
	t_array	tokens;
	size_t	i;

	tokens = array_new(array_size(words), sizeof(t_token), NULL, NULL);
	i = 0;
	return (tokens);
}
