/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:05:53 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/18 19:05:28 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "hmap.h"
# include "libft.h"

typedef struct s_command
{
	char	**args;
	char	*input_file;
	int		is_here_doc;
	char	*output_file;
	int		append_output;
	char	*path;		// Fran
	int		fd_input;	// Fran
	int		fd_output;	// Fran
	int		type;		// Fran
	int		error;		// Fran
}	t_command;

typedef struct s_pipeline
{
	int			n_commands;
	t_command	*commands;
	char		**envp;
}	t_pipeline;

typedef struct s_minishell
{
	t_hmap	*vars;
	int		last_status;
	int		tmp_count;
	int		pid;
	int		is_interactive;
}	t_minishell;

typedef enum e_operator
{
	OPER_ERROR,
	OPER_LT,
	OPER_GT,
	OPER_LT_LT,
	OPER_GT_GT,
	OPER_PIPE,
	OPER_NONE,
}	t_operator;

// pipeline parsing
typedef struct s_pp
{
	int			state;
	t_operator	op;
	t_list		*tokens;
	t_list		*ctk;
	t_list		*cmds;
	t_list		*vars;
	t_list		*args;
	t_command	*ccmd;
}	t_pp;
/*
typedef enum e_result
{
	OP_OK,
	OP_FAILED,
	OP_INVALID
}	t_result;*/
extern int			g_signal_status;

t_minishell	*minishell_init(char **envp);
t_result	minishell_destroy(t_minishell *ctx);
t_list		*minishell_parse_line(t_minishell *ctx, char *line);
t_pipeline	*minishell_parse_words(t_minishell *ctx, t_list *words);
int			minishell_execute(t_minishell *ctx, t_pipeline *cmds);
int			ft_getpid();

t_command   *msh_create_command(void);
void    msh_destroy_command(t_command **simple_command);
void    msh_print_command(int fd, t_command *sc);
t_result    msh_command_set_input(t_command *sc, char *filename, int is_here_doc);
t_result    msh_command_set_output(t_command *sc, char *filename, int is_app_mode);
t_result    msh_command_set_args(t_command *sc, char **args);
t_result    msh_command_set_path(t_command *sc, char *path);

t_pipeline	*msh_create_pipeline(void);
void	msh_destroy_pipeline(t_pipeline *pline);
void	msh_print_pipeline(int fd, t_pipeline *pline);

t_operator  get_operator_type(char *str);
t_result    pipe1(t_pp *pps);
t_result    pipe2(t_pp *pps);

#endif
