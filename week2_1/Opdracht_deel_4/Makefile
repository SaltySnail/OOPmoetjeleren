CFLAGS = -std=c++11 `sdl2-config --cflags --libs` -lSDL2_image -lm -I include/
OBJ = $(wildcard obj/*.o)


make: main.o
	echo $(OBJ)
	g++ -o Stoplichten $(CFLAGS) $(OBJ)

main.o: init.o 
	g++ -c src/main.cpp -o obj/main.o $(CFLAGS)

init.o: blit.o car.o stoplicht.o
	g++ -c src/init.cpp -o obj/init.o $(CFLAGS)

stoplicht.o: lamp.o
	g++ -c src/stoplicht.cpp -o obj/stoplicht.o $(CFLAGS)

lamp.o:
	g++ -c src/lamp.cpp -o obj/lamp.o $(CFLAGS)

blit.o:
	g++ -c src/blit.cpp -o obj/blit.o $(CFLAGS)

car.o:
	g++ -c src/car.cpp -o obj/car.o $(CFLAGS)

clean:
	rm -f $(OBJ)
