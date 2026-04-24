/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:23:04 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/24 13:06:38 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
When Ctrl-C is press
1. a new line is printed
2. readline is on a new line
3. the current typed text is cleared
4. the prompt is redisplayed
*/
static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* Setup of the Ctrl-C (SIG_INT) and Ctrl-\ (SIGN_QUIT) signals which otherwise
cause errors

Ctrl-C is sent to handle_sigint
Ctrl-\ is ignored (SIG_IGN)
*/
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
