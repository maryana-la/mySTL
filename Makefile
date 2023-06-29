NAME_FT		=	ft_containers
NAME_STD	=	std_containers

COMP		=	clang++ -Wall -Wextra -Werror -std=c++98 -pedantic

SRC_FOLD	=	test/
SRC			=	main_all.cpp test_map.cpp test_stack.cpp test_vector.cpp test_set.cpp
SRC_DIR		=	$(addprefix $(SRC_FOLD), $(SRC))

HEADER		=	includes/color.hpp includes/reverse_iterator.hpp includes/tree_iterator.hpp \
				includes/vector_iterator.hpp \
				includes/iterator.hpp includes/set.hpp includes/tree_node.hpp \
				includes/map.hpp includes/stack.hpp includes/utils.hpp \
				includes/pair.hpp includes/tree.hpp includes/vector.hpp

O_FOLD		=	objs/
OBJ			=	$(addprefix $(O_FOLD), $(SRC:.cpp=.o))
DEP			=	$(addprefix $(O_FOLD), $(SRC:.cpp=.d))

$(O_FOLD)%.o: $(SRC_FOLD)%.cpp $(HEADER)
		@mkdir -p objs
		@$(COMP) -D FT=1 -MMD -c $< -o $@

all:	$(NAME_FT) $(NAME_STD)

$(NAME_FT): $(OBJ)
		@echo "Compiling ft_containers"
		@$(COMP) -D FT=1 -MMD $(OBJ) -o $(NAME_FT)

$(NAME_STD): $(OBJ)
	@echo "Compiling std_containers"
	@$(COMP) -MMD $(SRC_DIR) -o $(NAME_STD)

bonus:	all
ft:		$(NAME_FT)
std:	$(NAME_STD)

test:	all
	@./compare.sh

clean:
	@echo "Object files deleted"
	@rm -rf $(OBJ)
	@rm -rf std_containers.d
	@rm -rf $(O_FOLD)
	@rm -rf ft_test
	@rm -rf std_test
	 @echo "Test output deleted"

fclean:	clean
	@rm -rf $(NAME_FT)
	@rm -rf $(NAME_STD)
	@echo "Everything is cleaned"

re:	fclean all

.PHONY: clean fclean re all bonus ft std test
