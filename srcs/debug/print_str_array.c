/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:28:08 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/20 01:30:26 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_str_array(char **strs)
{
	size_t	i;

	i = 0;
	while (i < array_size(strs))
	{
		lp_putstr_fd(strs[i], 2);
		lp_putstr_fd((char *)"\n", 2);
		i++;
	}
}
