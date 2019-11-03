/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:47:06 by asmall            #+#    #+#             */
/*   Updated: 2019/10/18 17:36:06 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# define M_T 27
# define SIZE_TETRI 20

typedef struct	s_tetris
{
	char		**pos;
	int			length;
	int			height;
}				t_tetris;

typedef struct	s_map
{
	int			size;
	char		**field;
}				t_map;

int				main(int ac, char **av);

/*
**          read_tetri.c
**  Чтение файла, проверка валидности тетрамино, запись тетри в листы.
*/

t_list			*read_tetrimino_from_file(int fd, int flag);
t_tetris		*get_new_cut_tetri(char *tetri_str, int tetri_num);
int				check_connect_and_valids(const char *str, int i, int counter);

/*
**          crop_new.c
** Ширина, высота, заполнение нового массива, где "#" заменены буквами.
*/

int				ft_height_tetri(char *t, int i);
int				ft_length_tetri(char *t, int i);
char			**ft_put_letter(char *str, int hgt, int len, char letter);
int				ft_start_to_fill(char *t, int x);

/*
**          list.c
** Очистка и удаление структуры, заполнение листов, переворот структуры.
*/

t_list			*free_list(t_list *list);
void			free_tetris(t_tetris *tetri);
t_tetris		*tetris_new(char **pos, int width, int height);
t_list			*reverse(t_list *head);

/*
**          map_constructor.c
** Очистка и печать карты + создание новой карты.
*/

void			map_clear(t_map *map);
void			map_print(t_map *map);
t_map			*map_new(int size);

/*
**          sorter.c
** Расчет размера карты, алгоритм поиска с возвратом, проверка валидности
** позиции для тетрамино и размещение/удаление ее на карте.
*/

t_map			*gen_map_and_solve(t_list *list);
int				backtracking_solve(t_map *map, t_list *list);
int				check_place(t_tetris *tetri, t_map *map, int x, int y);
void			set_or_remove_tr(t_tetris *tetri, t_map *map, int x, int y);

#endif
