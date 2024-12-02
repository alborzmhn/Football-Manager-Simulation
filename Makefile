futballFantasy.out: main.o Futball.o Week.o Real_Team.o User_Team.o Player.o game.o Admin.o
	g++ main.o Futball.o Week.o Real_Team.o User_Team.o Player.o game.o Admin.o -o futballFantasy.out

main.o: main.cpp header.hpp
	g++ -c -std=c++11 main.cpp

Futball.o: Futball.cpp header.hpp
	g++ -c -std=c++11 Futball.cpp

Week.o: Week.cpp header.hpp
	g++ -c -std=c++11 Week.cpp

Real_Team.o: Real_Team.cpp header.hpp
	g++ -c -std=c++11 Real_Team.cpp

User_Team.o: User_Team.cpp header.hpp
	g++ -c -std=c++11 User_Team.cpp

Player.o: Player.cpp header.hpp
	g++ -c -std=c++11 Player.cpp	

game.o: game.cpp header.hpp
	g++ -c -std=c++11 game.cpp

Admin.o: Admin.cpp header.hpp
	g++ -c -std=c++11 Admin.cpp

clean: 
	rm *.o futballFantasy.out