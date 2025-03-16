CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
lmain: src/ladder_main.cpp src/ladder.cpp
	g++ $(CXXFLAGS) src/ladder_main.cpp src/ladder.cpp -o l_main
dmain: src/dijkstras_main.cpp src/dijkstras.cpp
	g++ $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp -o d_main
clean:
	/bin/rm l_main
	/bin/rm d_main