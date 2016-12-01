#include <vector>
#include <string>

struct WGCState
{
	int boat;
	int wolf;
	int goat;
	int cabbage;
};

class WGC {

public:

	WGCState state;
	std::vector<std::string> actions;
	std::string act;
	WGC *parent;
	std::string actionTaken;
	int g, f, h;

	WGC::WGC(); // Intial state constrcutor 
	WGC::WGC(WGC* parent); // Every other node constructor
	
	void Actions(); // Return set of available actions
	void Result(std::string action); // Return the result of an action performed on a state
	bool isGoal(); // Checks if current state is a goal state

	void G(int cost); // Path cost
	void H(); // Heuristic Function

	std::string toString(); // Convert struct members into single string
	std::string renderState(); // Render string to display current state
};

WGC::WGC() {
	state.boat = 0;
	state.wolf = 0;
	state.goat = 0;
	state.cabbage = 0;
	parent = this;
	g = 0, f = 0, h = 0;
	act = "";
}
// Initial Constructor

WGC::WGC(WGC* parent) {
	state.boat = parent->state.boat;
	state.wolf = parent->state.wolf;
	state.goat = parent->state.goat;
	state.cabbage = parent->state.cabbage;
	G(parent->g);
	H();
	f = g + h;
	this->parent = parent;
}
// Every node after intial constructor

void WGC::Actions() {
	if (state.boat == 0 && state.wolf == 0 && state.goat == 0 && state.cabbage == 0)
		actions.push_back("g");
	else if (state.wolf == 0 && state.boat == 0 && state.cabbage == 0 && state.goat == 1)
	{
		actions.push_back("w");
		actions.push_back("c");
		actions.push_back("b");

	}
	else if (state.goat == 0 && state.wolf == 1 && state.boat == 1 && state.cabbage == 1)
	{
		actions.push_back("w");
		actions.push_back("c");
		actions.push_back("b");
	}
	else if (state.wolf == 0 && state.boat == 0 && state.goat == 0 && state.cabbage == 1)
	{
		actions.push_back("w");
		actions.push_back("g");
	}
	else if (state.wolf == 1 && state.boat == 1 && state.goat == 1 && state.cabbage == 0)
	{
		actions.push_back("w");
		actions.push_back("g");
	}
	else if (state.goat == 0 && state.cabbage == 0 && state.boat == 0 && state.wolf == 1)
	{
		actions.push_back("c");
		actions.push_back("g");
	}
	else if (state.goat == 1 && state.cabbage == 1 && state.boat == 1 && state.wolf == 0)
	{
		actions.push_back("c");
		actions.push_back("g");
	}
	else if (state.goat == 0 && state.boat == 0 && state.wolf == 1 && state.cabbage == 1)
	{
		actions.push_back("g");
		actions.push_back("b");
	}
	else if (state.wolf == 0 && state.cabbage == 0 && state.goat == 1 && state.boat == 1)
	{
		actions.push_back("g");
		actions.push_back("b");
	}
} 
// Return set of available actions

void WGC::Result(std::string action) {

	if (action == "w")
	{
		if (state.wolf == 1)
		{
			state.wolf = 0;
			state.boat = 0;
			act = "Moved boat with wolf left.";
		}
		else
		{
			state.wolf = 1;
			state.boat = 1;
			act = "Moved boat with wolf right.";
		}
	}
	else if (action == "g")
	{
		if (state.goat == 1)
		{
			state.goat = 0;
			state.boat = 0;
			act = "Moved boat with goat left.";
		}
		else
		{
			state.goat = 1;
			state.boat = 1;
			act = "Moved boat with goat right.";
		}
	}
	else if (action == "c")
	{
		if (state.cabbage == 1)
		{
			state.cabbage = 0;
			state.boat = 0;
			act = "Moved boat with cabbage left.";
		}
		else
		{
			state.cabbage = 1;
			state.boat = 1;
			act = "Moved boat with cabbage right.";
		}
	}
	else
	{
		if (state.boat == 1)
		{
			state.boat = 0;
			act = "Moved empty boat left.";
		}
		else
		{
			state.boat = 1;
			act = "Moved empty boat right.";
		}
	}
} 
// Return the result of an action performed on a state

bool WGC::isGoal() {
		if (toString() == "1111")
			return true;
		return false;
} 
// Checks if current state is a goal state

void WGC::G(int cost) { g = cost + 1; }
// Path cost

void WGC::H() 
{
	h = 0;
	if (state.wolf == 0)
		h++;
	if (state.goat == 0)
		h++;
	if (state.cabbage == 0)
		h++;
	if (state.boat == 0)
		h++;
}
// Heuristic Function

std::string WGC::toString() 
{  
	std::string combined = "";

	combined += std::to_string(state.boat);
	combined += std::to_string(state.wolf);
	combined += std::to_string(state.goat);
	combined += std::to_string(state.cabbage);

	return combined;
}
// Convert struct members into single string

std::string WGC::renderState()
{
	std::string str = "";

	if (state.boat == 0 && state.wolf == 0 && state.goat == 0 && state.cabbage == 0)
		str = "B,W,G,C | ";
	else if (state.wolf == 0 && state.boat == 0 && state.cabbage == 0 && state.goat == 1)
		str = "B,W,C | G";
	else if (state.goat == 0 && state.wolf == 1 && state.boat == 1 && state.cabbage == 1)
		str = "G | B,W,C";
	else if (state.wolf == 0 && state.boat == 0 && state.goat == 0 && state.cabbage == 1)
		str = "W,B,G | C";
	else if (state.wolf == 1 && state.boat == 1 && state.goat == 1 && state.cabbage == 0)
		str = "C | W,B,G";
	else if (state.goat == 0 && state.cabbage == 0 && state.boat == 0 && state.wolf == 1)
		str = "G,C,B | W";
	else if (state.goat == 1 && state.cabbage == 1 && state.boat == 1 && state.wolf == 0)
		str = "W | G,C,B";
	else if (state.goat == 0 && state.boat == 0 && state.wolf == 1 && state.cabbage == 1)
		str = "G,B | W,C";
	else if (state.wolf == 0 && state.cabbage == 0 && state.goat == 1 && state.boat == 1)
		str = "W,C | G,B";
	else if (state.wolf == 1 && state.cabbage == 1 && state.goat == 1 && state.boat == 1)
		str = " | B,W,G,C";
	return str;
}
// Render string to display current state