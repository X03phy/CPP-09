/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:18:37 by ebonutto          #+#    #+#             */
/*   Updated: 2025/05/29 12:18:38 by ebonutto         ###   ########.fr       */
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
std::string BitcoinExchange::getDate( void ) { return ( _date ); }
float BitcoinExchange::getValue( void ) { return ( _value ); }
float BitcoinExchange::getRate( void ) { return ( _rate ); }
bool BitcoinExchange::getIsPrintable( void ) { return ( _isPrintable ); }
std::string BitcoinExchange::getErrorMessage( void ) { return ( _errorMessage ); }

// Parsing
bool BitcoinExchange::checkInputLineDate( std::string &line, unsigned char &i )
{
	// Handle year-month-day ( yyyy-mm-dd )
	for ( ; i < 4; ++i ) // Handle year
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
	}

	if ( line[i++] != '-' ) // Handle first '-'
		return ( false );

	for ( ; i < 7; ++i ) // Handle month
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
	}

	if ( line[i++] != '-' ) // Handle second '-'
		return ( false );

	for ( ; i < 10; ++i ) // Handle day
	{
		if ( isdigit( line[i] ) == 0 )
			return ( false );
	}
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
			return (false);

		if ( line[i++] != ',' ) // Handle ','
			return ( false );

		float value;
		char *end;
		const char *exchange;

		exchange = line.c_str() + i; // Debut du mot
		value = std::strtof( exchange, &end );
		if ( end == exchange || *end != '\0')
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
		_errorMessage = "Error: too large a number.";
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
	dataInfile.seekg(0, std::ios::beg);   // Remet le curseur au début du fichier
	getline( dataInfile, data );          // skip la premiere ligne : "date,exchange_rate"

	while ( getline( dataInfile, data ) )
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
	if ( this->checkInputLine( line ) == false )
	{
		if ( _errorMessage == "None" )
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
