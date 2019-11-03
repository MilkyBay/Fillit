/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crop_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:58:58 by asmall            #+#    #+#             */
/*   Updated: 2019/10/12 14:59:00 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** i - бегает по столбцу, пока не встретит '#'. y - получает номер строки,
** в которой встречается первый '#'. Функция возвращает индекс с которого нужно
** начать копировать.
*/

int			ft_start_to_fill(char *t, int x)
{
	int		y;
	int		i;

	while (x < 5)
	{
		y = 1;
		while (y < 5)
		{
			i = y * 4 + y + x - 6;
			if (t[i] == '#')
				break ;
			y++;
		}
		if (t[i] == '#')
			break ;
		x++;
	}
	i = 0;
	while (t[i] != '#')
		i++;
	y = 1 + (i / 5);
	i = y * 4 + y + x - 6;
	return (i);
}

/*
** i - принимает значение столбца, с которого начинается копирование.
** j - бегает по строкам обрезанного массива. Зная высоту тетрамино -
** заполняем новый массив '.', а '#' заменяем буквой алфавита.
*/

char		**ft_put_letter(char *str, int hgt, int len, char letter)
{
	char	**new_tetri;
	int		step;
	int		i;
	int		count;

	count = -1;
	i = ft_start_to_fill(str, 1);
	new_tetri = (char **)ft_memalloc(sizeof(char *) * hgt);
	while (++count < hgt)
	{
		new_tetri[count] = (char*)ft_memalloc(len + 1);
		step = 0;
		while (step < len)
		{
			if (str[i + step] == '#')
				new_tetri[count][step] = letter;
			else
				new_tetri[count][step] = '.';
			step++;
		}
		new_tetri[count][len] = '\0';
		i = i + 5;
	}
	return (new_tetri);
}

/*
** Считает максимальную высоту фигуры тетриса.
*/

int			ft_height_tetri(char *tetri, int i)
{
	int		height_max;

	height_max = 0;
	while (i < 19)
	{
		if (tetri[i] == '#')
		{
			height_max++;
			while (tetri[i] != '\n')
				i++;
		}
		i++;
	}
	return (height_max);
}

/*
** Считает максимальную ширину фигуры тетриса.
*/

int			ft_length_tetri(char *tetri, int i)
{
	int		x;
	int		y;
	int		length_max;

	x = 1;
	length_max = 0;
	while (x < 5 && length_max != 4)
	{
		y = 1;
		while (y < 5)
		{
			i = y * 4 + y + x - 6;
			if (tetri[i] == '#')
			{
				length_max++;
				break ;
			}
			y++;
		}
		x++;
	}
	return (length_max);
}
