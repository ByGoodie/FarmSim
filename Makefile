compile:
	g++ -c main.cpp Geometry.cpp State.cpp StateStack.cpp SceneNode.cpp Entity.cpp Human.cpp Game.cpp App.cpp InputManager.cpp Animation.cpp -I"ThirdParty/SFML-2.4.2/include" -I"D:/GAMES/FarmSim"
compileGeo:
	g++ -c GeoTest.cpp Geometry.cpp -I"E:/GAMES/SFML-2.4.2/include" -I"D:/GAMES/FarmSim"
link:
	g++ main.o Geometry.o State.o StateStack.o SceneNode.o Entity.o Human.o Game.o App.o InputManager.o Animation.o -o FarmSim -L"ThirdParty/SFML-2.4.2/lib" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lopengl32 -lwinmm -lgdi32
linkGeo:
	g++ GeoTest.o Geometry.o -L"E:/GAMES/SFML-2.4.2/lib" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lopengl32 -lwinmm -lgdi32