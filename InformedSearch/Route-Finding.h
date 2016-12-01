#include <vector>
#include <string>
#include <map>

class routeFinding {

public:

	int g;
	int f;
	int h;
	char vertex;
	char goal;
	std::string act;
	routeFinding *parent;
	std::map<char, int> edges;

	routeFinding::routeFinding(char key, char goal_node, std::map<char, int> graph); // Intial state constrcutor 
	routeFinding::routeFinding(std::map<char, int> graph ,char key, char goal_node, routeFinding* parent); // Every other node constructor

	bool isGoal(); // Checks if current state is a goal state

	void G(int g, char key); // Set path cost to current node
	void H1(); // Straight Line Distance

	std::string renderState(); // Render string to display current state
};

routeFinding::routeFinding(char key, char goal_node, std::map<char, int> graph) {
	f = 0;
	g = 0;
	this->parent = this;
	vertex = key;
	goal = goal_node;
	edges.swap(graph);
}
// Initial Constructor

routeFinding::routeFinding(std::map<char, int> graph, char key, char goal_node, routeFinding* parent) 
{
	vertex = key;
	edges.swap(graph);
	this->parent = parent;
	goal = goal_node;
	G(parent->g, parent->vertex);
	if (vertex != goal)
		H1(); // Straight Line Distance
		// H2();
	else
		h = 0;
	f = g + h;
}
// Every node after intial constructor

bool routeFinding::isGoal() {
	if (this->vertex == 'B')
		return true;
	return false;
}
// Checks if current state is a goal state

void routeFinding::G(int cost, char key) { g = cost + edges[key]; }
// Path Cost

void routeFinding::H1() 
{
	if (vertex == 'A')
		h = 366;
	else if (vertex == 'B')
		h = 0;
	else if (vertex == 'C')
		h = 160;
	else if (vertex == 'D')
		h = 242;
	else if (vertex == 'E')
		h = 161;
	else if (vertex == 'F')
		h = 176;
	else if (vertex == 'G')
		h = 77;
	else if (vertex == 'H')
		h = 151;
	else if (vertex == 'I')
		h = 226;
	else if (vertex == 'L')
		h = 244;
	else if (vertex == 'M')
		h = 241;
	else if (vertex == 'N')
		h = 234;
	else if (vertex == 'O')
		h = 380;
	else if (vertex == 'P')
		h = 100;
	else if (vertex == 'R')
		h = 193;
	else if (vertex == 'S')
		h = 253;
	else if (vertex == 'T')
		h = 329;
	else if (vertex == 'U')
		h = 80;
	else if (vertex == 'V')
		h = 199;
	else 
		h = 374;

} 
// Straight Line Distance

std::string routeFinding::renderState() {
	std::string str;

	if (vertex == 'A')
		str = "In Arad";
	else if (vertex == 'B')
		str = "In Bucharest";
	else if (vertex == 'C')
		str = "In Craiova";
	else if (vertex == 'D')
		str = "In Drobeta";
	else if (vertex == 'E')
		str = "In Eforie";
	else if (vertex == 'F')
		str = "In Fagaras";
	else if (vertex == 'G')
		str = "In Giurgiu";
	else if (vertex == 'H')
		str = "In Hirsova";
	else if (vertex == 'I')
		str = "In Iasi";
	else if (vertex == 'L')
		str = "In Lugoj";
	else if (vertex == 'M')
		str = "In Mehadia";
	else if (vertex == 'N')
		str = "In Neamt";
	else if (vertex == 'O')
		str = "In Oradea";
	else if (vertex == 'P')
		str = "In Pitesti";
	else if (vertex == 'R')
		str = "In Rimnicu Vilcea";
	else if (vertex == 'S')
		str = "In Sibiu";
	else if (vertex == 'T')
		str = "In Timisoara";
	else if (vertex == 'U')
		str = "In Urziceni";
	else if (vertex == 'V')
		str = "In Vaslui";
	else
		str = "In Zerind";
	return str;
}
// Render string to display current state