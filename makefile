



all: a.out

a.out: test.cpp entity.cpp dragon.cpp player.cpp dragonFire.cpp HealthBar.cpp Time.cpp InputManager.cpp Level.cpp LivingEntity.cpp Dialogue.cpp wizardspells.cpp MouseButton.cpp

	g++ $^ -LSFML -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm *.o a.out