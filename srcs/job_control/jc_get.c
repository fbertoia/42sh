/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:31:30 by fle-roy           #+#    #+#             */
/*   Updated: 2018/04/20 15:58:58 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_jc		*jc_get(void)
{
	static t_jc jc;

	return (&jc);
}
