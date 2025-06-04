/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:28:26 by user1             #+#    #+#             */
/*   Updated: 2025/03/07 11:32:02 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_ungetchar(int c, t_buf *rb)
{
	if (rb == NULL || rb->ungetc > 0)
		return (EXIT_FAILURE);
	rb->ungetc = c;
	return (EXIT_SUCCESS);
}
