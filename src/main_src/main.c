/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:35:25 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 15:52:20 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>
#include <sys/time.h>

static void		manage_option(t_data *data, int option)
{
	O_D || O_I ? global_info(data) : 0;
	O_D ? debug_lem_in(data) : 0;
	O_V ? main_visualisateur(*data) : 0;
}

/*
** exit_lem_in_error:
**	parameters
**		need elements for free
**	return value
**		return false
*/

static t_bool	exit_lem_in_error(char *line, char *line2, t_room *room, t_tube *tube)
{
	if (line)
		free(line);
	if (line2)
		free(line);
	if (room)
		free(room);
	if (tube)
		free(tube);
	return (false);
}

/*
** exit_lem_in_ok:
**	parameters
**		need elements for free
**	return value
**		return true
*/

static t_bool	exit_lem_in_ok(char *file_line, t_data *data)
{
	free(file_line);
	free(data->t_tab);
	free_room(data->r_tab, data->rooms);
	ft_strdel(&(data->opt));
	del_2d_int_tab(data->ret);
	del_2d_int_tab(data->paths);
	return (true);
}

/*
** lem_in:
**	parameters
**		the path of the file given in parameters
**		the option given
**	variable
**		char *file_line to stock the file after transform in string
**		struct data to stock it
**	return value
**		return true if the file_line is in good format
**		and enough information collect
**		otherwise return false
*/

t_bool			lem_in(const char *path, int option)
{
	char	*file_line;
	t_data	data;

	if (!(file_line = parsing_into_line(path)))
	{
		if (*(char*)f_error(0, NULL) == 0)
			f_error(ERR_EMPTY_FILE, NULL);
		return (exit_lem_in_error(file_line, NULL, NULL, NULL));
	}
	stock_file_line(&data, file_line);
	if ((data.rooms = get_number_of_room(file_line)) < 2)
		return (exit_lem_in_error(file_line, data.bopt, NULL, NULL));
	if ((data.tubes = get_number_of_tube(file_line)) < 1)
		return (exit_lem_in_error(file_line, data.bopt, NULL, NULL));
	if (!(data.r_tab = create_room(data.rooms)))
		return (exit_lem_in_error(file_line, data.bopt, NULL, NULL));
	if (!(data.t_tab = create_tube(data.tubes)))
		return (exit_lem_in_error(file_line, data.bopt, data.r_tab, NULL));
	get_abc_for_room(file_line, &data.abc.abc_len);
	get_abc_id_for_room(&data.abc.abc_start, data.abc.abc_len);
	get_abc_id_for_room(&data.abc.abc_id, data.abc.abc_len);
	if (O_M)
	{
		if (stock_anthill_for_threading(file_line, &data))
			return (exit_lem_in_error(file_line, data.bopt, data.r_tab, data.t_tab));
	}
	else
	{
		if (stock_anthill(file_line, &data))
			return (exit_lem_in_error(file_line, data.bopt, data.r_tab, data.t_tab));
	}
	if (browse_map(&data))
		return (exit_lem_in_error(file_line, data.bopt, data.r_tab, data.t_tab));
	manage_option(&data, option);
	return (exit_lem_in_ok(file_line, &data));
}

/*
**main:
**	first function call after exect the programm
**	parameters
**		int		ac	number of argument
**		char	**a	arguments
**	variable
**		int for stock options
*/

int				main(int ac, char **av)
{
	int				option;

	if (ac >= 2)
	{
		av = get_option(ac - 1, &av[1], &option);
		if (lem_in(*av, option) && !O_D && !O_I)
			str_error(*(char*)f_error(0, NULL));
	}
	else
		usage();
	if (O_D || O_I)
		debug_main(option);
	return (0);
}
