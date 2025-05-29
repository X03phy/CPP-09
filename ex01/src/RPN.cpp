/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:12:23 by ebonutto          #+#    #+#             */
/*   Updated: 2025/05/29 16:34:27 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool RPN( std::string &entry, int &result )
{
	int a;
	int b;
	std::stack<int> _stack;
	std::string token;
	char *end;
	std::istringstream ss( entry );

	while ( ss >> token )
	{
		if ( token == "*" || token == "/" || token == "+" || token == "-" )
		{
			if ( _stack.size() < 2 )
				return ( false );
			a = _stack.top(); _stack.pop();
			b = _stack.top(); _stack.pop();
			if ( token == "*" )
				result = b * a;
			else if ( token == "/" )
				result = b / a;
			else if ( token == "+" )
				result = b + a;
			else
				result = b - a;
		}
		else
		{
			if ( token.size() > 2 )
				return ( false );
			result = std::strtol( token.c_str(), &end, 10 );
			if ( end == token.c_str() || *end != '\0' || result < 0 || result > 10 )
				return ( false );
		}
		_stack.push( result );
	}

	return ( true );
}
