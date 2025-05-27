#include <string> // string
#include <iostream> // cout, cerr, endl
#include <fstream> // ifstream, getline()
#include <vector> // vector

class BitcoinExchange
{
private:
	std::string _date;
	float _value;
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

// Setters
	bool setBitcoinExchange( std::ifstream &infile );
	static std::vector<BitcoinExchange> setBitcoinExchanges( std::ifstream &infile );

// Getters
	std::string getDate( void ) const;
	float getValue( void ) const;

// Date
	void checkDate( void );

// Value
	void checkValue( void );
};
