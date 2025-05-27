#include "BitcoinExchange.hpp"

// Canonical form

// Default constructor and Destructor
BitcoinExchange::BitcoinExchange( void ) {}
BitcoinExchange::~BitcoinExchange( void ) {}

// Copy constructor
BitcoinExchange::BitcoinExchange( const BitcoinExchange &other ) : _date( other._date ), _value( other._value ) {}

// Copy assignment operator
BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange &other )
{
	if ( this != &other )
	{
		_date = other._date;
		_value = other._value;
	}
	return (*this);
}

// Member functions

// Setters
bool BitcoinExchange::setBitcoinExchange( std::ifstream &infile )
{
	std::string delimiter;

	std::getline(infile, _date, ' ');
	std::getline(infile, delimiter, ' ');
	std::getline(infile, delimiter);

	this->checkDate();
	this->checkValue();

	return ( true );
}

std::vector<BitcoinExchange> BitcoinExchange::setBitcoinExchanges( std::ifstream &infile )
{
	std::vector<BitcoinExchange> bitcoin_exchanges;
	BitcoinExchange bitcoin_exchange;

	while ( infile.peek() != EOF && bitcoin_exchange.setBitcoinExchange( infile ) == true )
		bitcoin_exchanges.push_back( bitcoin_exchange );

	return ( bitcoin_exchanges );
}

// Getters
std::string BitcoinExchange::getDate( void ) const
{
	return (_date);
}

float BitcoinExchange::getValue( void ) const
{
	return (_value);
}

// Date
void BitcoinExchange::checkDate( void )
{
	if ( _date.size() != 10 )
		return ( false );

	unsigned char i = 0 ;
	unsigned short int year = 0;
	unsigned char month = 0;
	unsigned char day = 0;

	for ( ; i < 4; ++i )
	{
		if ( isdigit( _date[i] ) == 0 )
			return ( false );
		year = 10 * year + ( _date[i] - '0' );
	}

	if (_date[i] != '-')
		return ( false );

	++i;

	for ( ; i < 7; ++i )
	{
		if ( isdigit( _date[i] ) == 0 )
			return ( false );
		month = 10 * month + ( _date[i] - '0' );
	}

	if (_date[i] != '-')
		return ( false );

	++i;

	for ( ; i < 10; ++i )
	{
		if ( isdigit( _date[i] ) == 0 )
			return ( false );
		day = 10 * day + ( _date[i] - '0' );
	}

	if ( _date[i] != '\0' )
		return ( false );

	if ( year < 2009 || year > 2025 )
		return ( false );

	if ( month < 1 || month > 12 )
		return ( false );

	if ( day < 1 || day > 31 )
		return ( false );

	// Cas particuliers

	if ( year == 2009 && day < 12 ) // date du premier echange de bitcoins: 12/01/2009
		return ( false );

	// if ( year == 2025 )
	// {
	// 	if ()
	// }

	_isPrintable = true;
}

// Value
void BitcoinExchange::checkValue( void )
{
}
