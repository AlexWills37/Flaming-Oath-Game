



all: a.out

a.out: test.cpp entity.cpp dragon.cpp player.cpp dragonFire.cpp wizardspells.cpp
	g++ $^ -LSFML -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm *.o ./a.out