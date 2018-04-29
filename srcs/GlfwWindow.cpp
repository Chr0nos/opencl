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
#include <iostream>

GlfwWindow::GlfwWindow(std::string title, unsigned int w, unsigned int h)
{
	this->_title = title;
	this->_w = w;
	this->_h = h;
	this->_window = nullptr;
	this->_flags = FLAG_NONE;
	this->_vbo = nullptr;
}

GlfwWindow::~GlfwWindow(void)
{
	if (this->_vbo)
		delete this->_vbo;
	glfwTerminate();
	std::cout << "glfw terminated" << std::endl;
}

bool GlfwWindow::Init(void)
{
	if (!glfwInit())
		return (false);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 16);
	this->_flags |= FLAG_GLFW_INIT_OK;
	std::cout << "glfw init ok" << std::endl;
	return (true);
}

bool GlfwWindow::InitGlew(void)
{
	int			err;

	if ((!(this->_flags & FLAG_GLEW_INIT_OK)) && ((err = glewInit()) != GLEW_OK))
	{
		std::cout << "error: failed to init glew: " << glewGetErrorString(err)
			<< std::endl;
		return (false);
	}
	this->_flags |= FLAG_GLEW_INIT_OK;
	return (true);
}

bool GlfwWindow::Show(void)
{
	if (!(this->_flags & FLAG_GLFW_INIT_OK))
	{
		std::cout << "error: missing glfw initialisation" << std::endl;
		return (false);
	}
	this->_window = glfwCreateWindow(this->_w, this->_h, this->_title.c_str(),
			NULL, NULL);

	if (this->_window)
	{
		glfwMakeContextCurrent(this->_window);
		glEnable(GL_DEPTH_TEST);
		std::cout << "renderer: " << glGetString(GL_RENDERER) <<
			" version: " <<	glGetString(GL_VERSION) << std::endl;
		if (!this->InitGlew())
			return (false);
	}
	return (true);
}

void GlfwWindow::RenderFrame(void)
{
}

void GlfwWindow::Render(void)
{
	if (!this->_window)
	{
		std::cout << "error: no window" << std::endl;
		return ;
	}
	std::cout << "render loop started" << std::endl;
	while (!glfwWindowShouldClose(this->_window))
	{
		if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(this->_window, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		this->RenderFrame();
		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}
	std::cout << "render loop exited" << std::endl;
}
