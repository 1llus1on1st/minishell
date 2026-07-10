/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:58:31 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:40:26 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

int		is_builtin(char *cmd);
int		execute_builtin(t_shell *shell, t_cmd *cmd);
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_env(t_shell *shell, t_cmd *cmd);
int		builtin_exit(t_shell *shell, t_cmd *cmd);
void	set_exit_code(long long *code, unsigned long long value, int sign);
int		parse_exit_code(char *str, long long *code);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_export(t_shell *shell, t_cmd *cmd);
int		export_error(char *arg);
int		is_append_assignment(char *arg);
int		export_append(t_shell *shell, char *arg);
int		builtin_unset(t_shell *shell, t_cmd *cmd);
int		print_export(t_shell *shell);

#endif