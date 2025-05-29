/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:49:16 by ebonutto          #+#    #+#             */
/*   Updated: 2025/05/29 14:04:52 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

template <typename T>
class RPN : public std::stack<T>
{
public:
// Canonical form

// Default constructor
	RPN( void );
	
// Default destructor
	~RPN( void );

// Copy constructor
	RPN( const RPN &other );

// Copy assignment operator
	RPN &operator=( const RPN &other );

}

