/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:30:39 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:37:37 by mshargan         ###   ########.fr       */
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
int		apply_input_redir(char *file, int target_fd);
int		apply_output_redir(char *file, int append, int target_fd);
int		apply_read_write_redir(char *file, int target_fd);
int		apply_here_string(char *word, int target_fd);
int		save_stdio(int saved[2]);
int		restore_stdio(int saved[2]);
char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_status);
char	*handle_direct_path(char *cmd, int *exit_status);
int		handle_special_cmd_name(char *cmd, int *exit_status);
int		execute_pipeline(t_shell *shell, t_cmd *cmds);
int		wait_pipeline(pid_t *pids, int count);
void	run_pipeline_child(t_shell *shell, t_cmd *cmd, int *pipes,
			int info[2]);
void	close_pipes(int *pipes, int count);
int		prepare_heredocs(t_shell *shell, t_cmd *cmds);
int		open_unique_heredoc(t_shell *shell, char **path);
int		read_heredoc_loop(t_shell *shell, t_redir *redir, int fd);
int		prepare_one_heredoc(t_shell *shell, t_redir *redir);
void	close_heredoc_fds(t_cmd *cmds);
void	exit_child(t_shell *shell, int status);

#endif