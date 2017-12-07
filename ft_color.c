/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:48:30 by esuits            #+#    #+#             */
/*   Updated: 2017/12/07 20:58:40 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

int		*ft_color_smooth(int c1, int c2)
{
	int *tab;
	int i;

	if (!(tab = malloc(sizeof(int) * NB_COL)))
		return (NULL);
	i = 0;
	while (i < NB_COL)
	{
		tab[i] = (c1 & (0xffffff - 256 / NB_COL * i * 0x010101))
			+ (c2 & ( 256 / NB_COL * i * 0x010101));
		i++;
	}
	return (tab);
}

int		*ft_palette1(int j, int color1, int color2, int color3)
{
	int i;
	int *tab1;
	int *tab2;
	int *tab;

	i = -1;
	if (!(tab = malloc(sizeof(int) * NB_COL * 2 + 1)))
		return (NULL);
	tab1 = ft_color_smooth(color1, color2);
	tab2 = ft_color_smooth(color2, color3);
	while (++i < NB_COL)
		tab[i] = tab1[i % NB_COL];
	while (++i <= NB_COL * 2)
		tab[i - 1] = tab2[(i - NB_COL) % NB_COL];
	ft_memdel((void**)&tab1);
	ft_memdel((void**)&tab2);
	tab[NB_COL * 2] = 0;
	return (tab);
}
