/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_identifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:09 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/23 14:33:13 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_identifier(char *str, int allow_equal)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (allow_equal && str[i] == '=')
			return (1);
		if (!is_name_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}