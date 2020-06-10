/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:10:55 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 14:35:57 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>

# define BUFFER_SIZE 100

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** PART 1
*/

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, void const *src, size_t n);
void				*ft_memccpy(void *dst, void const *src, int c, size_t n);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
size_t				ft_strlen(char const *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
size_t				ft_strlcpy(char *dst, char const *src, size_t size);
size_t				ft_strlcat(char *dst, char const *src, size_t dstsize);
char				*ft_strnstr(char const *s1, char const *s2, size_t n);
int					ft_atoi(char const *str);
char				*ft_strdup(char const *s1);
void				*ft_calloc(size_t count, size_t size);

/*
** PART 2
*/

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** LIST FUNCTIONS
*/

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),\
					void (*del)(void *));

/*
** MORE
*/

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strcdup(char const *s1, char c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
int					ft_isspace(char c);
int					ft_isupper(int c);
int					ft_islower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_putnbr(int n);
double				ft_absval(double n);
char				*ft_strndup(char const *s, int n);
int					ft_free_str(char **str, int r);
int					get_next_line(int fd, char **line);
int					ft_free_strs(char **strs, int size, int r);
void				*ft_realloc(void *ptr, size_t size);
char				**ft_strsdup(char **strs, size_t size);
char				**ft_strsndup(char **strs, size_t size, int i);
int					get_rgb(int r, int g, int b);
int					get_tab_size(char **t);
char				*ft_str_replace(char *s, char occ, char nocc);
int					ft_is_blank(char *s);
int					ft_isnum_string(char *s);

#endif
