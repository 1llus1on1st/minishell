/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:30 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 22:07:35 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# include "../libft/libft.h"
# include "garbage_collector.h"

# include "builtins.h"
# include "env.h"
# include "exec.h"
# include "expand.h"
# include "lexer.h"
# include "parser.h"
# include "signals.h"
# include "utils.h"

typedef struct s_shell
{
	int		last_exit;
	char	**env;
	t_gc	*line_gc;
	t_gc	*shell_gc;
}	t_shell;

void	init_shell(t_shell *shell, char **envp);
void	setup_signals(void);
void	shell_loop(t_shell *shell);

#endif
