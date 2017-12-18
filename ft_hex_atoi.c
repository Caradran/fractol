/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:12:47 by esuits            #+#    #+#             */
/*   Updated: 2017/12/17 15:36:37 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

int	ft_hex_atoi(char *str)
{
	int		i;
	int		j;
	long	result;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)
			|| (unsigned)str[i] == 133 || (unsigned)str[i] == 160)
		i++;
	if (ft_strncmp("0x", &str[i], 2))
		return (0);
	i += 2;
	j = i;
	while (str[j])
	{
		if (ft_isalpha(str[j]))
			str[j] = ft_toupper(str[j]);
		j++;
	}
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F'))
	{
		result = result * 16 + str[i] - (ft_isalpha(str[i]) ? 'A' - 10 : '0');
		i++;
	}
	return (result);
}
