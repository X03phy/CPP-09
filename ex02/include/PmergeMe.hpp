/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:28:22 by ebonutto          #+#    #+#             */
/*   Updated: 2025/05/29 16:28:23 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string> // string
#include <iostream> // cout, cerr, endl
#include <cstddef> // size_t
#include <sstream> // istringstream
#include <cstdlib> // strtod()
#include <algorithm> // swap()
#include <vector> // vector, iterator
#include <utility> // pair
#include <deque> // deque

class PmergeMe
{
private:

public:
// Default constructor
	PmergeMe( void );

// Destructor
	~PmergeMe( void );

// Copy constructor
	PmergeMe( const PmergeMe &other );

// Copy assignment operator
	PmergeMe &operator=( const PmergeMe &other );

// Member functions
	template <typename T>
	static void mergeInsertionSort( T &container )
	{
		size_t n;
		std::vector< std::pair< int, int > > pairs;
		int a;
		int b;

		n = container.size();

		if ( n <= 1 )
			return ;

		for ( size_t i = 0; ( i + 1 ) < n; i += 2 )
		{
			a = container[i];
			b = container[i + 1];
			if ( b < a )
				std::swap( a, b );
			pairs.push_back( make_pair( a, b ) );
			std::cout << "hello" << " " << 4 << std::endl;
		}
	}
};
