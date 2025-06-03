/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:28:22 by ebonutto          #+#    #+#             */
/*   Updated: 2025/06/03 18:11:23 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string> // string
#include <iostream> // cout, cerr, endl
#include <cstddef> // size_t
#include <sstream> // istringstream
#include <cstdlib> // strtol()
#include <climits> // INT_MIN, INT_MAX
#include <algorithm> // swap(), lower_bound()
#include <vector> // vector, iterator
#include <utility> // pair
#include <deque> // deque

class PmergeMe
{
private:
	std::vector<int> _nbSequence;

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
	bool ParseInput( std::istringstream &ss );
	void mergeInsertionSort( void );

};
