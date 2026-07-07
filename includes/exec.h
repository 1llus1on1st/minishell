/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:30:39 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/07 21:16:15 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;

int		execute_cmd(t_shell *shell, t_cmd *cmd);
int		execute_external(t_shell *shell, t_cmd *cmd);
int		execute_builtin_with_redirs(t_shell *shell, t_cmd *cmd);
int		execute_redir_only(t_cmd *cmd);
int		apply_redirections(t_cmd *cmd);
int		save_stdio(int saved[2]);
int		restore_stdio(int saved[2]);
char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_status);
int		execute_pipeline(t_shell *shell, t_cmd *cmds);
void	run_pipeline_child(t_shell *shell, t_cmd *cmd, int *pipes,
		int info[2]);
void	close_pipes(int *pipes, int count);
int		prepare_heredocs(t_shell *shell, t_cmd *cmds);
int		prepare_one_heredoc(t_shell *shell, t_redir *redir);
void	close_heredoc_fds(t_cmd *cmds);

#endif