/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <pthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:25:25 by pthuy             #+#    #+#             */
/*   Updated: 2019/10/18 01:20:22 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Создает карту указанного размера.
*/

t_map	*map_new(int size)
{
	t_map	*map;
	int		height;
	int		length;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->size = size;
	map->field = (char **)ft_memalloc(sizeof(char *) * size);
	height = -1;
	while (++height < size)
	{
		map->field[height] = ft_strnew(size);
		length = -1;
		while (++length < size)
			map->field[height][length] = '.';
	}
	return (map);
}

/*
** Очищает созданную структуру карты.
*/

void	map_clear(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->size)
		ft_memdel((void **)&(map->field[i]));
	ft_memdel((void **)&(map->field));
	ft_memdel((void **)&map);
}

/*
** Печатает карту.
*/

void	map_print(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->size)
		ft_putendl(map->field[i]);
}
