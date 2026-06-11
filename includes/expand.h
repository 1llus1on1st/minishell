/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:34:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/11 11:38:15 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

int		expand(t_shell *shell, t_cmd *cmds);
char	*expand_string(t_shell *shell, char *str);
char	*remove_quotes(t_shell *shell, char *str);
int		append_char(t_shell *shell, char **res, char c);
int		append_str(t_shell *shell, char **res, char *str);
int		expand_variable(t_shell *shell, char *str, char **res, int *i);

#endif