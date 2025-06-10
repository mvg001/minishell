/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/10 14:56:18 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "parser.h"

static void	init_pi(t_parser_i *pi, char *line)
{
	if (pi == NULL)
		return ;
	pi->cw = NULL;
	pi->words = NULL;
	pi->cchar = line;
	pi->key = NULL;
	pi->state = 1;
}

static void	dispose_cw_key(t_parser_i *pi)
{
	if (pi->key != NULL)
		free(pi->key);
	pi->key = NULL;
	if (pi->cw != NULL)
		free(pi->cw);
	pi->cw = NULL;
}

static t_list *input_error(t_parser_i *pi)
{
	ft_lstclear(&pi->words, free);
	ft_dprintf(2, "* Invalid input\n");
	return (NULL);
}

t_list *parser_tokenizer(t_minishell *ctx, char *line)
{
	t_parser_i	pi;

	if (ctx == NULL || line == NULL)
		return (NULL);
	init_pi(&pi, line);
	while (pi.state > 0)
	{
		if (pi.state == 1)
			tokenizer_1(&pi);
		else if (pi.state == 2)
			tokenizer_2(&pi);
		else if (pi.state == 3)
			tokenizer_3(&pi);
		else if (pi.state == 4)
			tokenizer_4(&pi);
		else if (pi.state == 5)
			tokenizer_5(&pi);
		pi.cchar++;
	}
	dispose_cw_key(&pi);
	if (pi.state < 0)
		return (input_error(&pi));
	return (pi.words);
}


t_list	*minishell_parse_line(t_minishell *ctx, char *line)
{
	t_list		*words;

	if (ctx == NULL || line == NULL)
		return (NULL);
	words = parser_tokenizer(ctx, line);
	return (words);
}
