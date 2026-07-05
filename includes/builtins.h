/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:58:31 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 17:28:10 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

int	is_builtin(char *cmd);
int	execute_builtin(t_shell *shell, t_cmd *cmd);

int	builtin_echo(t_cmd *cmd);
int	builtin_pwd(void);
int	builtin_env(t_shell *shell);
int	builtin_exit(t_shell *shell, t_cmd *cmd);
int	parse_exit_code(char *str, long long *code);
int	builtin_cd(t_shell *shell, t_cmd *cmd);
int	builtin_export(t_shell *shell, t_cmd *cmd);
int	builtin_unset(t_shell *shell, t_cmd *cmd);
int		print_export(t_shell *shell);

#endif