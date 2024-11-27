CC = gcc
CFLAGS = -Wall -pthread
EXEC1 = gamestarter
EXEC2 = player1
EXEC3 = player2

# Default target
all: $(EXEC1) $(EXEC2) $(EXEC3)

# Compile gamestarter.c
$(EXEC1): gamestarter.c
	$(CC) $(CFLAGS) -o $(EXEC1) gamestarter.c

# Compile player1.c
$(EXEC2): player1.c
	$(CC) $(CFLAGS) -o $(EXEC2) player1.c

# Compile player2.c
$(EXEC3): player2.c
	$(CC) $(CFLAGS) -o $(EXEC3) player2.c

# Clean up compiled files
clean:
	rm -f $(EXEC1) $(EXEC2) $(EXEC3)
