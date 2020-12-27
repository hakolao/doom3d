/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:04:12 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/22 23:36:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			read_level_list(t_doom3d *app)
{
	int32_t		fd;
	const char	*level_list;
	int32_t		i;

	ft_memset(app->level_list, 0, sizeof(char*) * MAX_LEVELS);
	level_list = "assets/map_data/level_list.txt";
	if ((fd = open(level_list, O_RDONLY)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", level_list))
		return ;
	i = 0;
	while (get_next_line(fd, &app->level_list[i]))
		i++;
	app->num_levels = i;
}