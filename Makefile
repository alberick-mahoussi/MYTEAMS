##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## nherbal
##

all:
	${MAKE} -C src/server/
	${MAKE} -C src/client/

fclean:
	${MAKE} fclean -C src/server/
	${MAKE} fclean -C src/client/

clean:
	${MAKE} clean -C src/server/
	${MAKE} clean -C src/client/

re: fclean
	${MAKE} -C src/server/
	${MAKE} -C src/client/

.phony: all clean fclean re
