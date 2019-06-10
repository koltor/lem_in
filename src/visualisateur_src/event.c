/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 15:52:28 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/05 17:33:34 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

static void	reset(t_env *env)
{
	env->marge = 4;
	env->zoom = 50;
	env->help = false;
	env->highlight_path = false;
	env->x_img = WIN_SIZE_X / 4;
	env->y_img = WIN_SIZE_Y / 4;
}

int			keyboard_events(int key, void *data)
{
	t_env *env;

	env = (t_env*)data;
	if (key == ESC)
		exit(0);
	if (key == LESS && env->marge > 0)
		env->marge -= 3;
	else if (key == PLUS && env->marge < 10)
		env->marge += 3;
	else if (key == DOWN || key == S)
		env->x_img += 3;
	else if (key == UP || key == W)
		env->x_img -= 3;
	else if (key == LEFT || key == A)
		env->y_img -= 3;
	else if (key == RIGHT || key == D)
		env->y_img += 3;
	else if (key == H)
		env->help = (env->help) ? true : false;
	else if (key == R)
		reset(env);
	else if (key == L)
		env->highlight_path = (env->highlight_path) ? true : false;
	put_img(env, *(env->data));
	return (0);
}

int			mouse_events(int button, int x, int y, void *data)
{
	t_env *env;

	env = (t_env*)data;
	if (button == ZOOM_IN && env->zoom < 100)
	{
		env->zoom += 1;
		put_img(env, *(env->data));
	}
	else if (button == ZOOM_OUT && env->zoom > 1)
	{
		env->zoom -= 1;
		put_img(env, *(env->data));
	}
	return (0);
}