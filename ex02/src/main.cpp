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
	if ( argc < 2 )
	{
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		return ( 1 );
	}

	PmergeMe FJ;

	if ( FJ.ParseInput( argv ) == false )
	{
		std::cerr << "Error: Invalid input" << std::endl;
		return ( 1 );
	}

	FJ.MergeThat();

	return ( 0 );
}
