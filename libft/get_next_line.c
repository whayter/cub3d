/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:28:06 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/27 19:28:29 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		set_line(char **stock, char **line)
{
	int		i;
	char	*tmp;

	if (!(tmp = ft_strdup(*stock)))
		return (-1);
	i = 0;
	while (tmp[i] != '\n' && tmp[i])
		i++;
	if (!(*line = ft_strndup(*stock, i)))
		return (ft_free_str(&tmp, -1));
	ft_free_str(stock, 0);
	if (tmp[i] != '\0')
		if (!(*stock = ft_strdup(&(tmp)[i + 1])))
			return (ft_free_str(&tmp, -1));
	ft_free_str(&tmp, 0);
	return (i);
}

int		read_file(int fd, char **stock)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strdup(*stock);
		ft_free_str(stock, 0);
		if (!(*stock = ft_strjoin(tmp, buf)))
			return (ft_free_str(&tmp, -1));
		ft_free_str(&tmp, 0);
		if (ft_strchr(*stock, '\n'))
			break ;
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char		*stock;
	int				ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!stock)
		if (!(stock = ft_strdup("")))
			return (ft_free_str(&stock, -1));
	if (!(ft_strchr(stock, '\n')))
		if ((read_file(fd, &stock)) == -1)
			return (ft_free_str(&stock, -1));
	if ((ret = set_line(&stock, line)) == -1)
		return (ft_free_str(&stock, -1));
	if (ret == 0 && !stock)
	{
		ft_free_str(line, 0);
		return (0);
	}
	return (1);
}
