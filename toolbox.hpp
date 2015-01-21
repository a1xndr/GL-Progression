/*
 * toolbox.hpp
 *
 *  Created on: Jan 20, 2015
 *      Author: alxndr
 */

#ifndef TOOLBOX_HPP_
#define TOOLBOX_HPP_

#include <sstream>

#define tostr( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


#endif /* TOOLBOX_HPP_ */
