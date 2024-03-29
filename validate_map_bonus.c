/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:00:20 by namoussa          #+#    #+#             */
/*   Updated: 2024/03/16 15:50:54 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/header_bonus.h"

int	check_conditions(char ch, int count)
{
	if ((ch == 'P' || ch == 'E') && (count > 1 || count == 0))
		return (0);
	else if (count == 0)
		return (0);
	return (1);
}

int	ft_check_char(t_data *data, char ch, int *count)
{
	int	h;
	int	w;

	*count = 0;
	h = -1;
	while (++h < data->game->height)
	{
		w = -1;
		while (data->game->map[h][++w] != '\0')
		{
			if (data->game->map[h][w] == 'P')
			{
				data->game->player_x = w;
				data->game->player_y = h;
			}
			if (data->game->map[h][w] == 'E')
			{
				data->game->exit_x = w;
				data->game->exit_y = h;
			}
			if (data->game->map[h][w] == ch)
				*count += 1;
		}
	}
	return (check_conditions(ch, *count));
}

int	ft_check_chars(t_data *data)
{
	int	h;
	int	w;

	h = 0;
	while (h < data->game->height)
	{
		w = 0;
		while (data->game->map[h][w] != '\n' && data->game->map[h][w] != '\0')
		{
			if (ft_strchr("01CEPV", data->game->map[h][w]) == 0)
				return (0);
			w++;
		}
		h++;
	}
	return (1);
}

int	ft_check_every_char(t_data *data)
{
	int	count;

	if (!(ft_check_chars(data)))
		return (INVALID_CHARS);
	if (!(ft_check_char(data, 'P', &count)))
		return (PLAYER_ERROR);
	if (!(ft_check_char(data, 'E', &count)))
		return (EXIT_ERROR);
	if (!(ft_check_char(data, 'C', &count)))
		return (COLLECT_ERROR);
	else
		data->game->collect = count;
	if ((ft_check_char(data, 'V', &count)))
		data->game->enemy_num = count;
	else
		return (INVALID_CHARS);
	return (VALID);
}

int	ft_validate_map(t_data *data)
{
	int	h;
	int	w;
	int	len;
	int	out;
	int	height;

	len = ft_strlen_nl(data->game->map[0]);
	height = data->game->height;
	if ((height * ASSET_SIZ) > 2160 || (len * ASSET_SIZ) > 2460)
		print_error_free("Error\nmax size\n", data);
	h = 0;
	while (h < data->game->height)
	{
		if (len != (ft_strlen_nl(data->game->map[h])))
			return (INVALID_RECT);
		h++;
	}
	data->game->width = len;
	if (!(ft_validate_walls(data, &h, &w, len)))
		return (INVALID_WALLS);
	out = ft_check_every_char(data);
	if (out > 0)
		return (out);
	flood_fill(data, data->game->player_x, data->game->player_y);
	return (check_flood_fill(data));
}
