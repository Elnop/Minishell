/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:23:41 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/07 18:17:36 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

bool	copy_str(void *pelem, void *dest);
void	destroy_str(void *pelem);
t_array	line_to_array(char *line);
char	*get_next_word(char **p_line);

#endif