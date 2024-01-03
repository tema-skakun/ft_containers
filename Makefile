# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 23:23:13 by fdarkhaw          #+#    #+#              #
#    Updated: 2022/12/25 22:38:21 by fdarkhaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_container_test

SOURCES_FOLDER	= ./tester/

SOURCES			=	main.cpp \
					tester.cpp \
					tester_map.cpp \
					tester_vector.cpp \
					tester_stack.cpp

INCLUDE 		= ./tester/tester.hpp

FLAGS 			= -Wall -Wextra -Werror -std=c++98

OBJECTS_FOLDER 	= ./tester/objects/

OBJECT			= $(SOURCES:.cpp=.o)
OBJECTS		 	= $(addprefix $(OBJECTS_FOLDER), $(OBJECT));

$(OBJECTS_FOLDER)%.o :	$(SOURCES_FOLDER)%.cpp	$(INCLUDE)
	@mkdir -p	$(OBJECTS_FOLDER)
	@echo "Compiling: $<"
	@c++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@c++ $(FLAGS) -o $(NAME) $(OBJECTS)

.PHONY: all clean fclean re run

all: $(NAME)

clean:
	@echo "Cleaning: $(OBJECTS_FOLDER)"
	@rm -rf $(OBJECTS_FOLDER)
	@echo "Cleaning: ./tester/vectors_output"
	@rm -rf ./tester/vectors_output
	@echo "Cleaning: ./tester/stacks_output"
	@rm -rf ./tester/stacks_output
	@echo "Cleaning: ./tester/maps_output"
	@rm -rf ./tester/maps_output

fclean: clean
	@echo "Cleaning: $(NAME)"
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	@./$(NAME)
