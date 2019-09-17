/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:06:50 by cauranus          #+#    #+#             */
/*   Updated: 2019/09/17 20:05:51 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_file(t_list **start, int fd)
{
	t_list *tmp;

	tmp = *start;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(start, tmp);
	return (tmp);
}

static int		end(const char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*file_buf;
	int				ret;
	t_list			*tmp;
	char			buf[BUFF_SIZE + 1];

	CHECK_RETURN((fd < 0 || line == NULL || read(fd, buf, 0) < 0), -1);
	tmp = get_file(&file_buf, fd);
	if (!tmp->content)
		tmp->content = ft_strnew(1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		ft_swapnfree(&tmp->content, ft_strjoin(tmp->content, buf));
		CHECK_RETURN(!tmp->content, -1);
		if (ft_strchr(tmp->content, '\n'))
			break ;
	}
	CHECK_RETURN(ret < BUFF_SIZE && !*(char *)(tmp->content), 0);
	*line = ft_strndup(tmp->content, end(tmp->content));
	if (ft_strlen(*line) < ft_strlen(tmp->content))
		ft_swapnfree(&tmp->content,
			ft_strdup(tmp->content + ft_strlen(*line) + 1));
	else
		ft_memdel(&tmp->content);
	return (1);
}
