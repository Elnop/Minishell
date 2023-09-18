/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenify.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:48:19 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/18 09:11:49 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIFY_H
# define TOKENIFY_H

enum e_token_type
{
	EXEC,
	AND,
	OR,
	PIPE,
	REDIR,
};

enum e_redir_type
{
	IN,
	IN_APPEND,
	OUT,
	OUT_APPEND,
};

typedef struct s_token
{
	void			*infos;
	e_token_type	type;
}	t_token;

typedef struct s_cmd_infos {
	pid_t	fd_in;
	pid_t	fd_out;
	pid_t	cmd_name;
	pid_t	cmd_args;
}	t_cmd_infos;

typedef struct s_and_infos {
	t_token	*token_left;
	t_token	*token_right;
}	t_and_infos;

typedef struct s_or_infos {
	t_token	*token_left;
	t_token	*token_right;
}	t_and_infos;

typedef struct s_redir_infos {
	e_redir_type	type;
	char			*name;
	t_token			*next_token;
}	t_and_infos;

#endif