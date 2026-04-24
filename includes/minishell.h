/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:52:52 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/24 10:56:41 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL.H
# define MINISHELL.H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#include "builtins.h"
#include "exec.h"
#include "expand.h"
#include "lexer.h"
#include "main.h"
#include "parser.h"
#include "utils.h"

#endif