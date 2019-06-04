/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ui.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/31 15:55:00 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/31 17:35:32 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visu_lem_in.h"

static void other_infomations(t_env env)
{
    int     clr;

    clr = 0xaaaaaa;
    mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 85, clr, "======================");
    mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 105, clr, "colonne envoyes:");
    mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 125, clr, "chemin trouves:");
    mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 145, clr, "numéro de tour:");
}

static void  helping_informations_value(t_env env)
{
    int     clr;
    char    *zoom;
    char    *depl_x;
    char    *depl_y;
    char    *marge;

    clr = 0xaaaaaa;
    zoom = ft_itoa(env.zoom);
    depl_x = ft_itoa(env.x_img);
    depl_y = ft_itoa(env.y_img);
    marge = ft_itoa(env.marge);
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 250, 85, clr, "======================");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 250, 105, clr, "       zoom:");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 100, 105, 0xaa5498, zoom);
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 70, 105, clr, "/100");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 250, 125, clr, "deplacement:    x    y");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 130, 125, 0xaa0000, depl_x);
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 80, 125, 0x00aa00, depl_y);
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 250, 145, clr, " ecartement:");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 120, 145, 0xFF9A09, marge);
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 100, 145, clr, " -2/10");
    free(zoom);
    free(depl_x);
    free(depl_y);
}

static void     helping_informations(t_env env)
{
    int     clr;

    clr = 0xaaaaaa;
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 250, 25, clr, "       zoom: molette");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 250, 45, clr, "deplacement: hgbd/wasd");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 250, 65, clr, "      marge: + / -");
}

static void     number_information(t_env env, char *nb_ants, char *nb_rooms, char *nb_tubes)
{
    int     clr;

    clr = 0xaaaaaa;
    if (WIN_SIZE_X > 700)
    {
        mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 5, clr, "nombre de fourmis:");
        mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 45, clr, "nombre de liaisons:");
        mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 25, clr, "nombre de salles:");
        mlx_string_put(env.mlx_ptr, env.win_ptr, 210, 5, clr, nb_ants);
        mlx_string_put(env.mlx_ptr, env.win_ptr, 210, 25, clr, nb_rooms);
        mlx_string_put(env.mlx_ptr, env.win_ptr, 210, 45, clr, nb_tubes);
    }
    else
    {
        mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 5, clr, "fourmis:");
        mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 45, clr, "liaisons:");
        mlx_string_put(env.mlx_ptr, env.win_ptr, 5, 25, clr, "salles:");
        mlx_string_put(env.mlx_ptr, env.win_ptr, 110, 5, clr, nb_ants);
        mlx_string_put(env.mlx_ptr, env.win_ptr, 110, 25, clr, nb_rooms);
        mlx_string_put(env.mlx_ptr, env.win_ptr, 110, 45, clr, nb_tubes);
    }
}

static void    first_informations(t_env env)
{
    int     clr;
    char    *nb_ants;
    char    *nb_rooms;
    char    *nb_tubes;

    clr = 0xaaaaaa;
    nb_ants = ft_itoa(env.data->ants);
    nb_rooms = ft_itoa(env.data->rooms);
    nb_tubes = ft_itoa(env.data->tubes);
    number_information(env, nb_ants, nb_rooms, nb_tubes);
    free(nb_ants);
    free(nb_rooms);
    free(nb_tubes);
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 180, 5, clr, "aide: h");
    mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X / 2 - 70, 5, clr, "quitter: esc    reset: r");
    if (env.help)
        mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 100, 5, clr, "(inactif)");
    else
        mlx_string_put(env.mlx_ptr, env.win_ptr, WIN_SIZE_X - 100, 5, clr, "(actif)");
}

static void legendary(t_env env)
{
	mlx_string_put(env.mlx_ptr, env.win_ptr, 5, WIN_SIZE_Y - 20, 0x00ff00, "GREEN:");
	mlx_string_put(env.mlx_ptr, env.win_ptr, 75, WIN_SIZE_Y - 20, 0xaaaaaa, "debut de la fourmiliere");
	mlx_string_put(env.mlx_ptr, env.win_ptr, 345, WIN_SIZE_Y - 20, 0xff0000, "RED:");
	mlx_string_put(env.mlx_ptr, env.win_ptr, 390, WIN_SIZE_Y - 20, 0xaaaaaa, "fin de la fourmiliere");
	mlx_string_put(env.mlx_ptr, env.win_ptr, 630, WIN_SIZE_Y - 20, 0xffffff, "WHITE:");
	mlx_string_put(env.mlx_ptr, env.win_ptr, 700, WIN_SIZE_Y - 20, 0xaaaaaa, "salle");
	mlx_string_put(env.mlx_ptr, env.win_ptr, 790, WIN_SIZE_Y - 20, 0x5E450E, "BROWN:");
	mlx_string_put(env.mlx_ptr, env.win_ptr, 870, WIN_SIZE_Y - 20, 0xaaaaaa, "liaisons");
}

void    user_interface(t_env env)
{
    if (!env.help)
    {
		legendary(env);
        helping_informations(env);
        helping_informations_value(env);
        other_infomations(env);
    }
    first_informations(env);
}