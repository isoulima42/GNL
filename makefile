# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/25 00:00:00 by isoulima          #+#    #+#              #
#    Updated: 2025/12/25 12:29:58 by isoulima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = get_next_line

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE = 42

# Fichiers source
SRCS = get_next_line.c \
       get_next_line_utils.c \
       main.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Header
HEADER = get_next_line.h

# Règle par défaut
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilation des fichiers objets
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS)

# Nettoyage complet
fclean: clean
	rm -f $(NAME)

# Recompilation
re: fclean all

# Déclaration des règles phony
.PHONY: all clean fclean re
