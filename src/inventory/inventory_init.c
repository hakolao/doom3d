/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:50:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/09 15:16:49 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_init(t_doom3d *app)
{
	int	i;

	app->player.item[0] = (t_item) {item_fist, item_type_melee, 0,
									fire_melee, 2};
	app->player.item[1] = (t_item) {item_glock, item_type_sidearm, 20,
									fire_ray, 4};
	i = 2;
	while (i < INVENTORY_SIZE)
	{
		app->player.item[i] = (t_item) {0, 0, -1, 0, 0};
		i++;
	}
	app->player.equipped_item = &(app->player.item[item_type_melee]);
}
