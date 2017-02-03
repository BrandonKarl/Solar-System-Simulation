CC=g++
OFLAGS= -c -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pedantic
CFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pedantic
SOURCEMAIN=main
SOURCE2=spaceobjects
SOURCE3=universe
EXECUTABLE=NBody

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCEMAIN).o $(SOURCE2).o $(SOURCE3).o
	$(CC) $(SOURCEMAIN).o $(SOURCE2).o $(SOURCE3).o $(CFLAGS) -o $(EXECUTABLE)
	
$(SOURCEMAIN).o: $(SOURCEMAIN).cpp ./spaceobjects/$(SOURCE2).hpp ./universe/$(SOURCE3).hpp
	$(CC) $(OFLAGS) $(SOURCEMAIN).cpp

$(SOURCE2).o: ./spaceobjects/$(SOURCE2).cpp ./spaceobjects/$(SOURCE2).hpp ./universe/$(SOURCE3).hpp
	$(CC) $(OFLAGS) ./spaceobjects/$(SOURCE2).cpp
	
$(SOURCE3).o: ./universe/$(SOURCE3).cpp ./universe/$(SOURCE3).hpp ./spaceobjects/$(SOURCE2).hpp
	$(CC) $(OFLAGS) ./universe/$(SOURCE3).cpp

permissions: all
	chmod o+x $(EXECUTABLE)

clean:
	rm *.o
