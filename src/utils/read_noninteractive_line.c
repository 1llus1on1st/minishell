/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_noninteractive_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 00:00:00 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/08 00:00:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_input_char(char **line, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(*line, tmp);
	if (!joined)
		return (0);
	free(*line);
	*line = joined;
	return (1);
}

char	*read_noninteractive_line(void)
{
	char	*line;
	char	c;
	int		got;
	ssize_t	ret;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	got = 0;
	ret = read(STDIN_FILENO, &c, 1);
	while (ret > 0)
	{
		got = 1;
		if (c == '\n')
			break ;
		if (!append_input_char(&line, c))
			return (free(line), NULL);
		ret = read(STDIN_FILENO, &c, 1);
	}
	if (ret < 0 || !got)
		return (free(line), NULL);
	return (line);
}
