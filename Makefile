# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rludosan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 10:26:56 by rludosan          #+#    #+#              #
#    Updated: 2017/09/29 14:58:40 by rludosan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER			=	Durex
SERVER_DUP		=	/usr/sbin/Durex
LOCK_FILE		=	/var/lock/durex.lock
CLIENT			=	Manix
INC				=	-Iincludes
DIR				=	./sources/
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
SRC_SERVER		=	durex \
					signal \
					path \
					daemon \
					replicate \
					lock \
					report \
					server \
					client \
					shell \
					key_serv \
					key_utils_serv
SRC_CLIENT		=	manix key_utils_cli key_cli
OBJ_SERVER		=	$(addsuffix .o, $(SRC_SERVER))
OBJ_CLIENT		=	$(addsuffix .o, $(SRC_CLIENT))
TGT_SERVER		=	$(addprefix $(DIR), $(OBJ_SERVER))
TGT_CLIENT		=	$(addprefix $(DIR), $(OBJ_CLIENT))

all: $(SERVER) $(CLIENT)

$(SERVER): $(TGT_SERVER)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

$(CLIENT): $(TGT_CLIENT)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -f $(TGT_SERVER) $(TGT_CLIENT)

fclean: clean
	rm -rf $(SERVER) $(CLIENT) $(SERVER_DUP) $(LOCK_FILE)

re: fclean all

.PHONY: all clean fclean re
