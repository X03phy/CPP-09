#include <string> // string
#include <iostream> // cout, cerr, endl
#include <fstream> // ifstream, getline()

class BitcoinExchange
{
private:
	std::string _date;
	float _value;

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
	void setClass( std::ifstream &infile );
	void setDate( std::string &date );
	void setValue( float &value );
	void setIsPrintable( bool &isPrintable );

// Getters
	std::string getDate( void ) const;
	float getValue( void ) const;

// Date
	bool isValidDate( void ) const;

// Value
	bool isValidValue( void ) const;


};
