#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2018/04/25 20:11:05 by snicolet          #+#    #+#             *#
#*   Updated: 2018/05/18 22:19:32 by snicolet         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME=test
CC=clang++
CXXFLAGS=-Wall -Werror -Wextra -std=c++11 -Wvla
CFLAGS=-Wall -Werror -Wextra -Wvla -Weverything
INC=-I include
LINKER=
BUILDDIR=./build
SRCDIR=./srcs

SRCS=main.cpp Mopencl.cpp GlfwWindow.cpp GLBuffer.cpp Vbo.cpp Shader.cpp kernel.cpp

OBJS=$(SRCS:%.cpp=$(BUILDDIR)/%.o)

ifeq ($(shell uname -s),Darwin)
	INC += -I$(HOME)/.brew/include
	LINKER += -framework OpenCL -framework OpenGL -L$(HOME)/.brew/lib/ -lglfw -lglew
	CFLAGS += -Wno-unused-macros
else
	LINKER += -lOpenCL -lglfw -lGLEW -lGL
endif

all: $(NAME)

lstobj:
	@echo $(OBJS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(INC) $(CXXFLAGS) -c $< -o $@

$(NAME): $(BUILDDIR) $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LINKER)

clean:
	$(RM) -r $(BUILDDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

poc-clean:
	$(RM) poc

poc: poc-clean
	clang $(CFLAGS) srcs/poc.c -I../libft/include -L../libft -lft $(LINKER) -o poc
