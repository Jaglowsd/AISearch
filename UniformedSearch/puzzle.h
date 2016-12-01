#include <vector>
#include <list>
#include <string>

struct puzzleState
{
	std::string config;
};

class puzzle {

public:

	puzzleState state;
	std::vector<std::string> actions;
	puzzle *parent;
	std::string actionTaken;
	int path_Cost;

	puzzle::puzzle(); // Intial state constrcutor 
	puzzle::puzzle(std::string state, puzzle* parent, std::string action); // Every other node constructor
	
	void Actions(); // Return set of available actions
	std::string Result(std::string action); // Return the result of an action performed on a state
	bool isGoal(); // Checks if current state is a goal state

	void g(int cost);
	std::string getState();
};

puzzle::puzzle() {
	state.config = "806547231";
	path_Cost = 0;
}
// Initial Constructor
puzzle::puzzle(std::string st, puzzle* parent, std::string action) {
	state.config = st;
	this->parent = parent;
	actionTaken = action;
	g(parent->path_Cost);
}
// Every node after intial constructor

void puzzle::Actions() {
	size_t pos = this->state.config.find_first_of("0");

	if (pos <= 2)
	{
		if (pos == 0)
		{
			actions = { "d", "r" };
		}
		else if (pos == 2)
		{
			actions = { "l", "d" };
		}
		else
		{
			actions = { "r", "l", "d" };
		}
	}
	else if (pos > 2 && pos <= 5)
	{
		if (pos == 3)
		{
			actions = { "u", "d", "r" };
		}
		else if (pos == 5)
		{
			actions = { "l", "d", "u" };
		}
		else
		{
			actions = { "r", "d", "l", "u" };
		}
	}
	else
	{
		if (pos == 6) 
		{
			actions = { "r", "u" };
		}
		else if (pos == 8)
		{
			actions = { "l", "u" };
		}
		else
		{
			actions = { "r", "l", "u" };
		}
	}

} 
// Return set of available actions

std::string puzzle::Result(std::string action) {
	std::string current = this->state.config;
	std::string new_state = current;
	size_t pos = current.find_first_of("0");

	if (action == "u")
	{
		char swap = current.at(pos - 3);
		std::string str = new_state.substr(0, pos) + swap + new_state.substr(pos + 1);
		new_state = str.substr(0, (pos - 3)) + "0" + str.substr(pos - 2);
	}
	else if (action == "l")
	{
		char swap = current.at(pos - 1);
		std::string str = new_state.substr(0, pos) + swap + new_state.substr(pos + 1);
		new_state = str.substr(0, (pos - 1)) + "0" + str.substr(pos);
	}
	else if (action == "r")
	{
		char swap = current.at(pos + 1);
		std::string str = new_state.substr(0, pos) + swap + new_state.substr(pos + 1);
		new_state = str.substr(0, (pos + 1)) + "0" + str.substr(pos + 2);
	}
	else 
	{
		char swap = current.at(pos + 3);
		std::string str = new_state.substr(0, pos) + swap + new_state.substr(pos + 1);
		new_state = str.substr(0, (pos + 3)) + "0" + str.substr(pos + 4);
	}
	return new_state;

} 
// Return the result of an action performed on a state

bool puzzle::isGoal() {
		if (this->state.config == "012345678")
			return true;
		return false;
} 
// Checks if current state is a goal state

//////////////////////////////////////////////////////
////                Auxiliary				      ////
//////////////////////////////////////////////////////
std::string puzzle::getState() { return state.config; }
void puzzle::g(int cost) { path_Cost = cost + 1; }

