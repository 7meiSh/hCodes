CC = gcc
CFLAGS = -Wall
LDFLAGS =

SRCS = main.c freqTable.c buildTree.c generateCodes.c
OBJS = $(SRCS:.c=.o)
TARGET = Hcodes

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
