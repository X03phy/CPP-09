/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:01:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/06/03 14:23:26 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main( int argc, char **argv )
{
	PmergeMe FJ;
	std::string input( argv[1] );
	std::istringstream ss( input );

	if ( argc != 2 )
	{
		std::cout << "Invalid number of aruments" << std::endl;
		return ( 1 );
	}

	if ( FJ.ParseInput( ss ) == false )
	{
		std::cerr << "Error: Invalid argument" <<std::endl;
		return ( 1 );
	}

	FJ.mergeInsertionSort();
	return ( 0 );
}
