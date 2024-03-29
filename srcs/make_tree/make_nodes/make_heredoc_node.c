/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:15:47 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/13 14:40:13 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*str_unquote(char *str)
{
	char	*unquoted;
	size_t	i;

	unquoted = lp_calloc(lp_strlen(str) + 1, sizeof(char));
	i = 0;
	while (unquoted && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			str++;
			continue ;
		}
		unquoted[i] = str[i];
		i++;
	}
	return (unquoted);
}

char	*get_heredoc_buffer(char *limiter, bool need_ex)
{
	char	*buff;
	char	*line;

	buff = lp_strdup("");
	if (!buff || (!limiter && (free(buff), 1)))
		return (NULL);
	if ((signal_handler(2), 0) || !buff || !lp_strcat(&limiter, "\n"))
		return (free(buff), NULL);
	line = readline("document-ici>");
	if (line && !lp_strcat(&line, "\n"))
		return (free(buff), free(line), free(limiter), NULL);
	while (buff && line && lp_strncmp(line, limiter, lp_strlen(line)))
	{
		if (get_app_data()->here_sigint)
			return (free(buff), free(line), free(limiter), NULL);
		if (need_ex)
			line = expand_parameters(line);
		if (!lp_strcat(&buff, line) || (free(line), 0))
			return (free(buff), free(line), free(limiter), NULL);
		line = readline("document-ici>");
		if (line && !lp_strcat(&line, "\n"))
			return (free(buff), free(line), free(limiter), NULL);
	}
	return (free(line), free(limiter), buff);
}

t_node	*make_heredoc_node(char **words)
{
	t_node	*p_node;
	size_t	i;

	i = 0;
	while (words[i] && !is_operator(words[i]))
		i++;
	if (!lp_strncmp(words[i], "<<", 3)
		&& (!words[i + 1] || is_operator(words[i + 1])))
		return (NULL);
	p_node = malloc(sizeof(t_node));
	p_node->type = HEREDOC_NODE;
	p_node->data = malloc(sizeof(t_heredoc_data));
	if (!p_node->data)
		return (free(p_node), NULL);
	((t_heredoc_data *)p_node->data)->buff = get_heredoc_buffer(
			str_unquote(words[i + 1]),
			!(lp_strchr(words[i + 1], '"') || lp_strchr(words[i + 1], '\'')));
	if (!((t_heredoc_data *)p_node->data)->buff)
		return (free(p_node->data), free(p_node), NULL);
	array_remove((t_array)words, i);
	array_remove((t_array)words, i);
	add_grb(p_node, GRBG_TREE_NODE);
	((t_heredoc_data *)p_node->data)->next = make_cmd_node(words);
	return (p_node);
}
