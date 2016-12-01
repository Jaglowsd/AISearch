# AISearch
Artificial Intelligence Search Algorithms

\Overview:   
Both projects are written entirely in c++ and were run in visual studios 2013. Both project consist of familair AI search algorithms, domains to test the algorithms on, and an output of an algorithm with a domain. The goal of each of the algorithms was to make them as universal as possible in order to run most domains on them so the algorithms are templated to accept most types of domains. It was quite challenging to design entirely universal algoirhtms due to the fact that some domains have state solutions and others have path solutions in addition to the fact that some domains have predetermiend state spaces such as the Traveling Salesman problem, where other states spaces could be generated when needed such as monkeys and bananas. The projects themselves are not available for download here but the necessary source files are. So if you are interested in running it yourself, create a project in your favorite IDE that supports c++ and give it a go! The only changes that would need to be made are in the main.cpp file where you specify which combination of alogrithm and domain you want.

\UniformedSearch:
Consisting of a Depth-First Search (DFS) usgin a stack, Iterative Deepening Search (IDS), and Depth-Limited Search algorithms. Each of these algorithms are templated and will therefore accept templated domain classes. The domains are: 8-puzzle and 3 Water Jug (12, 8, 3 units). The only real requriement is that the domain classes have similar functions and memebers in order for the alogorithms to work properly. Most of the work is done in the domain class. The algoithm simply specifes the steps that each domain should take.

\Informed Search:
Algorithms: A* Search and A* Beam Search. Domains: Monkeys and Bananas, Route-Finding Traveling Salesman, and Wolf, Goat, and Cabbage.
Similar to UniformedSearch in that most of the algorithms and domains are templated with the excpetion of the Route-Finding Traveling Salesman Problem.

\Output:
Both of the output files show the algorithm and domain in use, the first 40 state transitions, the starte state, empirical information about run time, and a state solution or path solution.
    
