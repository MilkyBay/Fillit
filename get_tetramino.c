/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetramino.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:51:39 by asmall            #+#    #+#             */
/*   Updated: 2019/10/18 17:56:30 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Проверка валидности файла после считывания 21 символа. Считаем
** количество символов строки, проверяем символы на "." "#" и "\n".
** Проверяем фигуры на соответствие тетрамино.
*/

int				check_connect_and_valids(const char *str, int i, int counter)
{
	int			side;

	side = 0;
	while (i < 20)
	{
		if (str[i] == '#' && counter++ < 4)
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				side++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				side++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				side++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				side++;
			i++;
		}
		else if ((str[i] == '.' && (i + 1) % 5 != 0)
				|| ((i + 1) % 5 == 0 && str[i] == '\n'))
			i++;
		else
			return (0);
	}
	return ((side == 6 || side == 8) ? 1 : 0);
}

/*
** Считаем высоту и ширину валидной фигуры тетрамино, создаём под параметры
** массив. Помещаем в новый массив обрезанную фигуру тетрамино, где '#' заменены
** нужной буквой алфавита.
*/

t_tetris		*get_new_cut_tetri(char *tetri_str, int tetri_num)
{
	int			hgt;
	int			len;
	char		**new_tetri;
	t_tetris	*tetri;

	tetri_str[SIZE_TETRI] = '\0';
	hgt = ft_height_tetri(tetri_str, 0);
	len = ft_length_tetri(tetri_str, 0);
	new_tetri = ft_put_letter(tetri_str, hgt, len, 64 + tetri_num);
	tetri = tetris_new(new_tetri, len, hgt);
	return (tetri);
}

/*
** Считываем из файла 21 символ и отправляем их на валидацию. Если валидация
** успешна, вынимаем из строки с 21 символом фигуру тетрамино.
** Записываем итоговую тетрамину в лист структуры. Возвращаем готовую структуру.
*/

t_list			*read_tetrimino_from_file(int fd, int flag)
{
	t_tetris	*tetri;
	t_list		*list;
	char		buf[21];
	int			count;
	size_t		tetri_num;

	tetri_num = 0;
	list = NULL;
	ft_bzero(buf, 21);
	while ((count = read(fd, buf, 21)) >= 20)
	{
		if (((check_connect_and_valids(buf, 0, 0) == 0) ||
				(count == 21 && buf[20] != '\n')))
			return (free_list(list));
		if ((count == 20 && buf[20] == '\0'))
			flag = 1;
		tetri = get_new_cut_tetri(buf, ++tetri_num);
		ft_lstadd(&list, ft_lstnew(tetri, sizeof(t_tetris)));
		ft_memdel((void **)&tetri);
		ft_bzero(buf, 21);
	}
	if ((close(fd) == -1) || (count != 0) || (tetri_num >= M_T) || (flag == 0)
		|| (tetri_num != ft_lstcount(list)))
		return (free_list(list));
	return (ft_lstrev(list));
}
