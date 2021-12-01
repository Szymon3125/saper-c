all: compile link

compile:
	g++ -I src/include -c src/mapa.c -o src/mapa.o
	g++ -I src/include -c src/menu.c -o src/menu.o
	g++ -I src/include -c src/tlo.c -o src/tlo.o
	g++ -I src/include -c main.c
link:
	g++ src/mapa.o src/menu.o src/tlo.o main.o -o saper -L src/lib/gcc -l csfml-graphics -l csfml-window -l csfml-system -l csfml-audio -l csfml-network