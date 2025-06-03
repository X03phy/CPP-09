

#include "PmergeMe.hpp"

// Default constructor
PmergeMe::PmergeMe( void ) {}

// Destructor
PmergeMe::~PmergeMe( void ) {}






// Member functions

bool PmergeMe::ParseInput( std::istringstream &ss )
{
	std::string token;
	char *end;
	long nb;

	while ( ss >> token )
	{
		if ( token.size() > 11)
			return ( false );
		nb = std::strtol( token.c_str(), &end, 10 );
		if ( *end != '\0' || nb < INT_MIN || nb > INT_MAX )
			return ( false );
		_nbSequence.push_back( static_cast<int>( nb ) );
	}
	return ( true );
}

std::vector<int> generateJacobsthalSequence( int n )
{
	std::vector<int> jacobsthal;

	if ( n == 0 )
		return ( jacobsthal );

	jacobsthal.push_back( 1 );

	if ( n == 1 )
		return ( jacobsthal );

	jacobsthal.push_back( 3 );

	int i = 2;
	int next;
	while ( true )
	{
		next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		if ( next > n )
			break;
		jacobsthal.push_back( next );
		++i;
	}

	return ( jacobsthal );
}

std::vector<int> mergeInsertionSort( std::vector<int> &container )
{
	size_t n;

	// Cas de base
	n = container.size();

	if ( n <= 1 )
		return ;
	if ( n == 2 )
	{
		if ( container[0] > container[1] )
			std::swap( container[0], container[1] );
		return ( container );
	}

	// Former des pairs: grand - petit
	std::vector< std::pair<int, int> > pairs;
	bool hasOdd = ( n & 1 );
	int oddElement;

	if ( hasOdd )
	{
		oddElement = container.back();
		--n;
	}

	for ( size_t i = 0; i < n; i += 2 )
	{
		if ( container[i] > container[i + 1] )
			pairs.push_back( {container[i], container[i + 1]} );
		else
			pairs.push_back( {container[i + 1], container[i]} );
	}

	std::vector<int> largerElements;
	std::vector<int> smallerElements;

	// Tri recursif des plus grands elements de chaque paire
	for ( std::vector< std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it )
	{
		largerElements.push_back( it->first );
		smallerElements.push_back( it->second );
	}

	if ( largerElements.size() > 1 )
		largerElements = mergeInsertionSort( largerElements );

	// Creation de la chaine pricinpale
	std::vector<int> mainChain = largerElements;

	if ( !smallerElements.empty() )
	{
		for ( std::vector< std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it )
		{
			if ( it->first == mainChain[0] )
			{
				mainChain.insert( mainChain.begin(), it->second );
				break;
			}
		}
	}

	// Inserer les elements restants selon l'ordre de Jacobsthal
	std::vector<int> pendantChain;

	n = mainChain.size();
	for ( size_t i = 1; i < n; ++i )
    {
		for ( size_t j = 0; j < pairs.size(); j++ ) {
            if ( pairs[j].first == mainChain[i] )
			{
                pendantChain.push_back( pairs[j].second );
                break;
            }
        }
    }

	if ( pendantChain.size() > 1 )
	{
		std::vector<int> jacobsthalSequence = generateJacobsthalSequence( pendantChain.size() );
		
	}






	


}
