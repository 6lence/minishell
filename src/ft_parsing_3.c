/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:40:05 by mescobar          #+#    #+#             */
/*   Updated: 2023/10/13 15:35:00 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_data *l)
{
	l->params_split = ft_calloc(ft_words(l), sizeof(char *));
	ft_fill_split(l);
	if (l->params)
		free(l->params);
	ft_chained_args(l);
}
