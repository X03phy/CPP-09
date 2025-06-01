
#include "PmergeMe.hpp"

int main( int argc, char **argv )
{
	(void)argc;
	(void)argv;
	std::vector<int> gello;
	gello.push_back(0);
	gello.push_back(10);

	gello.push_back(4);
	gello.push_back(1);

	std::cout << "hello" << std::endl;
	PmergeMe::mergeInsertionSort( gello );
	return ( 0 );
}
