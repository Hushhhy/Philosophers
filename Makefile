# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 20:27:40 by acarpent          #+#    #+#              #
#    Updated: 2024/11/08 16:31:23 by acarpent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#$(shell find $(SRCS_DIR) -name '*.c')

#### COLORS ####

GREEN = \033[0;92m
NC = \033[0m

##### FOLDERS PATH ####

SRCS_DIR = ./Srcs/
OBJS_DIR = ./Objs/
HEADER_DIR = ./Includes/

###### ARGUMENTS ######

NAME = philosophers
CFLAGS = -Wall -Werror -Wextra -g -pthread
COMP = cc
RM = rm -rf
MKDIR = mkdir -p

######  SOURCES  ######

SRCS_FILES = philosophers.c\
				parsing.c\

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))			

######  OBJECTS  ######

OBJS_FILES = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

######   RULES   ######

all: $(NAME)
	
$(NAME) : $(OBJS_DIR) $(OBJS_FILES)
	@echo "$(GREEN)Compilation in progress...$(NC)"
	@$(COMP) $(CFLAGS) $(OBJS_FILES) -o $(NAME)
	@echo "$(GREEN)Compilation completed!$(NC)"
	
#Creer le repertoire 'Objs' et compiles C source files into object files

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(MKDIR) $(dir $@)
	@$(COMP) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

#Clean objects files and dependencies

clean:
	@echo "$(GREEN)Cleaning in progress...$(NC)"
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)Cleaning completed!$(NC)"

#Cleans everything generated by the Makefile

fclean: clean
	@$(RM) $(NAME) $(BIN_DIR) $(OBJS_DIR)

#Remake

re: fclean all

.PHONY: all clean fclean re 