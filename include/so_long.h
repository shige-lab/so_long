/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:02:41 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/07 17:10:55 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define E_KEY_PRESS 2
# define E_WIN_RESIZE 9
# define E_WIN_CLOSE 17

# define M_KEY_PRESS 1
# define M_WIN_RESIZE 2097152
# define M_WIN_CLOSE 131072

# define IMAGE_SIZE 32

# define W 119
# define S 115
# define A 97
# define D 100
# define ESC 65307

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

enum	e_components {
	WALL,
	FLOOR,
	PLAYER,
	EXIT,
	COLLECTIBLE
};

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
	size_t	num_collectible;
	size_t	num_exit;
	size_t	num_s_position;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_player
{
	size_t	x;
	size_t	y;
}	t_player;

typedef struct s_game
{
	t_map		map;
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_player	player;
	size_t		move_count;
}	t_game;

char	*get_next_line(int fd);
void	get_map_data(int fd, t_game *game);
void	error_exit(char *message);
void	move_list_to_double_pointer(t_game *game, t_list *map);

int	ft_input(int key, void *game_);
int	close_window(t_game *game);
int	minimize_window(t_game *game);

void	ft_put_image_to_window(t_game *game, size_t x, size_t y);
void	select_image(t_game *game, char c);
void	get_image(t_game *game);
t_bool	can_move(t_game *game, char next_position);

void	ft_put_image_to_window(t_game *game, size_t x, size_t y);
void	select_image(t_game *game, char c);
void	get_image(t_game *game);
t_bool	can_move(t_game *game, char next_position);

#endif