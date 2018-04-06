/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:26:30 by fbertoia          #+#    #+#             */
/*   Updated: 2018/04/06 17:16:56 by hfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh21.h"

int	exec_tree(t_ast_node *first)
{
	ft_printf("$$%s$$\n", first->content);
	return (g_exec_fn[first->type](first));
}
