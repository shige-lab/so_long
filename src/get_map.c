/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:10:10 by tshigena          #+#    #+#             */
/*   Updated: 2021/11/21 10:25:51 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_list_to_duoble_pointer(t_game *game);
size_t	map_row_len(const char *row);
int		check_map_row_is_valid(char *row, size_t row_lens, t_game *game);
int		check_map_edge_row(char *row);
int		check_map_is_invalid(t_list *map, size_t number_of_rews, t_game *game);

t_game	get_map_data(int fd, t_game *game)
{
	t_list	*map;

	game->map.number_of_rows = 0;
	map = ft_lstnew(get_next_line(fd));
	game->map_tmp = map;
	while (map->content != NULL)
	{
		game->map.number_of_rows++;
		map->next = ft_lstnew(get_next_line(fd));
		map = map->next;
	}
	if (check_map_is_invalid(game->map_tmp, game->map.number_of_rows, game))
		error_exit("invalid map");
	move_list_to_duoble_pointer(game);
	return (*game);
}

int	check_map_edge_row(char *row)
{
	while (*row)
	{
		if (*row != '1' && *row != '\n')
			return (1);
		row++;
	}
	return (0);
}

int	check_map_row_is_valid(char *row, size_t row_lens, t_game *game)
{
	// if (row == NULL)
	// {
	// 	if (!collectible || !s_position || !exit || s_position > 1)
	// 		return (1);
	// 	return (0);
	// }
	if (row[0] != '1' || row[row_lens - 1] != '1')
		return (1);
	while (*row)
	{
		if (ft_strchr("10CPE\n", *row) == NULL)
			return (1);
		if (*row == 'C')
			game->map.num_collectible += 1;
		if (*row == 'P')
			game->map.num_exit += 1;
		if (*row == 'E')
			game->map.num_s_position += 1;
		row++;
	}
	return (0);
}

int	check_map_is_invalid(t_list *map_tmp, size_t number_of_rews, t_game *game)
{
	size_t	i;
	int		error_flag;

	error_flag = 0;
	i = 0;
	game->map.row_lens = map_row_len(map_tmp->content);
	while (map_tmp->content != NULL && error_flag == 0)
	{
		if (i != 0 && game->map.row_lens != map_row_len(map_tmp->content))
		{
			error_flag = 1;
			break ;
		}
		if (i == 0 || i + 1 == number_of_rews)
			error_flag = check_map_edge_row(map_tmp->content);
		else
			error_flag = check_map_row_is_valid(map_tmp->content, game->map.row_lens, game);
		i++;
		map_tmp = map_tmp->next;
	}
	// error_flag += check_map_row_is_valid(NULL, row_lens);
	if (error_flag)
		ft_lstclear(&map_tmp, free);
	return (error_flag);
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

void	move_list_to_duoble_pointer(t_game *game)
{
	size_t	i;
	t_list	*map;

	i = 0;
	game->map.map = (char **)ft_calloc(game->map.number_of_rows + 1, sizeof(char *));
	if (game->map.map == NULL)
	{
		ft_lstclear(&game->map_tmp, free);
		error_exit("failed malloc");
	}
	map = game->map_tmp;
	while (i < game->map.number_of_rows)
	{
		game->map.map[i] = map->content;
		map = map->next;
		i++;
	}
	ft_lstclear(&game->map_tmp, NULL);
}