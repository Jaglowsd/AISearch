#include "Algorithms.h"
#include "Route-Finding.h"
#include "MB.h"
#include "WGC.h"
#include <iostream>
#include <vector>


int main()
{
	std::cout << "Domain: " << "Traveling Salesman Route-Finding" << std::endl;
	Algorithms<routeFinding> *a_star = new Algorithms<routeFinding>("TSP");
	a_star->aStar();
	delete a_star;

	std::cout << "Domain: " << "Monkeys and Bananas" << std::endl;
	Algorithms<M_B> *a_star_beam1 = new Algorithms<M_B>();
	a_star_beam1->aStarBeam(5);
	delete a_star_beam1;
	
	std::cout << "Domain: " << "Wolf, Goat, and Cabbage" << std::endl;
	Algorithms<WGC> *a_star_beam2 = new Algorithms<WGC>();
	a_star_beam2->aStarBeam(5);
	delete a_star_beam2;
}
