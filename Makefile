#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2018/04/25 20:11:05 by snicolet          #+#    #+#             *#
#*   Updated: 2018/04/26 00:56:55 by snicolet         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME=test
CC=clang++
CXXFLAGS=-Wall -Werror -Wextra -std=c++11 -Wvla
INC=-I./includes
LINKER=-lOpenCL
BUILDDIR=./build
SRCDIR=./srcs


SRCS=main.cpp Mopencl.cpp

OBJS=$(SRCS:%.cpp=$(BUILDDIR)/%.o)

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

