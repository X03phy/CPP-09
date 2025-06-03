#include "PmergeMe.hpp"

// Default constructor
PmergeMe::PmergeMe( void ) {}

// Destructor
PmergeMe::~PmergeMe( void ) {}

// Copy constructor
PmergeMe::PmergeMe( const PmergeMe &other ) : _vectorSequence( other._vectorSequence ), _dequeSequence( other._dequeSequence ) {}

// Copy assignment operator
PmergeMe &PmergeMe::operator=( const PmergeMe &other )
{
	if ( this != &other )
	{
		_vectorSequence = other._vectorSequence;
		_dequeSequence = other._dequeSequence;
	}

	return ( *this );
}

// Member functions
bool PmergeMe::ParseInput( char **argv )
{
	std::string token;
	char *end;
	long nb;

	for ( int i = 1; argv[i] != NULL; ++i )
	{
		std::string token(argv[i]);
		
		if ( token.size() > 11)
			return ( false );
		nb = std::strtol( token.c_str(), &end, 10 );
		if ( *end != '\0' || nb < INT_MIN || nb > INT_MAX )
			return ( false );
		_vectorSequence.push_back( static_cast<int>( nb ) );
		_dequeSequence.push_back( static_cast<int>( nb ) );
	}
	return ( true );
}

std::vector<int> PmergeMe::generateJacobsthalSequence( int n )
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
	while ( 1 )
	{
		next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		if ( next > n )
			break;
		jacobsthal.push_back( next );
		++i;
	}

	return ( jacobsthal );
}

std::vector<int> PmergeMe::mergeInsertionSort( std::vector<int> &container )
{
	// Cas de base
	size_t n = container.size();

	if ( n <= 1 )
		return ( container );
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
			pairs.push_back( std::make_pair( container[i], container[i + 1] ) );
		else
			pairs.push_back( std::make_pair(container[i + 1], container[i]) );
	}

	// Tri recursif des plus grands elements de chaque paire
	std::vector<int> largerElements;
	std::vector<int> smallerElements;

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

	// On cree la liste de petits nombres
	std::vector<int> pendantChain;

	for ( size_t i = 2; i < mainChain.size(); ++i )
	{
		for ( size_t j = 0; j < pairs.size(); ++j )
		{
			if ( pairs[j].first == mainChain[i] )
			{
				pendantChain.push_back( pairs[j].second );
				break;
			}
		}
	}

	// On place les petits nombres
	std::vector<int> jacobsthalSequence = generateJacobsthalSequence( pendantChain.size() );
	int index;
	int value;
	std::vector<int>::iterator pos;

	for (size_t i = 0; i < jacobsthalSequence.size(); ++i)
	{
		index = jacobsthalSequence[i] - 1; // car la séquence est en base 1
		if ( static_cast<size_t>(index) >= pendantChain.size() )
			continue; // protection au cas où

		value = pendantChain[index];
		pos = std::lower_bound(mainChain.begin(), mainChain.end(), value);
		mainChain.insert(pos, value);
	}

	// Gerer le dernier nb
	if ( hasOdd )
	{
		std::vector<int>::iterator pos = std::lower_bound( mainChain.begin(), mainChain.end(), oddElement );
		mainChain.insert( pos, oddElement );
	}

	return ( mainChain );

}

bool PmergeMe::checker( void )
{
	if ( _vectorSequence.size() != _vectorSequenceSorted.size() )
		return ( false );

	for ( size_t i = 0; ( i + 1 ) < _vectorSequenceSorted.size(); ++i )
		if ( _vectorSequenceSorted[i] > _vectorSequenceSorted[i + 1] )
			return ( false );

	return ( true );
}

void PmergeMe::MergeThat( void )
{
	std::cout << "----------vector----------" << std::endl;
	_vectorSequenceSorted = mergeInsertionSort( this->_vectorSequence );

	std::cout << "Before: ";
	for ( size_t i = 0; i < _vectorSequence.size(); ++i )
	{
		std::cout << _vectorSequence[i];
		if ( i != _vectorSequence.size() - 1 )
			std::cout << ' ';
		else
			std::cout << std::endl;
	}

	std::cout << "After:  ";
	for ( size_t i = 0; i < _vectorSequenceSorted.size(); ++i )
	{
		std::cout << _vectorSequenceSorted[i];
		if ( i != _vectorSequenceSorted.size() - 1 )
			std::cout << ' ';
		else
			std::cout << std::endl;
	}

	std::cout << "checker: ";
	if ( this->checker() == false )
		std::cout << "OK" << std::endl;
	else
		std::cout << "KO" << std::endl;

	std::cout << "----------deque----------" << std::endl;
}
