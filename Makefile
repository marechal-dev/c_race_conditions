CC = gcc
CFLAGS = -g
LDFLAGS = -pthread

RACE = race_condition.c
PET = peterson.c
SEM = semaphores.c
ALL_TARGETS = ${RACE} ${PET} ${SEM}

.DEFAULT_GOAL := all

all: race_condition peterson semaphores

race_condition: ${RACE}
	@echo "Compilling race_condition.c..."
	@${CC} ${CFLAGS} ${LDFLAGS} ${RACE} -o race_condition.out

peterson: ${PET}
	@echo "Compilling peterson.c..."
	@${CC} ${CFLAGS} ${LDFLAGS} ${PET} -o peterson.out

semaphores: ${SEM}
	@echo "Compilling semaphores.c..."
	@${CC} ${CFLAGS} ${LDFLAGS} ${SEM} -o semaphores.out

clean: $(*.out)
	@echo "Removing '.out' files..."
	@rm -f *.out