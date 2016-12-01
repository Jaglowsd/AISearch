#include <stack>
#include <queue>
#include <list>
#include <unordered_set>
#include <vector>
#include <time.h>
#include <iostream>

template <class T> class Searches {

public:

	Searches();

	void DFS(); // Depth-First Search
	void IDS(); // Iterative-Deepening Search
	bool DLS(T* domain, int depth); // Depth Limited Search
	void showResults(T* domain); // Print empirical data for a solution
	void printStateActions(T* domain, std::string actions); // Print the current state of a node along with the action that led to that state
	void printSolutionPath(T* domain); // Prints path of solution

	bool success;
	clock_t begin;
	clock_t end;
	double time;
	int counter = 0;

private:

	std::unordered_set <std::string> explored_set;
	std::vector<T*> pathSolution;
};

template <class T>
Searches<T>::Searches() {}
// Constructor

template <class T>
void Searches<T>::DFS() 
{
	T* domain = new T();
	domain->parent = domain;
	std::cout << "Algorithm in use: DFS" << std::endl;
	std::cout << "Starting state: " << domain->getState() << std::endl;

	explored_set.clear();
	std::stack<T*> open_list;

	open_list.push(domain);
	explored_set.insert(domain->getState());

	bool added = false;
	success = false;

	begin = clock();
	while (!open_list.empty())
	{
		//T* top = open_list.top();
		added = false;

		open_list.top()->Actions();
		std::vector<std::string>::iterator itr = open_list.top()->actions.begin();
		while (itr != open_list.top()->actions.end())
		{
			std::string acts = *itr;
			std::string next_state = open_list.top()->Result(*itr);
			std::unordered_set<std::string>::iterator itr2 = explored_set.find(next_state);
			itr++;
			if ((itr2 == explored_set.end())) 
			{
				T* new_node = new T(next_state, open_list.top(), acts);
				open_list.push(new_node);
				explored_set.insert(next_state);
				success = new_node->isGoal();
				counter++;
				if (counter <= 40)
					printStateActions(new_node, acts);
				if (success)
				{
					showResults(new_node);
					if (new_node->path_Cost < 250)
						printSolutionPath(new_node);
					else
						std::cout << "Solution path too long. Not printing." << std::endl << std::endl;
					return;
				}
				added = true;
				itr = open_list.top()->actions.end();
			}
		}
		if (!added)
		{
			T* remove = open_list.top();
			open_list.pop();
			delete remove;
			added = false;
		}
	}
	end = clock();
	time = ((double)(end - begin) / CLOCKS_PER_SEC);
	std::cout << "Total time for no solution: " << time << std::endl;
	return;
}
// Depth-First Search

template <class T>
void Searches<T>::IDS() {
	T* domain = new T();
	domain->parent = domain;
	explored_set.clear();

	std::cout << "Algorithm in use: IDS" << std::endl;
	std::cout << "Starting state: " << domain->getState() << std::endl;

	bool added = false;
	success = false;

	begin = clock();
	for (int limit = 0; limit < 20; limit++)
	{
		success = DLS(domain, limit);
		if (success)
			return;
	}
}
// Iterative-Deepening Search

template <class T>
bool Searches<T>::DLS(T* node, int depth)
{
	if (node->isGoal())
	{
		showResults(node);
		if (node->path_Cost < 250)
			printSolutionPath(node);
		else
			std::cout << "Solution path too long. Not printing." << std::endl;
		return true;
	}
	else if (depth <= 0)
		return false;
	else 
	{
		node->Actions();
		std::vector<std::string>::iterator itr;
		for (itr = node->actions.begin(); itr != node->actions.end(); itr++)
		{
			std::string acts = *itr;
			std::string next_state = node->Result(*itr);
			std::unordered_set<std::string>::iterator itr2 = explored_set.find(next_state);
			if ((itr2 == explored_set.end()))
				explored_set.insert(next_state);
			T* new_node = new T(next_state, node, *itr);
			counter++;
			if (counter <= 40)
				printStateActions(new_node, acts);
			if (DLS(new_node, depth - 1))
				return true;
		}
	}
	return false;
}
// Depth-Limited Search

template <class T>
void Searches<T>::printStateActions(T* domain, std::string action)
{
	std::cout << "Action taken: " << action << std::endl;
	std::cout << "Current state: " << domain->getState() << std::endl;
}
// Print the current state of a node along with the action that led to that state

template <class T>
void Searches<T>::showResults(T* domain)
{
	if (counter >= 40)
	{
		std::cout << std::endl;
		std::cout << "40+ expansions required for solution. Sleep mode" << std::endl;
	}
	end = clock();
	time = ((double)(end - begin) / CLOCKS_PER_SEC);
	std::cout << "Total algorithm time: " << time << " seconds" << std::endl;
	std::cout << "Total number of nodes expanded: " << counter << std::endl;
	std::cout << "Solution path length: " << domain->path_Cost << std::endl;
	std::cout << "Solution state: " << domain->getState() << std::endl << std::endl;
}
// Print empirical data for a solution

template <class T>
void Searches<T>::printSolutionPath(T* domain) 
{
	if (domain->parent != domain)
	{
		pathSolution.push_back(domain);
		printSolutionPath(domain->parent);
	}
	else
	{
		pathSolution.push_back(domain);
		std::cout << "Solution Path: " << std::endl;
		for (typename std::vector<T*>::reverse_iterator itr = pathSolution.rbegin(); itr != pathSolution.rend(); itr++)
		{
			T* domain = *itr;
			if (domain->actionTaken != "")
				std::cout << "Action Taken: " << domain->actionTaken << std::endl;
			std::cout << "Configuration: " << domain->getState() << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
}
// Prints path of solution