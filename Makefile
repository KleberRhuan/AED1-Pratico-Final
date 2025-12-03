CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -I.

SRC := \
	src/main.c \
	data/datastore.c \
	services/client_service.c \
	services/employee_service.c \
	services/room_service.c \
	services/stay_service.c \
	utils/utils_io.c \
	utils/utils_date.c \
	persistence/persistence.c

OBJ := $(SRC:.c=.o)

.PHONY: all clean

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -f $(OBJ) main
