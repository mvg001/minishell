/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:05:53 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/06 16:25:17 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "hmap.h"
# include "libft.h"

typedef struct s_command
{
	int		n_args;
	char	**args;
	char	**envp;
	char		*input_file;
	char		*output_file;
	int			append_output;
}	t_command;

typedef struct s_pipeline
{
	int			n_commands;
	t_command	*commands;
}	t_pipeline;

typedef struct s_minishell
{
	t_hmap	*vars;
	int		last_status;
	int		tmp_count;
}	t_minishell;

int			g_signal_status;

t_result	split_key_value(char *env, t_entry *entry);
t_hmap		*load_env_vars(char **envp);
t_minishell	*minishell_init(char **envp);
t_result	minishell_destroy(t_minishell *ctx);
t_list		*minishell_parse_line(t_minishell *ctx, char *line);
t_pipeline	*minishell_parse_words(t_minishell *ctx, t_list *words);
int			minishell_execute(t_minishell *ctx, t_pipeline *cmds);

typedef struct s_parser_i
{
	t_list	*words;
	char	*cw;
	char	*key;
	char	*cchar;
} t_parser_i;

char *append_char(char *w, char c);
void append_cw_char(t_parser_i *pi, char c);
void append_cw_string(t_parser_i *pi, char *str);
int is_first_char_identifier(char c);
void append_word(t_parser_i *pi);

int parser1_1(t_parser_i *pi);
int parser1_2(t_parser_i *pi);
int parser1_3(t_parser_i *pi);
int parser1_4(t_parser_i *pi, int last_status);
int parser1_5(t_parser_i *pi, t_hmap *hm);
int parser1_6(t_parser_i *pi);
int parser1_7(t_parser_i *pi);
int parser1_8(t_parser_i *pi, int last_status);
int parser1_9(t_parser_i *pi, t_hmap *hm);
int parser1_10(t_parser_i *pi);
int parser1_11(t_parser_i *pi);
int parser1_12(t_parser_i *pi);
int parser1_13(t_parser_i *pi);
#endif
