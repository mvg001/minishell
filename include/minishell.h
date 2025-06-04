/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:05:53 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/04 19:39:45 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "hmap.h"
# include "libft.h"

# define IFS	" \t\n"

typedef struct s_command
{
	int		n_args;
	char	**args;
}	t_command;

typedef struct s_pipeline
{
	char		*input_file;
	char		*output_file;
	int			append_output;
	int			n_commands;
	t_command	*commands;
}	t_pipeline;

typedef struct s_minishell
{
	t_hmap	*vars;
	int		last_status;
}	t_minishell;

t_result	split_key_value(char *env, t_entry *entry);
t_hmap		*load_env_vars(char **envp);
t_minishell	*minishell_init(char **envp);
t_result	minishell_destroy(t_minishell *ctx);
t_list		*minishell_parse_line(t_minishell *ctx, char *line);
t_pipeline	*minishell_parse_words(t_minishell *ctx, t_list *words);
int			minishell_execute(t_minishell *ctx, t_pipeline *cmds);

char *append_char(char *w, char c);
char *append_string(char *w, char *str);
int is_first_char_identifier(char c);
void append_word(t_list **words, char **w);

int parser1_1(t_list **words, char **cw, char **key, char c);
int parser1_2(t_list **words, char **cw, char **c);
int parser1_3(t_list **words, char **cw, char **c);
int parser1_4(char **cw, char **key, char **c);
int parser1_5(t_minishell *ctx, char **cw, char **key, char **c);
#endif
