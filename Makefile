CC = gcc
NAME=doom3d
DIR_SRC = ./src
DIR_OBJ = temp
LIBSDL2 = ./lib/SDL2
LIBFT = ./lib/libft
LIB3D = ./lib/lib3d
LIBGMATRIX = ./lib/libgmatrix
LIBFTFLAGS = -L$(LIBFT) -lft
LIB3DFLAGS = -L$(LIB3D) -l3d
LIBGMATRIXFLAGS = -L$(LIBGMATRIX) -lgmatrix
# Linux and MacOS specific includes & libs
# Linux requires sdl2 installed
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf
	LIB_MATH = -lm
	LIB_PTHRTEAD = -lpthread
else
	SDL_FLAGS = -rpath $(LIBSDL2) \
					-framework SDL2 -F$(LIBSDL2)/ \
					-framework SDL2_image -F$(LIBSDL2)/ \
					-framework SDL2_ttf -F$(LIBSDL2)/
	SDL_INCLUDES = -I$(LIBSDL2)/SDL2.framework/Headers \
			-I$(LIBSDL2)/SDL2_image.framework/Headers \
			-I$(LIBSDL2)/SDL2_ttf.framework/Headers
endif
LIBS = $(LIB3DFLAGS) $(LIBGMATRIXFLAGS) $(LIBFTFLAGS) $(SDL_FLAGS) $(LIB_MATH) $(LIB_PTHRTEAD)

INCLUDES = -I ./include \
		-I$(LIBFT)/include \
		-I$(LIB3D)/include \
		-I$(LIBGMATRIX)/include \
		$(SDL_INCLUDES)

CFLAGS =-Wall -Wextra -Werror -O3 -flto
SOURCES = main.c \
			doom3d.c \
			player/player.c \
			player/collision.c \
			player/movement.c \
			camera.c \
			debug.c \
			scene/scene.c \
			scene/cleanup.c \
			scene/assets.c \
			scene/scene_asset_files.c \
			scene/scene_data.c \
			render/render.c \
			render/prepare.c \
			render/prepare_utils1.c \
			render/prepare_utils2.c \
			render/prepare_utils3.c \
			render/rasterize.c \
			render/prepare_clip.c \
			render/ui.c \
			render/ui_main_game.c \
			window/text.c \
			window/window.c \
			window/frame.c \
			window/utils.c \
			window/buttons/button_events.c \
			window/buttons/button_group_events.c \
			window/buttons/button_group_utils.c \
			window/buttons/button_group.c \
			window/buttons/button_utils.c \
			window/buttons/button.c \
			events/mouse_state.c \
			events/menu_events.c \
			events/events.c \
			events/keyboard_state.c \
			events/general_input_events.c

OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEV_OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=_dev.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make libs
	@printf "\033[32;1mCompiling app...\n\033[0m"
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)
	@printf "\033[32;1mDone. Run: ./$(NAME)\n\033[0m"

libs:
	@printf "\033[32;1mCompiling libs...\n\033[0m"
	make -C $(LIBFT)
	make -C $(LIB3D)
	make -C $(LIBGMATRIX)

$(DIR_OBJ):
	@mkdir -p temp
	@mkdir -p temp/map
	@mkdir -p temp/scene
	@mkdir -p temp/window
	@mkdir -p temp/window/buttons
	@mkdir -p temp/render
	@mkdir -p temp/events
	@mkdir -p temp/player

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

clean:
	@make -C $(LIBFT) clean
	@make -C $(LIB3D) clean
	@make -C $(LIBGMATRIX) clean
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@make -C $(LIB3D) fclean
	@make -C $(LIBGMATRIX) fclean
	@/bin/rm -f $(NAME)

re: fclean all

norm: norminette $(DIR_SRC) $(LIBFT) $(LIB3D) $(LIBGMATRIX) ./include

.PHONY: all, $(DIR_OBJ), clean, fclean
