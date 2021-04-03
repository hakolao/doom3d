/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_reload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:58:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/02 17:59:46 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_reload_finish(t_doom3d *app)
{
	if (app->player.equipped_weapon->ammo <
			app->player.equipped_weapon->clip_size)
		app->player.equipped_weapon->clip = app->player.equipped_weapon->ammo;
	else
		app->player.equipped_weapon->clip =
			app->player.equipped_weapon->clip_size;
}

void	player_reload(t_doom3d *app)
{
	if (app->player.equipped_weapon->clip <
		app->player.equipped_weapon->clip_size &&
		app->player.equipped_weapon->clip !=
		app->player.equipped_weapon->ammo)
	{
		app->player.is_reloading = true;
		set_player_reload_frame(app);
	}
}