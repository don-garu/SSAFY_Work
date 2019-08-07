OBJECTS = client.o
SRCS = client.c

TARGET = client

$(TARGET): $(OBJECTS)
	gcc -o $(TARGET) $(OBJECTS)
	mv $(TARGET) ../output/

clean:
	rm $(OBJECTS) ../output/$(TARGET)

$(OBJECTS): $(SRCS)
	gcc -c $(SRCS)
