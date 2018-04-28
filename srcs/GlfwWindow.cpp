/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:57:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/04/28 18:09:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlfwWindow.hpp"

GlfwWindow::GlfwWindow(std::string title, unsigned int w, unsigned int h)
{
	this->_title = title;
	this->_w = w;
	this->_h = h;
	this->_window = nullptr;
	this->Init();
}

GlfwWindow::~GlfwWindow(void)
{
	glfwTerminate();
}

bool GlfwWindow::Init(void)
{
	if (!glfwInit())
		return (false);
	return (true);
}

void GlfwWindow::Show(void)
{
	this->_window = glfwCreateWindow(this->_w, this->_h, this->_title.c_str(),
			NULL, NULL);
	if (this->_window)
	{
		glfwMakeContextCurrent(this->_window);
	}
}

void GlfwWindow::Render(void)
{
	while (!glfwWindowShouldClose(this->_window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}
}
