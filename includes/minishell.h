/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:52:52 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 17:07:50 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#include "../libft/libft.h"
#include "builtins.h"
#include "exec.h"
#include "expand.h"
#include "lexer.h"
#include "parser.h"
#include "signals.h"
#include "utils.h"

typedef struct s_shell
{
    int last_exit;
} t_shell;

void	init_shell(t_shell *shell);
void	setup_signals(void);
void	shell_loop(t_shell *shell);

#endif
