



all: a.out

a.out: test.cpp
	g++ $< -LSFML -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
