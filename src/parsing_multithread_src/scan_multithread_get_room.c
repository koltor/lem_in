/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_multithread_get_room.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 20:11:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 19:19:22 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in_thread.h"

static t_bool	check_duplicate_room(UINT id, t_room *r_tab, UINT tab_size)
{
	t_bool	ret;
	t_room	room;

	ret = false;
	room = r_tab[id];
	while (tab_size--)
	{
		if (tab_size != id)
		{
			if (r_tab[tab_size].name && !ft_strcmp(room.name, r_tab[tab_size].name))
				return (*(t_bool*)f_error(ERR_DUPL_ROOM, &ret));
			else if (r_tab[tab_size].name && room.x == r_tab[tab_size].x &&
												room.y == r_tab[tab_size].y)
				return (*(t_bool*)f_error(ERR_DUPL_XY_ROOM, &ret));
		}
	}
	return (true);
}

/*
** split_line_for_room:
**	parameters
**		need a line of the file
**		need a case of the room_tab
**	return value
**		true of the data is collect
**		false otherwise
*/

static t_bool	split_line_for_room(char *line, t_room *room)
{
	long	x1;
	long	y1;
	t_bool	value;

	value = false;
	if (line && *line == 'L')
		return (*(t_bool*)f_error(ERR_ROOM_FORMAT, &value));
	if (!(room->name = ft_strsub_c(line, ' ')))
		return (*(t_bool*)f_error(ERR_MALLOC, &value));
	x1 = atol_id(line, ' ', 1);
	y1 = atol_id(line, ' ', 2);
	if (x1 < -2147483648 || y1 < -2147483648 ||
		x1 > 2147483647 || y1 > 2147483647)
		return (*(t_bool*)f_error(ERR_OVERFLOW, &value));
	room->x = (int)x1;
	room->y = (int)y1;
	return (true);
}

/*
** reset_one_room:
**	reset a room
**	parameters
**		need a room to reset
**	return value
**		false
*/

static t_bool	reset_one_room(t_room *room)
{
	if (room->name)
	{
		free(room->name);
		room->name = NULL;
	}
	room->x = 0;
	room->y = 0;
	return (false);
}

/*
** select_ben (begin-end-normal):
**	parameters
**		need a line
**		need the struct data
**		need the type of line
**		need an & id for moving it
**	return value
**		true of the data is collect
**		false otherwise
*/

static t_bool	select_ben(char *line, t_data *data, int *order, UINT *ir)
{
	t_bool	value;
	UINT 	tmp_id_room;

	value = false;
	if (*order == 1 || *order == 2)
	{
		if (data->r_tab[0].name != NULL && *order == 1)
			return (*(t_bool*)f_error(ERR_DUPLICATE_STR, &value));
		if (data->r_tab[1].name != NULL && *order == 2)
			return (*(t_bool*)f_error(ERR_DUPLICATE_END, &value));
		if (split_line_for_room(line, &data->r_tab[*order - 1]))
			return (false);
		if (check_duplicate_room(*order - 1, data->r_tab, data->rooms))
			return (reset_one_room(&data->r_tab[*order - 1]));
	}
	else if (*order == 0)
	{
		if (*ir >= data->rooms)
			return (false);
		if (split_line_for_room(line, &data->r_tab[*ir]))
			return (false);
		if (check_duplicate_room(*ir, data->r_tab, data->rooms))
			return (reset_one_room(&data->r_tab[*ir]));
		*ir = *ir + 1;
	}
	*order = 0;
	return (true);
}

void	get_room_thread_main(char *file_line, t_data *data, UINT id_thread, UINT section)
{
	char	*line;
	UINT	ir;
	UINT	cpt;
	int		order;
	char	type;

	ir = (section * (id_thread - 1)) + 2;
	order = 0;
	cpt = 0;
	type = 0;
 	while (cpt < section || (id_thread == NB_THREAD && type != -1))
 	{
		line = scan_line_line_for_threading(file_line, id_thread - 1);
		if ((type = is_room(line)) == -1)
			break ;
		if (type == 1 && order == 0 && (order = is_order(line)))
			continue ;
		if (type == 0)
		{
			if (order == 0)
				cpt++;
			if (select_ben(line, data, &order, &ir) && (data->rooms = ir))
				return ;
		}
	}
}