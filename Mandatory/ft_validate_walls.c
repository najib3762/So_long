/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_walls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:18:48 by mrhyhorn          #+#    #+#             */
/*   Updated: 2024/03/05 17:55:12 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_validate_side_walls(t_data *data, int len)
{
	int	h;

	h = 1;
	while (h < data->game->height)
	{
		if (data->game->map[h][0] != '1')
			return (0);
		else if (data->game->map[h][len - 1] != '1')
			return (0);
		h += 1;
	}
	return (1);
}

int	ft_validate_walls(t_data *data, int *h, int *w, int len)
{
	*w = 0;
	while (data->game->map[0][*w] != '\n')
	{
		if (data->game->map[0][*w] != '1')
			return (0);
		*w += 1;
	}
	*w = 0;
	*h = data->game->height - 1;
	while (data->game->map[*h][*w] != '\n' && data->game->map[*h][*w] != '\0')
	{
		if (data->game->map[*h][*w] != '1')
			return (0);
		*w += 1;
	}
	if (!(ft_validate_side_walls(data, len)))
		return (0);
	return (1);
}
