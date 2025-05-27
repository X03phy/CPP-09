#include "BitcoinExchange.hpp"

int main( int argc, char **argv )
{
	if ( argc == 2 )
	{
		std::ifstream infile( argv[1] );

		std::vector<BitcoinExchange> bitcoin_exchanges;

		bitcoin_exchanges = BitcoinExchange::setBitcoinExchanges( infile );
		std::vector<BitcoinExchange>::iterator it;
		for (it = bitcoin_exchanges.begin(); it != bitcoin_exchanges.end(); ++it)
			std::cout << (*it).getDate() << std::endl;
		return (0);
	}
	std::cerr << "Error: could not open file." << std::endl;
	return (1);
}
