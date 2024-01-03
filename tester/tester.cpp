/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:56:18 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/12/25 22:35:51 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tester.hpp"

bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool)
{
	fs << "\nBool result : \n";
	fs << " - STL : " << (stl_bool ? "true" : "false") << std::endl;
	fs << " - FT  : " << (ft_bool ? "true" : "false") << std::endl;

	return (stl_bool == ft_bool);
}
