/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:48:30 by esuits            #+#    #+#             */
/*   Updated: 2018/01/02 12:14:51 by esuits           ###   ########.fr       */
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
			+ (c2 & (256 / NB_COL * i * 0x010101));
		++i;
	}
	return (tab);
}

int		*ft_palette1(int color1, int color2, int color3, int *tab)
{
	int i;
	int *tab1;
	int *tab2;

	i = -1;
	tab1 = ft_color_smooth(color1, color2);
	tab2 = ft_color_smooth(color2, color3);
	while (++i < NB_COL)
		tab[i] = tab1[i];
	while (i++ < NB_COL * 2)
		tab[i - 1] = tab2[(i - 1) % NB_COL];
	tab[i - 1] = color3;
	ft_memdel((void**)&tab1);
	ft_memdel((void**)&tab2);
	return (tab);
}

int		*ft_rainbow(int *col)
{
	int i;

	i = -1;
	while (++i <= (NB_COL * 2 + 1))
	{
		col[i] = (0xff & (int)(0xff * (1 + sin(i * M_PI / NB_COL)) / 2.))
			+ (0xff00 & (int)(0xff00 *
						(1 + sin(i * M_PI / NB_COL + 2 * M_PI / 3)) / 2.))
			+ (0xff0000 & (int)(0xff0000 *
						(1 + sin(i * M_PI / NB_COL + 4 * M_PI / 3)) / 2.));
	}
	return (col);
}
