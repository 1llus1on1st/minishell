/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:02:12 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 20:00:39 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(void)
{
	char	buffer[4096];

	if (!getcwd(buffer, sizeof(buffer)))
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}
