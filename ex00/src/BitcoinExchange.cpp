#include "BitcoinExchange.hpp"

// Canonical form

// Default constructor and Destructor
BitcoinExchange::BitcoinExchange( void ) : _date( "0000-00-00" ), _value( 0 ), _rate( 0 ), _isPrintable( false ), _errorMessage( "None" ) {}
BitcoinExchange::~BitcoinExchange( void ) {}

// Copy constructor
BitcoinExchange::BitcoinExchange( const BitcoinExchange &other ) : _date( other._date ), _value( other._value ), _rate( other._rate ), _isPrintable( other._isPrintable ), _errorMessage( other._errorMessage ) {}

// Copy assignment operator
BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange &other )
{
	if ( this != &other )
	{
		_date = other._date;
		_value = other._value;
		_rate = other._rate;
		_isPrintable = other._isPrintable;
		_errorMessage = other._errorMessage;
	}
	return (*this);
}

// Member functions

// Getters
std::string BitcoinExchange::getDate( void ) { return ( _date ); }
float BitcoinExchange::getValue( void ) { return ( _value ); }
float BitcoinExchange::getRate( void ) { return ( _rate ); }
bool BitcoinExchange::getIsPrintable( void ) { return ( _isPrintable ); }
std::string BitcoinExchange::getErrorMessage( void ) { return ( _errorMessage ); }

// Input
bool BitcoinExchange::checkInputLine( std::string &line )
{
	unsigned char i = 0 ;

	for ( ; i < 4; ++i )
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
	}

	if ( line[i] != '-' )
		return ( false );

	++i;

	for ( ; i < 7; ++i )
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
	}

	if (line[i] != '-')
		return ( false );

	++i;

	for ( ; i < 10; ++i )
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
	}

	if ( line[i] != ' ' )
		return ( false );

	++i;

	if ( line[i] != '|' )
		return ( false );

	++i;

	if ( line[i] != ' ' )
		return ( false );

	float value;
	char *end;
	const char *exchange;

	exchange = line.c_str() + i;
	value = std::strtof( exchange, &end );
	if ( end == exchange || *end != '\0')
		return ( false );

	std::istringstream ss( line );

	getline( ss, _date, ' ' );
	_value = value;

	return (true);
}

// Data
// bool BitcoinExchange::parseData( std::ifstream &infile )
// {
// 	getline( infile, data ); // skip la premiere ligne : "date,exchange_rate"
// 	if ( data != "date,exchange_rate" )
// 	{
// 		_errorMessage = "Missing \"date,exchange_rate\" on top ( line 1 ) of data file";
// 		return ( false );
// 	}
// 		getline( ss, date, ',');
// 	if ( _date == date )
// 	{
// 		char *end;

// 		getline( ss, rate );
// 		_rate = std::strtof( rate.c_str(), &end );
// 		if (end == rate.c_str() || *end != '\0')
// 		{
// 			_errorMessage = "Invalid rate in "
// 			return ( false );
// 		}

// 		return ( true );
// 	}
// }

void BitcoinExchange::extractRateFromData( std::ifstream &infile )
{
	std::string data;
	std::string date;
	std::string rate;

	infile.clear();            // Clear EOF flag
	infile.seekg(0, std::ios::beg); // Remet le curseur au début du fichier


	getline( infile, data ); // skip la premiere ligne : "date,exchange_rate"
	while ( getline( infile, data ) )
	{
		std::istringstream ss( data );

		getline( ss, date, ',');
		if ( _date == date )
		{
			getline( ss, rate );
			_rate = std::strtof( rate.c_str(), NULL );
			this->_isPrintable = true;

			return ;
		}
	}
	_errorMessage = "No exchange was made that day";
}

// Creation
bool BitcoinExchange::createBitcoinExchange( std::ifstream &infile, std::ifstream &data )
{
	std::string line;

	getline( infile, line );
	if ( line == "" )
		return ( false );
	if ( this->checkInputLine( line ) == false )
	{
		this->_errorMessage = "Error: bad input => " + line;
		return ( true );
	}
	this->extractRateFromData( data );

	return ( true );
}

std::vector<BitcoinExchange> BitcoinExchange::createBitcoinExchanges( std::ifstream &infile, std::ifstream &data )
{
	std::vector<BitcoinExchange> bitcoin_exchanges;

	while ( !infile.eof() )
	{
		BitcoinExchange bitcoin_exchange;

		bitcoin_exchange.createBitcoinExchange( infile, data ); // Tant qu'on reussi a creer des BitcoinExchange on continue => on n'est pas a la fin du fichier.
		bitcoin_exchanges.push_back( bitcoin_exchange );
	}

	return ( bitcoin_exchanges );
}

// Print
void BitcoinExchange::printBitcoinExchanges( std::vector<BitcoinExchange> bitcoin_exchanges )
{
	float result;
	std::vector<BitcoinExchange>::iterator it;

	for ( it = bitcoin_exchanges.begin(); it != bitcoin_exchanges.end(); ++it )
	{
		if ( it->getIsPrintable() == true )
		{
			result = ( it->getValue() ) * ( it->getRate() );
			std::cout << it->getDate() << " => " << it->getValue() << " = " << result << std::endl;
		}
		else
			std::cout << it->getErrorMessage() << std::endl;
	}
}
