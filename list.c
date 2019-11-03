/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:08:12 by asmall            #+#    #+#             */
/*   Updated: 2019/10/15 11:08:14 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_list			*free_list(t_list *list)
{
	t_tetris	*tetris;
	t_list		*next;

	while (list)
	{
		tetris = (t_tetris *)list->content;
		next = list->next;
		free_tetris(tetris);
		ft_memdel((void **)&list);
		list = next;
	}
	return (NULL);
}

/*
** Очистка структур, хранящие тетрамино.
*/

void			free_tetris(t_tetris *tetri)
{
	int y;

	y = 0;
	while (y < tetri->height)
	{
		ft_memdel((void **)(&(tetri->pos[y])));
		y++;
	}
	ft_memdel((void **)(&(tetri->pos)));
	ft_memdel((void **)&tetri);
}

/*
** Создание новой структуры, в которую записываются данные о тетрамино.
*/

t_tetris		*tetris_new(char **pos, int length, int height)
{
	t_tetris	*tetris;

	tetris = ft_memalloc(sizeof(t_tetris));
	tetris->pos = pos;
	tetris->length = length;
	tetris->height = height;
	return (tetris);
}
