/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:37:21 by jmatute-          #+#    #+#             */
/*   Updated: 2021/05/29 16:46:52 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	len;
	void	*aux;

	len = 0;
	while (lst)
	{
		aux = lst->next;
		lst = aux;
		len++;
	}
	return (len);
}
