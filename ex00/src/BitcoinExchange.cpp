/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:18:37 by ebonutto          #+#    #+#             */
/*   Updated: 2025/06/03 13:44:01 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return ( *this );
}

// Member functions

// Getters
std::string BitcoinExchange::getDate( void ) const { return ( _date ); }
float BitcoinExchange::getValue( void ) const { return ( _value ); }
float BitcoinExchange::getRate( void ) const { return ( _rate ); }
bool BitcoinExchange::getIsPrintable( void ) const { return ( _isPrintable ); }
std::string BitcoinExchange::getErrorMessage( void ) const { return ( _errorMessage ); }

// Parsing
bool BitcoinExchange::is_leap_year( unsigned short int year )
{
	return ( ( year % 4 == 0 ) && ( ( year % 100 != 0 ) || ( year % 400 == 0 ) ) );
}

bool BitcoinExchange::is_date_valid( t_date &date )
{
	if ( date.year <= 0 || date.month <= 0 || date.day <= 0 )
		return ( false );
	if ( date.month > 12 || date.day > 31 )
		return ( false );
	if ( date.day == 31 && ( date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11 ) ) return ( false );
	if ( date.month == 2 ) {
		if ( date.day > 29 ) return ( false );
		if ( date.day == 29 && ( !is_leap_year( date.year ) ) ) return ( false );
	}
	return true;
}

bool BitcoinExchange::checkInputLineDate( std::string &line, unsigned char &i )
{
	t_date date = {0, 0, 0};
	// Handle year-month-day ( yyyy-mm-dd )
	for ( ; i < 4; ++i ) // Handle year
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
		date.year = 10 * date.year + ( line[i] - '0' );
	}

	if ( line[i++] != '-' ) // Handle first '-'
		return ( false );

	for ( ; i < 7; ++i ) // Handle month
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
		date.month = 10 * date.month + ( line[i] - '0' );
	}

	if ( line[i++] != '-' ) // Handle second '-'
		return ( false );

	for ( ; i < 10; ++i ) // Handle day
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
		date.day = 10 * date.day + ( line[i] - '0' );
	}

	if ( !is_date_valid( date ) )
		return ( false );

	return ( true );
}

bool BitcoinExchange::parseData( std::ifstream &dataInfile )
{
	std::string line;
	std::string date;
	std::string rate;
	unsigned char i;

	getline( dataInfile, line ); // obtient la premiere ligne : "date,exchange_rate"
	if ( line != "date,exchange_rate" )
		return ( false );

	while ( getline( dataInfile, line ) )
	{
		i = 0;
		if ( BitcoinExchange::checkInputLineDate( line, i ) == false )
			return ( false );

		if ( line[i++] != ',' ) // Handle ','
			return ( false );

		char *end;

		( void ) std::strtof( line.c_str() + i, &end );
		if ( end == line.c_str() + i || *end != '\0')
			return ( false );
	}

	return ( true );
}

bool BitcoinExchange::checkInputLine( std::string &line )
{
	unsigned char i = 0 ;

	if ( BitcoinExchange::checkInputLineDate( line, i ) == false )
		return (false);

	// Handle " | "
	if ( line[i++] != ' ' )
		return ( false );

	if ( line[i++] != '|' )
		return ( false );

	if ( line[i] != ' ' )
		return ( false );

	float value;
	char *end;
	const char *exchange;

	exchange = line.c_str() + i; // Debut du mot
	value = std::strtof( exchange, &end );
	if ( end == exchange || *end != '\0')
		return ( false );

	if ( value < 0 )
	{
		_errorMessage = "Error: not a positive number.";
		return ( false );
	}

	if ( value > 1000 )
	{
		_errorMessage = "Error: number too large.";
		return ( false );
	}

	std::istringstream ss( line );

	getline( ss, _date, ' ' );
	_value = value;

	return ( true );
}

// Data
void BitcoinExchange::extractRateFromData( std::ifstream &dataInfile )
{
	std::string data;
	std::string date;
	std::string rate;

	dataInfile.clear();                   // Clear EOF flag
	dataInfile.seekg( 0, std::ios::beg );   // Remet le curseur au début du fichier
	getline( dataInfile, data );          // skip la premiere ligne : "date,exchange_rate"

	getline( dataInfile, data ); // obtention de la premiere ligne de donnees
	std::istringstream ss( data );

	getline( ss, date, ',' ); // checker si la date est correcte 
	if ( _date < date )
	{
		_errorMessage = "No exchange was made that day or before";
		return ;
	}

	while ( getline( dataInfile, data ) )
	{
		std::istringstream ss( data );

		getline( ss, date, ',' );
		if ( _date < date )
		{
			this->_isPrintable = true;

			return ;
		}
		getline( ss, rate );
		_rate = std::strtof( rate.c_str(), NULL );
	}
	_errorMessage = "No exchange was made that day";
}

// Creation
void BitcoinExchange::createBitcoinExchange( std::ifstream &infile, std::ifstream &data )
{
	std::string line;

	getline( infile, line );
	if ( this->checkInputLine( line ) == false )
	{
		if ( _errorMessage == "None" )
			this->_errorMessage = "Error: bad input => " + line;
		return ;
	}
	this->extractRateFromData( data );

	return ;
}

std::list<BitcoinExchange> BitcoinExchange::createBitcoinExchanges( std::ifstream &infile, std::ifstream &data )
{
	std::list<BitcoinExchange> bitcoin_exchanges;

	while ( !infile.eof() )
	{
		BitcoinExchange bitcoin_exchange;

		bitcoin_exchange.createBitcoinExchange( infile, data ); // Tant qu'on reussi a creer des BitcoinExchange on continue => on n'est pas a la fin du fichier.
		bitcoin_exchanges.push_back( bitcoin_exchange );
	}

	return ( bitcoin_exchanges );
}

// Print
void BitcoinExchange::printBitcoinExchanges( std::list<BitcoinExchange> bitcoin_exchanges )
{
	float result;
	std::list<BitcoinExchange>::iterator it;

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
