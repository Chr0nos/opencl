/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:47:03 by snicolet          #+#    #+#             */
/*   Updated: 2018/04/26 00:50:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mopencl.hpp"
#define EXIT_SUCCESS 0

int		main(void)
{
	Mopencl		cl;

	cl.ListPlatforms();
	cl.SelectPlatform(1);
	cl.ListDevices();
	cl.CreateContext();
	return (EXIT_SUCCESS);
}
