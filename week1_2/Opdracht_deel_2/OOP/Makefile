CFLAGS = -std=c++11 -I include/
OBJ = $(wildcard obj/*.o)


make: main.o
	echo $(OBJ)
	g++ -o Country $(CFLAGS) $(OBJ)

main.o: Country.o
	g++ -c src/main.cpp -o obj/main.o $(CFLAGS)

Country.o:
	g++ -c src/Country.cpp -o obj/Country.o $(CFLAGS)

clean:
	rm -f $(OBJ)