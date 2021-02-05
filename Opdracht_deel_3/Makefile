CFLAGS = -std=c++11 -I include/
OBJ = $(wildcard obj/*.o)


make: hello.o
	echo $(OBJ)
	g++ -o country $(CFLAGS) $(OBJ)

hello.o: country.o
	g++ -c src/hello.cpp -o obj/hello.o $(CFLAGS)

country.o:
	g++ -c src/country.cpp -o obj/country.o $(CFLAGS)

clean:
	rm -f $(OBJ)
