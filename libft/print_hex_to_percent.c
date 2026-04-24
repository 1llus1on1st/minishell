/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_to_percent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:04:17 by mshargan          #+#    #+#             */
/*   Updated: 2025/12/01 11:34:07 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_u_decimal(va_list args)
{
	char	*str_num;
	int		count;

	str_num = ft_uitoa(va_arg(args, unsigned int));
	ft_putstr_fd(str_num, 1);
	count = ft_strlen(str_num);
	free(str_num);
	return (count);
}

int	print_lower_hex(va_list args)
{
	int		count;
	char	*str_hex;

	count = 0;
	str_hex = ft_htoa(va_arg(args, unsigned int));
	ft_putstr_fd(str_hex, 1);
	count = ft_strlen(str_hex);
	free(str_hex);
	return (count);
}

int	print_upper_hex(va_list args)
{
	int		count;
	char	*str_hex;
	int		i;

	count = 0;
	i = 0;
	str_hex = ft_htoa(va_arg(args, int));
	while (str_hex[i])
	{
		str_hex[i] = ft_toupper(str_hex[i]);
		i++;
	}
	ft_putstr_fd(str_hex, 1);
	count = ft_strlen(str_hex);
	free(str_hex);
	return (count);
}

int	print_percent(void)
{
	write(1, "%%", 1);
	return (1);
}
