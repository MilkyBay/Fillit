/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <pthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:25:22 by pthuy             #+#    #+#             */
/*   Updated: 2019/10/18 17:36:33 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Входная точка алгоритма для решения задачи.
** На первой итерации пробует решить задачу с использованием минимально
** возможного размера карты.
*/

t_map			*gen_map_and_solve(t_list *list)
{
	t_map		*map;
	int			size;
	int			len;

	len = ft_lstcount(list);
	size = 2;
	while (size * size < len * 4)
		size++;
	if (!(map = map_new(size)))
		return (NULL);
	while (!backtracking_solve(map, list))
	{
		map_clear(map);
		map = map_new(++size);
	}
	return (map);
}

/*
** Алгоритм поиска с возвратом.
*/

int				backtracking_solve(t_map *map, t_list *list)
{
	int			j;
	int			i;
	t_tetris	*tetramino;

	if (!list)
		return (1);
	tetramino = (t_tetris *)(list->content);
	j = -1;
	while (++j < map->size - tetramino->height + 1)
	{
		i = -1;
		while (++i < map->size - tetramino->length + 1)
		{
			if (check_place(tetramino, map, i, j))
			{
				if (backtracking_solve(map, list->next))
					return (1);
				else
					set_or_remove_tr(tetramino, map, i, j);
			}
		}
	}
	return (0);
}

/*
** Проверяет позицию для установки тетрамино. Если позиция подходящая, то
** запускает функцию для установки тетрамино.
*/

int				check_place(t_tetris *tetramino, t_map *map, int i, int j)
{
	int			y;
	int			x;

	y = -1;
	while (++y < tetramino->height)
	{
		x = -1;
		while (++x < tetramino->length)
			if (tetramino->pos[y][x] != '.' && map->field[j + y][i + x] != '.')
				return (0);
	}
	set_or_remove_tr(tetramino, map, i, j);
	return (1);
}

/*
** Устанавливает тетрамино на карту.
** Так же используется для очистки невалидно-установленного тетрамино.
** Очистка происходит, при повторном запуске функции с теми же параметрами.
*/

void			set_or_remove_tr(t_tetris *tetramino, t_map *map, int i, int j)
{
	int			y;
	int			x;

	y = -1;
	while (++y < tetramino->height)
	{
		x = -1;
		while (++x < tetramino->length)
			if (tetramino->pos[y][x] != '.' && map->field[j + y][i + x] != '.')
				map->field[j + y][i + x] = '.';
			else if (tetramino->pos[y][x] != '.')
				map->field[j + y][i + x] = tetramino->pos[y][x];
	}
}
