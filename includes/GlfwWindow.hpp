/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:57:54 by snicolet          #+#    #+#             */
/*   Updated: 2018/04/28 18:14:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFW_WINDOW_HPP
# define GLFW_WINDOW_HPP
# include <GLFW/glfw3.h>
# include <string>

class GlfwWindow
{
	public:
				GlfwWindow(std::string title, unsigned int w, unsigned int h);
				~GlfwWindow(void);
		bool	Init(void);
		void	Show(void);
		void	Render(void);

	private:
		unsigned int		_w;
		unsigned int		_h;
		std::string			_title;
		GLFWwindow			*_window;
};

#endif
