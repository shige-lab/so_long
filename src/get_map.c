/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:10:10 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/05 15:16:08 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_list_to_duoble_pointer(t_game *game, t_list *map);
size_t	map_row_len(const char *row);
t_bool	check_middle_row(char *row, size_t width, t_game *game);
t_bool	check_edge_row(char *row);
t_bool	get_map_info(t_list *map, size_t number_of_rews, t_game *game);

t_game	get_map_data(int fd, t_game *game)
{
	t_list	*map;
	t_list	*tmp;

	game->map.length = 0;
	tmp = ft_lstnew(get_next_line(fd));
	map = tmp;
	while (tmp->content != NULL)
	{
		game->map.length++;
		tmp->next = ft_lstnew(get_next_line(fd));
		tmp = tmp->next;
	}
	if (get_map_info(map, game->map.length, game) == FALSE)
		error_exit("invalid map");
	move_list_to_duoble_pointer(game, map);
	return (*game);
}

t_bool	check_edge_row(char *row)
{
	while (*row)
	{
		if (*row != '1' && *row != '\n')
			return (FALSE);
		row++;
	}
	return (TRUE);
}

t_bool	check_middle_row(char *row, size_t width, t_game *game)
{
	if (row[0] != '1' || row[width - 1] != '1')
		return (FALSE);
	while (*row)
	{
		if (ft_strchr("10CPE\n", *row) == NULL)
			return (FALSE);
		if (*row == 'C')
			game->map.num_collectible += 1;
		if (*row == 'P')
		{
			game->map.num_exit += 1;
			if (game->map.num_exit > 1)
				return (1);
		}
		if (*row == 'E')
			game->map.num_s_position += 1;
		row++;
	}
	return (TRUE);
}

t_bool	get_map_info(t_list *map, size_t number_of_rews, t_game *game)
{
	size_t	i;
	t_bool	is_valid;
	t_list	*tmp;

	is_valid = TRUE;
	i = 0;
	game->map.width = map_row_len(map->content);
	tmp = map;
	while (tmp->content != NULL && is_valid == TRUE)
	{
		if (i != 0 && game->map.width != map_row_len(tmp->content))
		{
			is_valid = FALSE;
			break ;
		}
		if (i == 0 || i + 1 == number_of_rews)
			is_valid = check_edge_row(tmp->content);
		else
			is_valid = check_middle_row(tmp->content, game->map.width, game);
		i++;
		tmp = tmp->next;
	}
	if (is_valid == FALSE)
	{
		ft_lstclear(&map, free);
		return (FALSE);
	}
	return (TRUE);
}

size_t	map_row_len(const char *row)
{
	size_t	i;

	i = 0;
	while (*row != '\0')
	{
		if (ft_strchr("10CPE", *row))
			i++;
		row++;
	}
	return (i);
}

void	move_list_to_duoble_pointer(t_game *game, t_list *map)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	game->map.map = (char **)ft_calloc(game->map.length + 1, sizeof(char *));
	if (game->map.map == NULL)
	{
		ft_lstclear(&map, free);
		error_exit("failed malloc");
	}
	tmp= map;
	while (i < game->map.length)
	{
		game->map.map[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&map, NULL);
}
