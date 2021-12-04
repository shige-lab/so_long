/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:02:41 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/04 20:41:06 by tshigena         ###   ########.fr       */
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

enum	e_basic_tex_path {
	WALL,
	FLOOR,
	EXIT,
	SPRITE,
};

typedef struct s_map
{
	char	**map;
	size_t	row_lens;
	size_t	number_of_rows;
	size_t	num_collectible;
	size_t	num_exit;
	size_t	num_s_position;
	int	p_x_position;
	int	p_y_position;
}	t_map;

typedef struct s_tex
{
	int				*addr;
	int				w;
	int				h;
}					t_tex;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		line_length;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_plyaer
{
	int	x_position;
	int	y_position;
	int	x_move_flag;
	int	y_move_flag; 
}				t_plyaer;

typedef struct s_game
{
	t_map		map;
	t_list		*map_tmp;
	void		*mlx;
	void		*mlx_win;
	t_tex		tex[5];
	t_img		img;
	t_plyaer	player;
	int			move_count;
}	t_game;

char	*get_next_line(int fd);
t_game	get_map_data(int fd, t_game *game);
void	error_exit(char *message);

#endif