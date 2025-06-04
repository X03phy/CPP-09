/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:28:22 by ebonutto          #+#    #+#             */
/*   Updated: 2025/06/04 14:16:23 by ebonutto         ###   ########.fr       */
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
	std::vector<int> getInsertPos( std::vector<int> &jacobsthalSequence, size_t n );

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
				pairs.push_back( std::make_pair( container[i + 1], container[i] ) );
		}

		// Tri recursif des plus grands elements de chaque paire
		Container largerElements;

		for ( std::vector< std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it )
		{
			largerElements.push_back( it->first );
		}

		if ( largerElements.size() > 1 )
			largerElements = mergeInsertionSort( largerElements );

		// Creation de la chaine pricinpale
		Container mainChain = largerElements;

		// On cree la liste de petits nombres
		Container pendantChain;

		for ( size_t i = 0; i < pairs.size(); i++ )
		{
			if ( pairs[i].first == mainChain[0] )
				mainChain.insert( mainChain.begin(), pairs[i].second );
			else
				pendantChain.push_back( pairs[i].second );
		}

		// On place les petits nombres de pendantChain dans mainChain
		if ( pendantChain.size() >= 1 )
		{
			int index;
			typename Container::iterator pos;
			std::vector<int> jacobsthalSequence = generateJacobsthalSequence( pendantChain.size() );
			std::vector<int> insertOrder = getInsertPos( jacobsthalSequence, pendantChain.size() );

			for ( size_t i = 0; i < pendantChain.size(); ++i )
			{
				index = insertOrder[i];
				pos = std::lower_bound( mainChain.begin(), mainChain.end(), pendantChain[index] );
				mainChain.insert( pos, pendantChain[index] );
			}
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

		// Trie une copie de `sequence`
		std::sort( sequence.begin(), sequence.end() );

		std::cout << std::endl;
		// Compare les deux séquences
		return ( sequence == sequenceSorted );
	}
};

// 4711 38852 4646 36206 48923 78168 12761 10359 51034 38800 73978 1055 32849 94016 49914 86754 79865 47526 65103 92247 3845 27954 6159 87190 68153 46489 44777 58225 9817 82158 7733 25858 85461 44040 24290
