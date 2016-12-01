#include <vector>
#include <string>
#include <math.h>

struct M_BState
{
	struct monkey {
		int location;
		int item;
	};
	struct banana {
		int location;
		int id = 1;
		bool held;
		bool suspended;
	};
	struct chair {
		int location;
		int id = 2;
		bool held;
	};
	struct stick {
		int location;
		int id = 3;
		bool held;
	};
};

class M_B {

public:

	M_BState::monkey monkey;
	M_BState::banana banana;
	M_BState::chair chair;
	M_BState::stick stick;

	std::vector<std::string> actions;
	std::string act;
	M_B *parent;
	std::string actionTaken;
	int g, f, h;

	M_B::M_B(); // Intial state constrcutor 
	M_B::M_B(M_B* parent); // Every other node constructor

	void Actions(); // Return set of available actions
	void Result(std::string action); // Return the result of an action performed on a state
	bool isGoal(); // Checks if current state is a goal state

	void G(int cost); // Path cost
	void H(); // Heuristic Function

	std::string toString(); // Convert struct members into single string
	std::string renderState(); // Render string to display current state
};

M_B::M_B() {
	monkey.location = 1, monkey.item = 0;
	banana.location = 2, banana.held = false, banana.suspended = true;
	chair.location = 3,  chair.held = false;
	stick.location = 4, stick.held = false;
	g = 0, f = 0, h = 0;
	parent = this;
	act = "";
}
// Initial Constructor

M_B::M_B(M_B* parent) {
	monkey.location = parent->monkey.location, monkey.item = parent->monkey.item;
	banana.location = parent->banana.location, banana.held = parent->banana.held, banana.suspended = parent->banana.suspended;
	chair.location = parent->chair.location, chair.held = parent->chair.held;
	stick.location = parent->stick.location, stick.held = parent->stick.held;
	G(parent->g);
	H();
	f = g + h;
	this->parent = parent;
}
// Every node after intial 

void M_B::Actions() {

	if (monkey.location != 1 && monkey.location != 4)
		actions.push_back("m1");
	if (monkey.location != 2 && monkey.location != 3)
		actions.push_back("m2");
	if (monkey.location != 3 && monkey.location != 2)
		actions.push_back("m3");
	if (monkey.location != 4 && monkey.location != 1)
		actions.push_back("m4");
	// Move monkey

	if (monkey.location == banana.location && !banana.suspended && monkey.item == 0)
		actions.push_back("p1");
	if (monkey.location == chair.location && monkey.item == 0)
		actions.push_back("p2");
	if (monkey.location == stick.location && monkey.item == 0)
		actions.push_back("p3");
	// Pick up items

	else if (chair.held)
		actions.push_back("d2");
	else if (stick.held)
		actions.push_back("d3");
	// Drop items

	if (stick.held && banana.location == monkey.location && chair.location == monkey.location && banana.suspended)
		actions.push_back("s");
	// Swing stick only with the correct state configuration 
	// Does not make sense to swing w/o because the state is uneffected

}
// Return set of available actions

void M_B::Result(std::string action) {
	if (action == "m1")
	{
		monkey.location = 1;
		if (monkey.item != 0)
		{
			if (monkey.item == banana.id)
				banana.location = monkey.location;
			else if (monkey.item == chair.id)
				chair.location = monkey.location;
			else
				stick.location = monkey.location;
		}
		act = "Moved to (0,0)";
	}
	else if (action == "m2")
	{
		monkey.location = 2;
		if (monkey.item != 0)
		{
			if (monkey.item == banana.id)
				banana.location = monkey.location;
			else if (monkey.item == chair.id)
				chair.location = monkey.location;
			else
				stick.location = monkey.location;
		}
		act = "Moved to (0,1)";
	}
	else if (action == "m3")
	{
		monkey.location = 3;
		if (monkey.item != 0)
		{
			if (monkey.item == banana.id)
				banana.location = monkey.location;
			else if (monkey.item == chair.id)
				chair.location = monkey.location;
			else
				stick.location = monkey.location;
		}
		act = "Moved to (1,0)";
	}
	else if (action == "m4")
	{
		monkey.location = 4;
		if (monkey.item != 0)
		{
			if (monkey.item == banana.id)
				banana.location = monkey.location;
			else if (monkey.item == chair.id)
				chair.location = monkey.location;
			else
				stick.location = monkey.location;
		}
		act = "Moved to (1,1)";
	}
	else if (action == "p1")
	{
		monkey.item = banana.id;
		banana.held = true;
		act = "Picked up bananas";
	}
	else if (action == "p2")
	{
		monkey.item = chair.id;
		chair.held = true;
		act = "Picked up chair";
	}
	else if (action == "p3")
	{
		monkey.item = stick.id;
		stick.held = true;
		act = "Picked up stick";
	}
	else if (action == "d2")
	{
		chair.held = false;
		monkey.item = 0;
		act = "Dropped chair";
	}
	else if (action == "d3")
	{
		stick.held = false;
		monkey.item = 0;
		act = "Dropped stick";
	}
	else if (action == "s")
	{
		banana.suspended = false;
		act = "Swung stick";
	}
}
// Return the result of an action performed on a state

bool M_B::isGoal() {
	if (monkey.item == banana.id)
		return true;
	return false;
}
// Checks if current state is a goal state

void M_B::G(int cost) { g = cost + 1; }
// Path cost

void M_B::H()
{
	h = 0;

	int diff = abs(monkey.location - banana.location);
	if (diff == 2)
		h = h + 2;
	else if (diff == 1 || diff == 3)
		h++;
	else
		h = h;

	diff = abs(chair.location - banana.location);
	if (diff == 2)
		h = h + 2;
	else if (diff == 1 || diff == 3)
		h++;
	else
		h = h;

	diff = abs(stick.location - banana.location);
	if (diff == 2)
		h = h + 2;
	else if (diff == 1 || diff == 3)
		h++;
	else
		h = h;
	
}
// Heuristic Function

std::string M_B::toString() 
{
	std::string combined = "";

	combined += std::to_string(monkey.location);
	combined += std::to_string(banana.location);
	combined += std::to_string(chair.location);
	combined += std::to_string(stick.location);
	combined += std::to_string(banana.held);
	combined += std::to_string(chair.held);
	combined += std::to_string(stick.held);
	combined += std::to_string(monkey.item);
	combined += std::to_string(banana.suspended);
	
	return combined;
}
// Convert struct members into single string

std::string M_B::renderState()
{
	std::string str = "";

	if (monkey.location == 1)
		str = "Monkey located in (0,0)";
	else if (monkey.location == 2)
		str = "Monkey located in (0,1)";
	else if (monkey.location == 3)
		str = "Monkey located in (1,0)";
	else if (monkey.location == 4)
		str = "Monkey located in (1,1)";

	if (monkey.item == 1)
		str += " holding bananas.";
	else if (monkey.item == 2)
		str += " holding the chair.";
	else if (monkey.item == 3)
		str += " holding the stick.";
	else
		str += " holding nothing.";

	return str;
}
// Render string to display current state