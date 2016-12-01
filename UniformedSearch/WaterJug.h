#include <vector>
#include <list>
#include <string>
#include <math.h>

struct waterJugState
{
	std::string twelve;
	std::string eight;
	std::string three;
};

class WaterJug {

public:

	waterJugState state;
	std::vector<std::string> actions;
	WaterJug *parent;
	std::string actionTaken;
	int path_Cost;

	WaterJug::WaterJug(); // Intial state constrcutor 
	WaterJug::WaterJug(std::string state, WaterJug *parent, std::string action); // Every other node constructor

	void Actions(); // Return set of available actions
	std::string Result(std::string action); // Return the result of an action performed on a state
	bool isGoal(); // Checks if current state is a goal state

	std::string getState();
	void g(int cost);
	int toInt(std::string);
};

WaterJug::WaterJug() {
	state.twelve = "0";
	state.eight = "0";
	state.three = "0";
	path_Cost = 0;
}
// Initial Constructor
WaterJug::WaterJug(std::string states, WaterJug *parent, std::string action) {
	if (states.length() == 4)
	{
		state.twelve = states.substr(0, 2);
		state.eight = states.substr(2, 1);
		state.three = states.substr(3, 1);
	}
	else
	{
		state.twelve = states.substr(0, 1);
		state.eight = states.substr(1, 1);
		state.three = states.substr(2, 1);
	}
	this->parent = parent;
	actionTaken = action;
	g(parent->path_Cost);
}
// Every node after intial constructor

void WaterJug::Actions() {
	if (state.twelve != "12")
		actions.push_back("f 12");
	if (state.eight != "8")
		actions.push_back("f 8");
	if (state.three != "3")
		actions.push_back("f 3");
	if (state.twelve != "0")
		actions.push_back("e 12");
	if (state.eight != "0")
		actions.push_back("e 8");
	if (state.three != "3")
		actions.push_back("e 3");
	actions.push_back("12 3");
	actions.push_back("12 8");
	actions.push_back("3 12");
	actions.push_back("3 8");
	actions.push_back("8 12");
	actions.push_back("8 3");
} // Return set of available actions
// Return set of available actions

std::string WaterJug::Result(std::string action) {
	std::string current = this->getState();
	std::string temp;

	if (action == ("f 12"))
	{
		temp = "12" + state.eight + state.three;
		return temp;
	}
	else if (action == ("f 8"))
	{
		temp = state.twelve + "8" + state.three;
		return temp;
	}
	else if (action == ("f 3"))
	{
		temp = state.twelve + state.eight + "3";
		return temp;
	}
	else if (action == ("e 12"))
	{
		temp = "0" + state.eight + state.three;
		return temp;
	}
	else if (action == ("e 8"))
	{
		temp = state.twelve + "0" + state.three;
		return temp;
	}
	else if (action == ("e 3"))
	{
		temp = state.twelve + state.eight + "0";
		return temp;
	}
	else if (action == ("12 3"))
	{
		if (state.twelve == ("0"))
			return current;
		else if (state.three == ("3"))
			return current;

		int twelve = toInt(state.twelve);
		int three = toInt(state.eight);

		if (twelve + three >= 3)
		{
			twelve = twelve - (3 - three);
			three = 3;
			temp = std::to_string(twelve) + state.eight + std::to_string(three);
			return temp;
		}
		else
		{
			three = twelve + three;
			temp = "0" + state.eight + std::to_string(three);
			return temp;
		}
	}
	else if (action == ("12 8"))
	{
		if (state.twelve == ("0"))
			return current;
		else if (state.eight == ("8"))
			return current;

		int twelve = toInt(state.twelve);
		int eight = toInt(state.eight);

		if (twelve + eight >= 8)
		{
			twelve = twelve - (8 - eight);
			eight = 8;
			temp = std::to_string(twelve) + std::to_string(eight) + state.three;
			return temp;
		}
		else
		{
			eight = twelve + eight;
			temp = "0" + std::to_string(eight) + state.three;
			return temp;
		}
	}
	else if (action == ("8 3"))
	{
		if (state.eight == ("0"))
			return current;
		else if (state.three == ("3"))
			return current;

		int eight = toInt(state.eight);
		int three = toInt(state.three);

		if (eight + three >= 3)
		{
			eight = eight - (3 - three);
			three = 3;
			temp = state.twelve + std::to_string(eight) + std::to_string(three);
			return temp;
		}
		else
		{
			three = three + eight;
			temp = state.twelve + "0" + std::to_string(three);
			return temp;
		}
	}
	else if (action == ("3 12"))
	{
		if (state.three == ("0"))
			return current;
		else if (state.twelve == ("12"))
			return current;

		int three = toInt(state.eight);
		int twelve = toInt(state.twelve);

		if (three + twelve >= 12)
		{
			three = three - (12 - twelve);
			twelve = 12;
			temp = std::to_string(twelve) + state.eight + std::to_string(three);
			return temp;
		}
		else
		{
			twelve = twelve + three;
			temp = std::to_string(twelve) + state.eight + "0";
			return temp;
		}
	}
	else if (action == ("3 8"))
	{
		if (state.three == ("0"))
			return current;
		else if (state.eight == ("8"))
			return current;

		int three = toInt(state.three);
		int eight = toInt(state.eight);

		if (three + eight >= 8)
		{
			three = three - (8 - eight);
			eight = 8;
			temp = state.twelve + std::to_string(eight) + std::to_string(three);
			return temp;
		}
		else
		{
			eight = eight + three;
			temp = state.twelve + std::to_string(eight) + "0";
			return temp;
		}
	}
	else if (action == ("8 12"))
	{
		if (state.eight == ("0"))
			return current;
		else if (state.twelve == ("12"))
			return current;

		int eight = toInt(state.eight);
		int twelve = toInt(state.twelve);

		if (eight + twelve >= 12)
		{
			eight = eight - (12 - twelve);
			twelve = 12;
			temp = std::to_string(twelve) + std::to_string(eight) + state.three;
			return temp;
		}
		else
		{
			twelve = eight + twelve;
			temp = std::to_string(twelve) + "0" + state.three;
			return temp;
		}
	}
} // Return the result of an action performed on a state
// Return the result of an action performed on a state

bool WaterJug::isGoal() {
	if (state.three == ("1"))
		return true;
	else if (state.eight == ("1"))
		return true;
	else if (state.twelve == ("1"))
		return true;
	else
		return false;
} // Checks if current state is a goal state
// Checks if current state is a goal state

//////////////////////////////////////////////////////
////                Auxiliary				      ////
//////////////////////////////////////////////////////
int WaterJug::toInt(std::string str) { return atoi(str.c_str()); }
std::string WaterJug::getState()
{
	std::string temp = state.twelve;
	temp = temp + state.eight;
	temp = temp + state.three;
	return temp;
}
void WaterJug::g(int cost) { path_Cost = cost + 1; }