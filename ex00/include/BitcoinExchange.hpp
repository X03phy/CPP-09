/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:18:44 by ebonutto          #+#    #+#             */
/*   Updated: 2025/06/03 13:43:57 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string> // string
#include <iostream> // cout, cerr, endl
#include <fstream> // ifstream, getline()
#include <list> // list
#include <sstream> // istringstream
#include <cstdlib> // strtof()

typedef struct s_date
{
	unsigned short int year;
	unsigned char month;
	unsigned char day;
} t_date;

class BitcoinExchange
{
private:
	std::string _date;
	float _value;
	float _rate;
	bool _isPrintable;
	std::string _errorMessage;

public:
// Canonical form

// Default constructor and Destructor
	BitcoinExchange( void );
	~BitcoinExchange( void );

// Copy constructor
	BitcoinExchange( const BitcoinExchange &other );

// Copy assignment operator
	BitcoinExchange &operator=( const BitcoinExchange &other );

// Member functions

// Getters
	std::string getDate( void ) const;
	float getValue( void ) const;
	float getRate( void ) const;
	bool getIsPrintable( void ) const;
	std::string getErrorMessage( void ) const;

// Parsing
	static bool is_leap_year( unsigned short int year );
	static bool is_date_valid( t_date &date );
	static bool checkInputLineDate( std::string &line, unsigned char &i );
	static bool parseData( std::ifstream &infile );
	bool checkInputLine( std::string &line );

// Data
	void extractRateFromData( std::ifstream &dataInfile );

// Creation
	void createBitcoinExchange( std::ifstream &infile, std::ifstream &data );
	static std::list<BitcoinExchange> createBitcoinExchanges( std::ifstream &infile, std::ifstream &data );

// Print
	static void printBitcoinExchanges( std::list<BitcoinExchange> bitcoin_exchanges );
};
