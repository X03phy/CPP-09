#include "BitcoinExchange.hpp"

int main( int argc, char **argv )
{
	if ( argc != 3 )
	{
		std::cerr << "Error: invalid number of arguments." << std::endl;
		return (1);
	}
	std::ifstream infile( argv[1] );
	std::ifstream data( argv[2] );

	std::vector<BitcoinExchange> bitcoin_exchanges;

	bitcoin_exchanges = BitcoinExchange::createBitcoinExchanges( infile, data );
	// BitcoinExchange::printBitcoinExchanges( bitcoin_exchanges );
	return (0);
}
