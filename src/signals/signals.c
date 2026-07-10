/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:23:04 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:17:16 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Stores the last signal caught by a signal handler.
1.	Signal handlers cannot safely do complex shell logic directly
2.	This global lets the handler record that a signal happened
3.	The main shell code can later read it and update last_exit safely
4.	It is global because signal handlers cannot receive t_shell
5.	sig_atomic_t is used because it is safe to read and write inside handlers
*/
volatile sig_atomic_t	g_signal = 0;

/*
Installs a signal handler for one signal number.
1.	Creates a sigaction structure for the chosen signal
2.	Initializes the signal mask so no extra signals are blocked
3.	Sets the flags field to 0 for default sigaction behavior
4.	Stores the handler function in the sigaction structure
5.	Calls sigaction to apply the handler
*/
void	set_signal_handler(int sig, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(sig, &sa, NULL);
}

/*
Handles Ctrl-C while minishell is waiting at the prompt.
1.	Stores the received signal in the global signal variable
2.	Writes a newline so the prompt moves to a clean line
3.	Tells readline that the cursor is now on a new line
4.	Clears the current readline input buffer
5.	Redisplays the prompt without exiting minishell
*/
static void	handle_prompt_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
Sets the signal behavior used while minishell is waiting for input.
1.	Handles SIGINT with the prompt-specific Ctrl-C handler
2.	Makes Ctrl-C clear the current input line instead of closing minishell
3.	Ignores SIGQUIT so Ctrl-\ does not quit from the prompt
4.	Leaves the shell ready to continue reading commands
*/
void	setup_prompt_signals(void)
{
	set_signal_handler(SIGINT, handle_prompt_sigint);
	set_signal_handler(SIGQUIT, SIG_IGN);
}
