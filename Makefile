OBJECTS = *.o
BINAIRE = calc
SRC = libft/*.c\
		src/main.c\
		src/calculs.c\
		src/operands.c\
		src/operators.c\
		src/addition.c\
		src/soustraction.c\
		src/multiplication.c\
		src/division.c\
		src/modulo.c\
		src/index_handler.c\
		src/helper_functions.c\
		src/helper_functions2.c\

FLAGS = -Wall -Wextra -Werror 
NAME = bistromatic.a

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SRC) -I header/bistromatic.h
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)
	gcc $(FLAGS) src/main.c -o $(BINAIRE) $(NAME)

sanitize:
	clang -fsanitize=address -fno-omit-frame-pointer -g src/main.c -o $(BINAIRE) $(NAME)

lldb:
	gcc -g $(SRC) bistromatic.a

cleanlldb:
	rm a.out
	rm -r a.out.dSYM

runlldb:
	lldb ./a.out
	b main
	r

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(BINAIRE)
	rm -f $(NAME)

re: fclean all
