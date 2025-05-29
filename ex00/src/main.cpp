#include "BitcoinExchange.hpp"

int main( int argc, char **argv )
{
	if ( argc != 3 )
	{
		std::cerr << "Error: invalid number of arguments." << std::endl;
		return (1);
	}

	std::ifstream infile( argv[1] );
	if ( !infile.is_open() )
	{
		std::cerr << "Error: " << argv[1] << " does not exist." << std::endl;
		return (1);
	}

	std::ifstream dataInfile( argv[2] );
	if ( !dataInfile.is_open() )
	{
		std::cerr << "Error: " << argv[2] << " does not exist." << std::endl;
		infile.close();
		return (1);
	}

	if ( BitcoinExchange::parseData( dataInfile ) == false )
	{
		std::cerr << "Error: the data is incorrectly formatted" << std::endl;
		infile.close();
		dataInfile.close();
		return (1);
	}

	std::vector<BitcoinExchange> bitcoin_exchanges;

	bitcoin_exchanges = BitcoinExchange::createBitcoinExchanges( infile, dataInfile );
	BitcoinExchange::printBitcoinExchanges( bitcoin_exchanges );

	infile.close();
	dataInfile.close();
	return (0);
}
