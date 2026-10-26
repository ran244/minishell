NAME = minishell

SRCS =  src/mini.c\
	src/parcing/node.c\
	src/parcing/tokenizer1.c\
	src/parcing/tokenizer2.c\
	src/utils/utils1.c\
	src/utils/utils2.c\
	src/utils/utils3.c\
	src/parcing/parsing1.c\
	src/parcing/parsing2.c\
	src/parcing/parsing3.c\
	src/execute/execute_child.c\
	src/execute/execute.c\
	src/execute/hd_expand.c\
	src/execute/hd.c\
	src/execute/hd2.c\
	src/execute/init_exec.c\
	src/execute/parent.c\
	src/execute/path.c\
	src/execute/prepforexecute.c\
	src/execute/redir.c\
	src/execute/redir2.c\
	src/built_in/built_in.c\
	src/built_in/cd.c\
	src/built_in/echo.c\
	src/built_in/env.c\
	src/built_in/exit.c\
	src/built_in/export_utils.c\
	src/built_in/export1.c\
	src/built_in/export2.c\
	src/built_in/export3.c\
	src/signals.c

OFILES = $(SRCS:src/%.c=obj/%.o)

LIB = libft/libft.a
LIB_PATH = ./libft

CFLAGS = -Wall -Wextra -Werror -I$(LIB_PATH)
LDFLAGS = -L$(LIB_PATH) -lft -L/usr/local/lib -lreadline

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C $(LIB_PATH)

$(NAME): $(OFILES)
	cc $(OFILES) $(LDFLAGS) -o $(NAME)

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	cc $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_PATH) clean
	rm -f $(OFILES)
	rm -rf obj

fclean: clean
	$(MAKE) -C $(LIB_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
