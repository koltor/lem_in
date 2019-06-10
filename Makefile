# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/14 16:56:52 by matheme      #+#   ##    ##    #+#        #
#    Updated: 2019/06/10 15:04:19 by matheme     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

# nom de l'executable
NAME = lem-in

# les routes
SRC_GPATH			= src
#source
VISU_SRC_PATH		= $(SRC_GPATH)/visualisateur_src
PARSING_SRC_PATH	= $(SRC_GPATH)/parsing_src
SRC_PATH			= $(SRC_GPATH)/main_src
#object
OBJ_PATH			= obj
PARSING_OBJ_PATH	= obj
VISU_OBJ_PATH		= obj

INC_PATH			= include
LIB_PATH			= librairies

# nom des fichier code source (*.c)
NAME_SRC			=	debug.c lib_plus.c main.c option.c error.c get_nodes.c \
						recursive_bs.c assign_tubes.c recursive_bs_destroy.c \
						debug2.c stock_path.c

NAME_SRC_PARSING	=	scan_create_struct.c scan_file.c scan_get_anthill.c \
						scan_get_room.c scan_get_tube.c scan_is_order.c \
						scan_is_room.c scan_is_tube.c scan_other.c \
						scan_room.c scan_skip.c scan_tube.c

NAME_SRC_VISU		=	main_visu.c algo_bresenham.c print.c event.c ui.c \
						ui2_legendary.c fill_pixel.c

#nom des ficher objects (*.o)
NAME_OBJ			= $(NAME_SRC:.c=.o)
PARSING_NAME_OBJ 	= $(NAME_SRC_PARSING:.c=.o)
VISU_NAME_OBJ		= $(NAME_SRC_VISU:.c=.o)

#les sources
SRC		 =  $(addprefix $(SRC_PATH)/,$(NAME_SRC))
SRC		+=  $(addprefix $(PARSING_SRC_PATH)/,$(NAME_SRC_PARSING))
SRC		+=	$(addprefix $(VISU_SRC_PATH)/,$(NAME_SRC_VISU))

HEADER	=  $(INC_PATH)/lem_in.h $(INC_PATH)/visu_lem_in.h

# les objects
OBJ			= $(addprefix $(OBJ_PATH)/,$(NAME_OBJ))
PARSING_OBJ	= $(addprefix $(PARSING_OBJ_PATH)/,$(PARSING_NAME_OBJ))
VISU_OBJ	= $(addprefix $(VISU_OBJ_PATH)/,$(VISU_NAME_OBJ))

#compilateur + flags + framework
CC			= gcc #-g3 -fsanitize=address
CFLAGS		=  -Wall -Wextra -Werror
FRAMEWORKS	= -lmlx -framework OpenGL -framework AppKit

#librairies
LIBFT				= $(LIB_PATH)/libft
LIBFT_INC			= $(LIB_PATH)/libft
LIBFT.A				= $(LIBFT)/libft.a
MINILIBX			= $(LIB_PATH)/minilibx
MINILIBX_INC		= $(LIB_PATH)/minilibx
MINILIBX.A			= $(MINILIBX)/libmlx.a

all : lib minilibx $(NAME)
	@echo "\033[48;5;22m\033[38;5;15m lem-in \033[0m"

$(NAME) : $(OBJ) $(PARSING_OBJ) $(VISU_OBJ) $(LIBFT.A)
	@$(CC) -I $(LIBFT_INC) -L $(LIBFT) -I $(MINILIBX_INC) -L $(MINILIBX)  $^ -o $@ $(FRAMEWORKS)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(LIBFT) -I $(INC_PATH) -c $< -o $@
	@printf "\033[48;5;28m \033[0m"

$(PARSING_OBJ_PATH)/%.o : $(PARSING_SRC_PATH)/%.c $(HEADER)
	@mkdir $(PARSING_OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(LIBFT) -I $(INC_PATH) -c $< -o $@
	@printf "\033[48;5;28m \033[0m"

$(VISU_OBJ_PATH)/%.o : $(VISU_SRC_PATH)/%.c $(HEADER)
	@mkdir $(VISU_OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(LIBFT) -I $(INC_PATH) -I$(MINILIBX_INC) -c $< -o $@
	@printf "\033[48;5;28m \033[0m"

lib:
	@make -C $(LIBFT)

minilibx :
	@make -C $(MINILIBX)

clean:
	@rm -f $(OBJ)
	@rm -f $(PARSING_OBJ)
	@rm -f $(VISU_OBJ)
	@make -C $(LIBFT) clean
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@rmdir $(PARSING_OBJ_PATH) 2> /dev/null || true
	@rmdir $(VISU_OBJ_PATH) 2> /dev/null || true
	@echo "\033[48;5;1m\033[38;5;15m   binaire supprimer  \033[0m"

fclean: clean
	@make -C $(LIBFT) fclean
	@make -C $(MINILIBX) clean
	@rm -f $(NAME)
	@echo "\033[48;5;208m\033[38;5;15m tout a été supprimer \033[0m"

re: fclean all

nonor :
	@norminette $(SRC_PATH)/*.c $(PARSING_SRC_PATH)/*.c $(VISU_SRC_PATH) $(INC_PATH)/*.h
