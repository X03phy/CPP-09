#include <string> // string
#include <iostream> // cout, cerr, endl
#include <fstream> // ifstream, getline()
#include <vector> // vector
#include <sstream> // istringstream
#include <cstdlib> // strtof()

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
	std::string getDate( void );
	float getValue( void );
	float getRate( void );
	bool getIsPrintable( void );
	std::string getErrorMessage( void );

// Parsing
	static bool checkInputLineDate( std::string &line, unsigned char &i );
	static bool parseData( std::ifstream &infile );
	bool checkInputLine( std::string &line );

// Data
	void extractRateFromData( std::ifstream &dataInfile );

// Creation
	bool createBitcoinExchange( std::ifstream &infile, std::ifstream &data );
	static std::vector<BitcoinExchange> createBitcoinExchanges( std::ifstream &infile, std::ifstream &data );

// Print
	static void printBitcoinExchanges( std::vector<BitcoinExchange> bitcoin_exchanges );
};
