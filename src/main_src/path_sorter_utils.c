#include "lem_in.h"

UINT	get_pnum(UINT pid, t_data *data)
{
	UINT i;
	UINT ret;

	i = 0;
	ret = 0;
	while (data->paths[i])
	{
		if (data->paths[i][0] == pid)
			ret++;
		i++;
	}
	return (ret);
}

UINT	get_min_pid(t_data *data, UINT max_paths)
{
	UINT i;
	UINT ret;

	i = 1;
	ret = data->paths[0][0];
	if (max_paths == 1)
		return (ret);
	while (i < max_paths)
	{
		if (data->paths[i][0] < ret)
			ret = data->paths[i][0];
		i++;
	}
	return (ret);
}

UINT	get_max_pid(t_data *data, UINT max_paths)
{
	UINT i;
	UINT ret;

	i = 1;
	ret = data->paths[0][0];
	if (max_paths == 1)
		return (ret);
	while (i <= max_paths)
	{
		if (data->paths[i][0] > ret)
			ret = data->paths[i][0];
		i++;
	}
	return (ret);
}

UINT	get_size_valid_tab(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		if ((*res)[i] != data->path_nbr && data->paths[(*res)[i]][0] != 0)
		{
			data->paths[(*res)[i]][0] = 0;
			return (data->paths[(*res)[i]][1] - 4);
		}
		i++;
	}
	return (0);
}

UINT	get_index_valid_tab(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT i;

	i = 0;
	while (i < max_paths)
	{
		if ((*res)[i] != data->path_nbr && data->paths[(*res)[i]][0] != 0)
			return (i);
		i++;
	}
	return (0);
}
