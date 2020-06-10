/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:17:30 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:37:12 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

/*
**  GENERAL VALUES
*/

# define NAME "Cub3D"
# define BUF_SIZE 100

/*
**  KEY & MOTION VALUES
*/

# define UP 122
# define DOWN 115
# define LEFT 113
# define RIGHT 100
# define QUIT 65307
# define SPACE 32
# define SHOOT 65362
# define LCAM 65361
# define RCAM 65363

# define R_SPEED 0.03
# define M_SPEED 0.03
# define M_RSPEED 0.07

# define RED 0xFF0000
# define GREY 0x808080
# define BLACK 0xFFFFFF

/*
**  ERROR VALUES
*/

# define FILENAME_ERROR -1
# define READ_ERROR -2
# define MEM_ERROR -3
# define RES_ERROR -4
# define TEXT_ERROR -5
# define COLOR_ERROR -6
# define TEXT_MISSING -7
# define RES_MISSING -8
# define MAP_ERROR -9
# define MUL_ERROR -10
# define ARG_ERROR -11

/*
**  STRUCTURES
*/

typedef struct		s_m_parse
{
	char			**m;
	int				x;
	int				y;
	int				wntd;
	char			r;
}					t_m_parse;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
	int				clr;
}					t_rgb;

typedef struct		s_bmp
{
	int				fd;
	unsigned char	fhead[14];
	unsigned char	ihead[40];
	unsigned char	pad[3];
	int				clr;
}					t_bmp;

typedef struct		s_tmp
{
	char			*fsrc;
	void			*img_ptr;
	char			*dt;
	int				bpp;
	int				size;
	int				endn;
	double			size_x;
	double			size_y;
	int				x;
	int				y;
	int				src;
	int				dst;
	int				s;
	int				new_s;
}					t_tmp;

typedef struct		s_img
{
	void			*ptr;
	char			*dt;
	char			*trgt;
	char			*gun;
	int				bpp;
	int				size;
	int				endn;
}					t_img;

typedef struct		s_motion
{
	int				m_up;
	int				m_down;
	int				m_left;
	int				m_right;
	int				t_left;
	int				t_right;
	double			spd;
	int				sht;
}					t_motion;

typedef struct		s_fl
{
	float			rdirx;
	float			rdiry;
	float			rdirxx;
	float			rdiryy;
	int				p;
	float			poz;
	float			row_d;
	float			step_x;
	float			step_y;
	float			fx;
	float			fy;
	int				cx;
	int				cy;
	int				x;
	int				y;
	int				f_clr;
	int				c_clr;
}					t_fl;

typedef struct		s_tx
{
	char			**paths;
	char			*fl_path;
	char			*ce_path;
	void			**pt;
	void			*fl_pt;
	void			*ce_pt;
	void			*trgt_pt;
	void			*gun_pt;
	char			**dt;
	char			*fl_dt;
	char			*ce_dt;
	char			*trgt_dt;
	char			*gun_dt;
	int				bpp;
	int				size;
	int				endn;
	int				w;
	int				h;
	int				x;
	int				y;
	double			w_x;
	double			pos;
	double			step;
}					t_tx;

typedef struct		s_spos
{
	double			x;
	double			y;
}					t_spos;

typedef struct		s_sp
{
	t_spos			*s;
	int				n_sp;
	double			*zbuf;
	double			spx;
	double			spy;
	double			inv;
	double			trx;
	double			try;
	int				scrx;
	int				w;
	int				h;
	int				strtx;
	int				strty;
	int				endx;
	int				endy;
	int				tx;
	int				ty;
}					t_sp;

typedef struct		s_pl
{
	int				strtx;
	int				strty;
	int				endx;
	int				endy;
	int				x;
	int				y;
	int				i;
	int				j;
	char			*pxl;
	int				d;
	int				new_s;
}					t_pl;

typedef struct		s_var
{
	t_motion		m;
	t_img			img;
	t_tx			tx;
	t_fl			fl;
	t_sp			sp;
	void			*mlx;
	void			*win;
	char			**file;
	int				m_strt;
	char			**map;
	int				rx_max;
	int				ry_max;
	int				resx;
	int				resy;
	int				map_w;
	int				map_h;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	int				ray_x;
	int				ray_y;
	double			rdirx;
	double			rdiry;
	double			plnx;
	double			plny;
	int				mapx;
	int				mapy;
	double			camx;
	double			s_dstx;
	double			s_dsty;
	double			d_dstx;
	double			d_dsty;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			w_dst;
	int				line_h;
	int				d_strt;
	int				d_end;
	double			life;
	int				s_gun;
	int				s_trgt;
	int				cnt;
	int				save;
	int				sht;
	int				sprite;
	int				j;
	int				x;
	int				y;
	int				open;
	int				r;
}					t_var;

/*
** Parsing functions
*/

int					check_file(t_var *v, char *map_path);
int					get_info(t_var *v);
char				*init_color(int r, int g, int b);
int					check_map(t_var *v);
int					is_valid(char c);
int					locate_player(t_var *v, t_m_parse *p);
void				init_player(t_var *v, int x, int y, char c);
int					locate_accessible_area(t_var *v, t_m_parse *p);
int					check_contours(t_var *v, t_m_parse *p);
int					check_path_line(char *s);

/*
** Raycasting functions
*/

void				v_init(t_var *v);
void				init_dir(t_var *v, char c);
void				init_plane(t_var *v, char c);
int					last_inits(t_var *v);
void				raycast(t_var *v);
int					get_fl_text(t_var *v, char *line);
void				get_floors(t_var *v, int start, int end, int tx);
void				get_sprites(t_var *v);
void				sort_sprites(t_var *v);

/*
** Motion functions
*/

void				init_motion(t_var *v);
int					move(t_var *v);
int					keys(int key, t_var *v);
int					key_press(int key, t_var *v);
int					key_rel(int key, t_var *v);
void				move_sp(t_var *v, int i);

/*
** Images functions
*/

int					get_text_path(t_var *v, char *s, int i);
int					get_text_data(t_var *v);
void				resize_image(t_var *v, t_tmp *t, void **pt, char **dt);
void				destroy_img(t_var *v);
void				init_steps(t_var *v, t_pl *p, t_tmp *t);

/*
** Drawing functions
*/

void				draw(t_var *v, int x);
void				draw_target(t_var *v);
void				draw_gun(t_var *v);
void				draw_life(t_var *v);

/*
** Exit functions
*/

int					quit(t_var *v);
void				game_over(t_var *v);
void				free_everything(t_var *v);
int					error(int err);
int					partial_free(t_var *v, int r);

/*
** Other functions
*/

void				gunshot(t_var *v, int sht);
void				get_bmp(t_var *v);
void				set_data(t_var *v, int x);
void				set_player(t_var *v);
int					check_params(t_var *v, int ac, char **av);
int					get_screen_size(t_var *v);
#endif
