OBJS = AddressBook2.o AddressBook2.h
CFLAGS = -Wall -g
ab: ${OBJS}
	gcc -o $@ ${OBJS}
clean:
	rm -f ab ${OBJS}











