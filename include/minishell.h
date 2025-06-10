/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:05:53 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/10 21:28:07 by user1            ###   ########.fr       */
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
	int		pid;
	int		is_interactive;
}	t_minishell;

extern int			g_signal_status;

t_result	split_key_value(char *env, t_entry *entry);
t_hmap		*load_env_vars(char **envp);
t_minishell	*minishell_init(char **envp);
t_result	minishell_destroy(t_minishell *ctx);
t_list		*minishell_parse_line(t_minishell *ctx, char *line);
t_pipeline	*minishell_parse_words(t_minishell *ctx, t_list *words);
int			minishell_execute(t_minishell *ctx, t_pipeline *cmds);
int			ft_getpid();

#endif
