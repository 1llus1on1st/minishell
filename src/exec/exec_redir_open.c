/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_open.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:33:55 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:37:15 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Prints a redirection open or dup error.
*/
static int	redir_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	return (0);
}

/*
Applies a <> read-write redirection.
1.	Opens the file for reading and writing, creating it if needed
2.	Duplicates the opened fd onto the requested target fd
*/
int	apply_read_write_redir(char *file, int target_fd)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, target_fd) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}

/*
Applies an input redirection.
1.	Opens the target file read-only
2.	Duplicates it onto the requested target fd
*/
int	apply_input_redir(char *file, int target_fd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, target_fd) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}

/*
Applies an output or append redirection.
1.	Creates the file if it does not exist
2.	Uses O_APPEND for >> and O_TRUNC for >
3.	Duplicates the opened file onto the requested target fd
*/
int	apply_output_redir(char *file, int append, int target_fd)
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
	if (dup2(fd, target_fd) < 0)
		return (close(fd), redir_error(file));
	close(fd);
	return (1);
}
