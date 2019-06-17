/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 11:24:26 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/17 13:48:46 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

UINT	path_counter(t_data *data)
{
	UINT tab_id[data->r_tab[1].nb_link_tubes];
	UINT i;
	UINT j;
	UINT ret;
	UINT bol;

	i = 0;
	ret = 0;
	bol = 0;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		tab_id[i] = data->t_tab[data->r_tab[1].link_tubes[i]].path_id;
		i++;
	}
	i = 0;
	if (tab_id[0] != 0)
		ret++;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		j = i + 1;
		while (j < data->r_tab[1].nb_link_tubes)
		{
			if (j != i && tab_id[j] != tab_id[i] && tab_id[j] != 0)
			{
				bol++;
				ret++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

UINT	find_smallest_path(t_data *data)
{
	UINT i;
	t_bool test;
	UINT ret;
	UINT smallest;

	i = 0;
	test = false;
	while (data->t_tab[data->r_tab[1].link_tubes[i]].path_id == 0 &&
			i < data->r_tab[1].nb_link_tubes)
		i++;
	ret = i;
	smallest = data->t_tab[data->r_tab[1].link_tubes[i]].turn;
	while (i < data->r_tab[1].nb_link_tubes)
	{
		if (smallest < data->t_tab[data->r_tab[1].link_tubes[i]].turn &&
				data->t_tab[data->r_tab[1].link_tubes[i]].used == false)
		{
			smallest = data->t_tab[data->r_tab[1].link_tubes[i]].turn;
			ret = i;
		}
		i++;
	}
	return (ret);
}


void	malloc_path_tabs(t_data *data)
{
	UINT i;
	UINT index;

	i = 0;
	while (data->paths[i] != NULL)
	{
		index = find_smallest_path(data);
		data->t_tab[data->r_tab[1].link_tubes[index]].used = true;
		if (!(data->paths[i] = (UINT*)malloc(sizeof(UINT) * (data->t_tab[data->r_tab[1].link_tubes[index]].turn + 1))))
		{
			f_error(ERR_MALLOC, NULL);
			return ;
		}
		data->paths[i][0] = data->t_tab[data->r_tab[1].link_tubes[index]].path_id;
		i++;
	}
}


void	print_malloc_tab(t_data *data)
{
	int i;

	i = 0;
	while (data->paths[i] != NULL)
	{
		printf("tab n* %u path_id = %u\n", i, data->paths[i][0]);
		i++;
	}
}

void	fill_path_tab(t_data *data)
{
	int path_nb;

	path_nb = path_counter(data);
	data->path_nbr = path_nb;
	printf("path counter = %u\n", path_counter(data));
	if (!(data->paths = (UINT**)malloc(sizeof(UINT*) * (path_counter + 1))))
	{
		f_error();
		return (f_error(ERR_MALLOC, NULL));
	}
	paths[path_counter] = NULL;
	malloc_path_tabs(data);
	print_malloc_tab(data);
}
