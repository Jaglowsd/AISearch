#include <queue>
#include <unordered_set>
#include <vector>
#include <time.h>
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include <map>

struct compare {
	template <class T>
	bool operator()(T *node1, T *node2) {
		return node1->f > node2->f;
	}
};

template <class T> class Algorithms {

public:

	Algorithms(std::string);
	Algorithms();

	void aStar(); // A* Search
	void aStarBeam(int k); // A* Beam Search
	
	void printStateActions(T* domain); // Print the current state of a node along with the action that led to that state
	void printSolutionPath(T* domain); // Prints path of solution

	bool noShow = false;
	clock_t begin;
	clock_t end;
	double time;
	int counter = 0;

private:

	std::unordered_set <std::string> closed_list; // Heap 
	std::priority_queue<T*, std::vector<T*>, compare> open_list; // Minimum priority queue with type T
	std::priority_queue<T*, std::vector<T*>, compare> beam_list; // Beam search list
	std::map<char, std::map<char, int>> graph; // Store TSP graph
	std::vector<T*> pathSolution;
};

template <class T>
Algorithms<T>::Algorithms() {}
// Default Constructor

template <class T>
Algorithms<T>::Algorithms(std::string str) 
{
	std::ifstream in;
	std::string filename = "graph.txt";
	in.open(filename.c_str());

	while (!in.eof()) 
	{
		char key;
		int edge_count;
		in >> key >> edge_count;
		for (int i = 0; i < edge_count; i++)
		{
			char first;
			int second;
			in >> first >> second;
			graph[key].insert(std::pair<char, int>(first, second));
		}
	}
	in.close();
}
// Construct TSP graph from text file

template <class T>
void Algorithms<T>::aStar()
{
	T* node = new T('A', 'B', graph['A']);
	open_list.push(node);

	std::cout << "Algorithm: A* Search" << std::endl;
	std::cout << "Starting state: " << node->renderState() << std::endl;
	noShow = true;

	while (!open_list.empty())
	{
		T *top = open_list.top();
		open_list.pop();
		closed_list.insert(std::string(1, top->vertex));
		if (top->isGoal())
		{
			printSolutionPath(top);
			return;
		}
		std::map<char, int>::iterator map_itr;
		for (map_itr = top->edges.begin(); map_itr != top->edges.end(); map_itr++)
		{
			T* successor_node = new T(graph[map_itr->first], map_itr->first, top->goal, top);
			std::unordered_set<std::string>::iterator set_itr = closed_list.find(std::string(1, successor_node->vertex));
			if (set_itr == closed_list.end())
			{
				counter++;
				open_list.push(successor_node);
			}
		}
	}
}
// A* Search

template <class T>
void Algorithms<T>::aStarBeam(int k)
{
	T* node = new T();
	beam_list.push(node);

	std::cout << "Algorithm: A* Beam Search" << std::endl;
	std::cout << "Starting state: " << node->renderState() << std::endl;

	begin = clock();
	while (!beam_list.empty())
	{
		while (!beam_list.empty())
		{
			T *top = beam_list.top();
			beam_list.pop();
			closed_list.insert(top->toString());

			if (top->isGoal())
			{
				printSolutionPath(top);
				return;
			}

			top->Actions();
			std::vector<std::string>::iterator itr;
			for (itr = top->actions.begin(); itr != top->actions.end(); itr++)
			{
				T* successor_node = new T(top);
				successor_node->Result(*itr);
				open_list.push(successor_node);
				counter++;
				if (counter <= 40)
					printStateActions(successor_node);
			}
		}

		while (!open_list.empty() && beam_list.size() < k)
		{
			T *top = open_list.top();
			open_list.pop();
			std::unordered_set<std::string>::iterator set_itr = closed_list.find(top->toString());
			if (set_itr == closed_list.end())
			{
				beam_list.push(top);
			}
		}
	}
}
// A* Beam Search

template <class T>
void Algorithms<T>::printStateActions(T* domain)
{
	std::cout << "Action taken: " << domain->act << std::endl;
	std::cout << "Current state: " << domain->renderState() << std::endl;
}
// Print the current state of a node along with the action that led to that state

template <class T>
void Algorithms<T>::printSolutionPath(T* domain)
{
	end = clock();
	time = ((double)(end - begin) / CLOCKS_PER_SEC);
	if (domain->parent != domain)
	{
		pathSolution.push_back(domain);
		printSolutionPath(domain->parent);
	}
	else
	{
		pathSolution.push_back(domain);

		std::cout << std::endl;
		if (counter > 40)
			std::cout << "40+ expansions required for solution. Sleep mode" << std::endl;
		std::cout << "Total algorithm time: " << time << " seconds" << std::endl;
		std::cout << "Total number of nodes expanded: " << counter << std::endl;
		std::cout << "Solution path length: " << pathSolution.size() - 1 << std::endl << std::endl;
		std::cout << "Solution Path: " << std::endl;
		for (typename std::vector<T*>::reverse_iterator itr = pathSolution.rbegin(); itr != pathSolution.rend(); itr++)
		{
			T* domain = *itr;
			if (!noShow)
			{
				if (domain->act != "")
					std::cout << "Action:  " << domain->act << std::endl;
			}
			std::cout << "State:  " << domain->renderState() << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
}
// Prints path of solution