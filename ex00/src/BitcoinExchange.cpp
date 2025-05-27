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
void BitcoinExchange::setClass( std::ifstream &infile )
{
	std::string delimiter;

	std::getline(infile, _date, ' ');
	std::getline(infile, delimiter, ' ');
	std::getline(infile, delimiter);

	if ( this->isValidDate() && this->isValidValue() )
		std::cout << "It works!!" << std::endl;
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
bool BitcoinExchange::isValidDate( void ) const
{
	if ( _date.size() != 10 )
		return ( false );

	unsigned char i = 0 ;
	unsigned short int year = 0;
	unsigned char month = 0;
	unsigned char day = 0;

	for ( ; i < 4; ++i )
	{
		if (isdigit(_date[i]) == 0)
			return ( false );
		year = 10 * year + ( _date[i] - '0' );
	}

	++i;

	for ( ; i < ; ++i )
	{
		if (isdigit(_date[i]) == 0)
			return ( false );
		year = 10 * year + ( _date[i] - '0' );
	}
	for ( ; i < 4; ++i )
	{
		if (isdigit(_date[i]) == 0)
			return ( false );
		year = 10 * year + ( _date[i] - '0' );
	}
}

// Value
bool BitcoinExchange::isValidValue( void ) const
{

}
