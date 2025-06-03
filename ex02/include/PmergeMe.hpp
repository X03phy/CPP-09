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
#include <cstdlib> // strtol(), exit()
#include <climits> // INT_MIN, INT_MAX
#include <algorithm> // swap(), lower_bound()
#include <vector> // vector, iterator
#include <utility> // pair
#include <deque> // deque

class PmergeMe
{
private:
	std::vector<int> _vectorSequence;
	std::deque<int> _dequeSequence;
	std::vector<int> _vectorSequenceSorted;
	std::deque<int> _dequeSequenceSorted;

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
	bool ParseInput( char **argv );
	void MergeThat( void );
	static std::vector<int> generateJacobsthalSequence( int n );
	static std::vector<int> mergeInsertionSort( std::vector<int> &container );
	// std::deque<int> mergeInsertionSort( std::deque<int> &container );
	bool checker( void );

};
