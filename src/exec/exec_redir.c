/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:37:50 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 18:38:18 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	return (0);
}

static int	apply_input_redir(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}

static int	apply_output_redir(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}

static int	apply_one_redir(t_redir *redir)
{
	if (redir->type == T_REDIR_IN)
		return (apply_input_redir(redir->file));
	if (redir->type == T_REDIR_OUT)
		return (apply_output_redir(redir->file, 0));
	if (redir->type == T_APPEND)
		return (apply_output_redir(redir->file, 1));
	if (redir->type == T_HEREDOC)
		return (0);
	return (1);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (!apply_one_redir(redir))
			return (0);
		redir = redir->next;
	}
	return (1);
}