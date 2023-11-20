/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:04:08 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/20 11:31:22 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wild_2(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (!s2[j] && i && j && s1[i - 1] != s2[j - 1])
			return (0);
		while (s1[i] == '*')
			i++;
		if (!s1[i])
			return (1);
		while (s2[j] && s2[j] != s1[i])
			j++;
		if (s2[j])
			j++;
		i++;
	}
	if (s2[j])
		return (0);
	return (1);
}

t_var	*ft_wild(char *str, t_var *lst)
{
	t_var	*res;
	t_var	*res2;

	res = NULL;
	while (lst)
	{
		if (ft_wild_2(str, lst->var))
		{
			if (!res)
			{
				res = malloc(sizeof(t_var));
				res->var = lst->var;
				res->next = NULL;
				res2 = res;
			}
			else
			{
				res2->next = malloc(sizeof(t_var));
				res2->next->var = lst->var;
				res2->next->next = NULL;
				res2 = res2->next;
			}
		}
		lst = lst->next;
	}
	return (res);
}

// t_var *init(int argc, char **argv)
// {
// 	t_var *lst = NULL;
// 	t_var *lst2 = NULL;

// 	if (argc > 2)
// 	{
// 		lst = malloc(sizeof(t_var));
// 		lst->var = argv[2];
// 		lst->next = NULL;
// 		lst2 = lst;
// 		for (int i = 3; i < argc; i++)
// 		{
// 			lst2->next = malloc(sizeof(t_var));
// 			lst2->next->var = argv[i];
// 			lst2->next->next = NULL;
// 			lst2 = lst2->next;
// 		}
// 	}
// 	return (lst);
// }

// int main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (printf("eh oh les args\n"), 0);
// 	t_var	*lst = init(argc, argv);
// 	t_var	*lst2 = ft_wild(argv[1], lst);

// 	while (lst2)
// 	{
// 		printf("%s\n", lst2->var);
// 		lst2 = lst2->next;
// 	}

// 	return (0);
// }
