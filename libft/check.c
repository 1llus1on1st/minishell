/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:31:52 by mshargan          #+#    #+#             */
/*   Updated: 2025/12/06 15:52:50 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	percent_check(const char **s)
{
	if (**s == '%')
	{
		return (1);
	}
	return (0);
}

int	flag_check(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	conversion_check(const char *s, t_conv_list *flags)
{
	if (*(s + 1) == 'c')
		flags->character = 1;
	else if (*(s + 1) == 's')
		flags->string = 1;
	else if (*(s + 1) == 'p')
		flags->pointer = 1;
	else if (*(s + 1) == 'd')
		flags->decimal = 1;
	else if (*(s + 1) == 'i')
		flags->integer = 1;
	else if (*(s + 1) == 'u')
		flags->u_decimal = 1;
	else if (*(s + 1) == 'x')
		flags->lower_hex = 1;
	else if (*(s + 1) == 'X')
		flags->upper_hex = 1;
	else if (*(s + 1) == '%')
		flags->percent = 1;
	if (flag_check(*s))
	{
		flags->conv = 1;
		return (1);
	}
	return (0);
}

int	trailing_percent_check(const char *s)
{
	int	i;
	int	percent_count;

	i = 0;
	percent_count = 0;
	while (s[i])
		i++;
	if (i == 0)
		return (0);
	else if (i == 1 && s[0] == '%')
		return (1);
	while (s[i - 1] == '%' && i > 0)
	{
		i--;
		percent_count++;
	}
	if (percent_count % 2 != 0)
		return (1);
	return (0);
}

int	initial_check(const char *s)
{
	if (!s)
		return (-1);
	else if (trailing_percent_check(s))
		return (-1);
	return (1);
}
