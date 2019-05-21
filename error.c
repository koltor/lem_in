/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 16:28:01 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 19:19:09 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	usage(void)
{
	ft_putstr("lem-in: [anthill_file]\n");
}

void	*f_error(char value, void *data)
{
	static char errno = 0;

	if (value > 0)
		errno = value;
	else if (value == 0)
		return ((void*)&errno);
	return (data);
}
