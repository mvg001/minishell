/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:05:53 by mvassall          #+#    #+#             */
/*   Updated: 2025/05/29 17:50:37 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "hmap.h"

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
int			proc_line(t_minishell *ctx, char *line);
#endif
