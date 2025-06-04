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

// Sequence utilisable dans l'algorithme Ford-Johnson
std::vector<int> PmergeMe::generateJacobsthalSequence( int n )
{
	std::vector<int> jacobsthal;

	jacobsthal.push_back( 0 );

	if ( n == 0 )
		return ( jacobsthal );

	jacobsthal.push_back( 1 );

	if ( n <= 3 )
		return ( jacobsthal );

	jacobsthal.push_back( 3 );

	int next;
	while ( 1 )
	{
		next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		if ( next > n )
			break;
		jacobsthal.push_back( next );
	}

	return ( jacobsthal );
}

std::vector<int> PmergeMe::getInsertPos( std::vector<int> &jacobsthalSequence, size_t n )
{
	std::vector<int> order;

	for ( size_t i = 0; i < jacobsthalSequence.size(); ++i )
	{
		order.push_back( jacobsthalSequence[i] );
		for ( int j = ( jacobsthalSequence[i] - 1 ); j > jacobsthalSequence[i - 1]; --j )
			order.push_back(j);
	}

	for ( size_t i = ( jacobsthalSequence[jacobsthalSequence.size() - 1] + 1 ); i < n; ++i )
		order.push_back(i);

	return ( order );
}


void PmergeMe::MergeThat( void )
{
	struct timeval start, end;
	long seconds, micros;

	std::cout << "----------vector----------" << std::endl;

	gettimeofday(&start, NULL);
	_vectorSequenceSorted = mergeInsertionSort( this->_vectorSequence );
	gettimeofday(&end, NULL);

	seconds = end.tv_sec - start.tv_sec;
	micros = end.tv_usec - start.tv_usec;
	_vectorTime = seconds * 1000000 + micros;

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

	std::cout << "Time: " << _vectorTime << " µs" << std::endl;

	std::cout << "checker: ";
	if ( this->checker( _vectorSequence, _vectorSequenceSorted ) != false )
		std::cout << "OK" << std::endl;
	else
		std::cout << "KO" << std::endl;


	std::cout << "----------deque----------" << std::endl;

	gettimeofday(&start, NULL);
	_dequeSequenceSorted = mergeInsertionSort( this->_dequeSequence );
	gettimeofday(&end, NULL);

	seconds = end.tv_sec - start.tv_sec;
	micros = end.tv_usec - start.tv_usec;
	_dequeTime = seconds * 1000000 + micros;

	std::cout << "Before: ";
	for ( size_t i = 0; i < _dequeSequence.size(); ++i )
	{
		std::cout << _dequeSequence[i];
		if ( i != _dequeSequence.size() - 1 )
			std::cout << ' ';
		else
			std::cout << std::endl;
	}

	std::cout << "After:  ";
	for ( size_t i = 0; i < _dequeSequenceSorted.size(); ++i )
	{
		std::cout << _dequeSequenceSorted[i];
		if ( i != _dequeSequenceSorted.size() - 1 )
			std::cout << ' ';
		else
			std::cout << std::endl;
	}

	std::cout << "Time: " << _dequeTime << " µs" << std::endl;

	std::cout << "checker: ";
	if ( this->checker( _dequeSequence, _dequeSequenceSorted ) != false )
		std::cout << "OK" << std::endl;
	else
		std::cout << "KO" << std::endl;
}
