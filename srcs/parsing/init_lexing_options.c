/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexing_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:40:54 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/10 02:33:21 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexing_option *init_lexing_options()
{
	const size_t			operators_count = 7;
	t_lexing_option			*heap_tab;
	const t_lexing_option	stack_tab[]
		= (const t_lexing_option	[]){
		(t_lexing_option){"|"},
		(t_lexing_option){"<"},
		(t_lexing_option){"<<"},
		(t_lexing_option){">"},
		(t_lexing_option){">>"},
		(t_lexing_option){"&&"},
		(t_lexing_option){"||"},
	};

	heap_tab
		= lp_calloc(operators_count + 1, sizeof(t_lexing_option));
	lp_memcpy(stack_tab, heap_tab, sizeof(t_lexing_option) * 7);
	return (heap_tab);
}
