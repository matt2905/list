CC			?= gcc
CFLAGS		+= -Wall -Wextra --pedantic -Werror

SRC			=   list_func.c \
				list_utils.c
MSRCS		=	main.c
TESTSRCS	=	test/main_test.c

DOBJ		= obj/
NAME		= list
INC			= -I includes
OBJ			= $(patsubst %.c, $(DOBJ)%.o, $(SRC))
MOBJ		=	$(patsubst %.c, $(DOBJ)%.o, $(MSRCS))
TESTOBJ		=	$(patsubst %.c, $(DOBJ)%.o, $(TESTSRCS))
DEPENDS		= -MT $@ -MD -MP -MF $(subst .o,.d,$@)

all: $(NAME)

$(NAME):		$(OBJ) $(MOBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MOBJ)
	@echo "\033[33m"Compilation of $(NAME) : "\033[32m"Success"\033[0m"

-include		$(OBJ:.o=.d)

$(DOBJ)%.o:		%.c
	@mkdir -p $(DOBJ)
	@mkdir -p $(DOBJ)test
	@$(CC) $(CFLAGS) $(DEPENDS) -c $< -o $@ $(INC)
	@echo "\033[32m$(CC) \033[33m$(CFLAGS) \033[35m$(DEPENDS) \033[36m-c $< -o $@ $(INC)\033[0m"

test: $(OBJ) $(TESTOBJ)
	@$(CC) $(CFLAGS) -o test_func $(OBJ) $(TESTOBJ) -lcunit
	@echo "\033[33m"Compilation of test_func : "\033[32m"Success"\033[0m"
	./test_func

clean:
	@/bin/rm -rf $(DOBJ)
	@echo "\033[31m"Objects of $(NAME) : deleted"\033[0m"

fclean:			clean
	@/bin/rm -f $(NAME) test_func
	@/bin/rm -rf $(NAME).dSYM
	@echo "\033[31m"$(NAME) : deleted"\033[0m"

re:				fclean all

.PHONY:			all clean re
