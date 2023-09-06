NAME = main
.DEFAULT_GOAL = all

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -MMD -MP
SRC = \
	parser/Consumer.cpp \
	parser/Parser.cpp \
	parser/ParseResult.cpp \
	main.cpp
.PHONY: all clean fclean re test

all: $(NAME)

DEP = $(SRC:.cpp=.d)
-include $(DEP)

$(NAME): $(SRC:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(OUTPUT_OPTION) $(SRC:.cpp=.o)

$(CLASS:.cpp=.o): %.o: %.cpp %.hpp

clean:
	rm -rf *.o **/*.o
	rm -rf *.d **/*.d

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

test: all
	./$(NAME) test.txt
