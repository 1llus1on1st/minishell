/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:15:22 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:15:23 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exit_code(long long *code, unsigned long long value, int sign)
{
	if (sign == -1 && value == 9223372036854775808ULL)
		*code = -9223372036854775807LL - 1;
	else if (sign == -1)
		*code = -(long long)value;
	else
		*code = (long long)value;
}