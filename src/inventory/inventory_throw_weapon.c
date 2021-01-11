/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_throw_weapon.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:14:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 14:05:37 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_throw_weapon(t_doom3d *app)
{
	if (app->player.equipped_item->item != item_fist)
		app->player.equipped_item->ammo = -1;
	if (app->player.equipped_item->item == item_type_melee)
		app->player.item[0] = app->item_data[item_fist];
	app->player.equipped_item = &(app->player.item[item_fist]);
	ft_printf("Threw away item!\n");//test
}