/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:53:06 by ebonutto          #+#    #+#             */
/*   Updated: 2025/05/29 15:32:45 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main( int argc, char **argv )
{
	if ( argc != 2 )
	{
		std::cerr << "Error" << std::endl;
		return ( 1 );
	}

	int result = 0;
	std::string entry( argv[1] );
	if ( RPN( entry, result ) == false )
	{
		std::cerr << "Error" << std::endl;
		return ( 1 );
	}
	std::cout << result << std::endl;

	return ( 0 );
}