CPP = c++
CPPFLAGS = -Wall -Wextra -Werror
NAME = RPN
SRC = $(shell find . -name "*.cpp")
OBJ = $(SRC:%.cpp=%.o)
RM = rm -f
all : $(NAME)

%.o : %.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $@

clean : 
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)
re : fclean all