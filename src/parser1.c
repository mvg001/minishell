/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/07 08:55:03 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hmap.h"
#include "minishell.h"
#include "libft.h"

static int	parser1_1_10(t_parser_i *pi, t_hmap *vars, int state,
	int last_status)
{
	if (state == 1)
		return (parser1_1(pi));
	else if (state == 2)
		return (parser1_2(pi));
	else if (state == 3)
		return (parser1_3(pi));
	else if (state == 4)
		return (parser1_4(pi, last_status));
	else if (state == 5)
		return (parser1_5(pi, vars));
	else if (state == 6)
		return (parser1_6(pi));
	else if (state == 7)
		return (parser1_7(pi));
	else if (state == 8)
		return (parser1_8(pi, last_status));
	else if (state == 9)
		return (parser1_9(pi, vars));
	else if (state == 10)
		return (parser1_10(pi));
	ft_dprintf(2, "*** INVALID STATE %d\n", state);
	return (-2);
}

static int	parser1_11_20(t_parser_i *pi, t_hmap *vars, int state)
{
	(void)vars;
	if (state == 11)
		return (parser1_11(pi));
	else if (state == 12)
		return (parser1_12(pi));
	else if (state == 13)
		return (parser1_13(pi));
	ft_dprintf(2, "*** INVALID STATE %d\n", state);
	return (-2);
}

static void	init_pi(t_parser_i *pi, char *line)
{
	if (pi == NULL)
		return ;
	pi->cw = NULL;
	pi->words = NULL;
	pi->cchar = line;
	pi->key = NULL;
}

static void	dispose_pi(t_parser_i *pi)
{
	if (pi->key != NULL)
		free(pi->key);
	pi->key = NULL;
	if (pi->cw != NULL)
		free(pi->cw);
	pi->cw = NULL;
}

t_list	*minishell_parse_line(t_minishell *ctx, char *line)
{
	int			state;
	t_parser_i	pi;

	if (ctx == NULL || line == NULL)
		return (NULL);
	init_pi(&pi, line);
	state = 1;
	while (state > 0)
	{
		if (1 <= state && state <= 10)
			state = parser1_1_10(&pi, ctx->vars, state, ctx->last_status);
		else if (11 <= state && state <= 13)
			state = parser1_11_20(&pi, ctx->vars, state);
		else
			break ;
		pi.cchar++;
	}
	dispose_pi(&pi);
	if (state < 0)
	{
		ft_lstclear(&pi.words, free);
		ft_dprintf(2, "* Invalid input\n");
		return (NULL);
	}
	return (pi.words);
}
