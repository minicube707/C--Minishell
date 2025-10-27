/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/10/27 22:58:53 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_shell		t_shell;
typedef struct s_struc		t_struc;
typedef struct s_two_int	t_two_int;

char					*get_next_line(t_shell *shell, t_two_int *two_int);
char					*ft_strncpy(char *dest, const char *src,
							unsigned int n);

#endif
