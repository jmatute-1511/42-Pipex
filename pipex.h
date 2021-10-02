/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:20:35 by jmatute-          #+#    #+#             */
/*   Updated: 2021/10/02 21:41:21 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#	define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pipex
{
	char	*path;
	char	**m_route;
}			t_pipex;
char 	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
#endif