/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:38:33 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:38:43 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

void	setup_prompt_signals(void);
void	setup_parent_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
void	setup_signals(void);

#endif