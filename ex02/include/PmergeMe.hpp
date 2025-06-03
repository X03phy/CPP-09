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
#include <sys/time.h>// gettimeofday()

class PmergeMe
{
private:
	std::vector<int> _vectorSequence;
	std::deque<int> _dequeSequence;
	std::vector<int> _vectorSequenceSorted;
	std::deque<int> _dequeSequenceSorted;
	long _vectorTime;
	long _dequeTime;

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

	template <typename Container>
	Container mergeInsertionSort( Container container )
	{
		// Cas de base
		size_t n = container.size();

		if ( n <= 1 )
			return ( container );
		if ( n == 2 )
		{
			if ( container[0] > container[1] )
				std::swap( container[0], container[1] );
			return ( container );
		}

		// Former des pairs: grand - petit
		std::vector< std::pair<int, int> > pairs;
		bool hasOdd = ( n & 1 );
		int oddElement;

		if ( hasOdd )
		{
			oddElement = container.back();
			--n;
		}
		for ( size_t i = 0; i < n; i += 2 )
		{
			if ( container[i] > container[i + 1] )
				pairs.push_back( std::make_pair( container[i], container[i + 1] ) );
			else
				pairs.push_back( std::make_pair(container[i + 1], container[i]) );
		}

		// Tri recursif des plus grands elements de chaque paire
		Container largerElements;
		Container smallerElements;

		for ( std::vector< std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it )
		{
			largerElements.push_back( it->first );
			smallerElements.push_back( it->second );
		}

		if ( largerElements.size() > 1 )
			largerElements = mergeInsertionSort( largerElements );

		// Creation de la chaine pricinpale
		Container mainChain = largerElements;

		if ( !smallerElements.empty() )
		{
			for ( std::vector< std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it )
			{
				if ( it->first == mainChain[0] )
				{
					mainChain.insert( mainChain.begin(), it->second );
					break;
				}
			}
		}

		// On cree la liste de petits nombres
		Container pendantChain;

		for ( size_t i = 2; i < mainChain.size(); ++i )
		{
			for ( size_t j = 0; j < pairs.size(); ++j )
			{
				if ( pairs[j].first == mainChain[i] )
				{
					pendantChain.push_back( pairs[j].second );
					break;
				}
			}
		}

		// On place les petits nombres
		std::vector<int> jacobsthalSequence = generateJacobsthalSequence( pendantChain.size() );
		int index;
		int value;
		typename Container::iterator pos;

		for (size_t i = 0; i < jacobsthalSequence.size(); ++i)
		{
			index = jacobsthalSequence[i] - 1; // car la séquence est en base 1
			if ( static_cast<size_t>(index) >= pendantChain.size() )
				continue; // protection au cas où

			value = pendantChain[index];
			pos = std::lower_bound(mainChain.begin(), mainChain.end(), value);
			mainChain.insert(pos, value);
		}

		// Gerer le dernier nb
		if ( hasOdd )
		{
			typename Container::iterator pos = std::lower_bound( mainChain.begin(), mainChain.end(), oddElement );
			mainChain.insert( pos, oddElement );
		}

		return ( mainChain );
	}

	template <typename Container>
	bool checker( Container sequence, Container sequenceSorted )
	{
		if ( sequence.size() != sequenceSorted.size() )
			return ( false );

		for ( size_t i = 0; ( i + 1 ) < sequenceSorted.size(); ++i )
			if ( sequenceSorted[i] > sequenceSorted[i + 1] )
				return ( false );

		return ( true );
	}
};
