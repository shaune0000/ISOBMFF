/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      DisplayableObject.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_DISPLAYABLE_OBJECT_HPP
#define ISOBMFF_DISPLAYABLE_OBJECT_HPP

#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/Utils.hpp>
#include <ostream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT DisplayableObject
    {
        public:
            
            virtual ~DisplayableObject( void );
            
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const = 0;
            virtual std::string                                          GetName( void )                  const = 0;
            
            virtual void        WriteDescription( std::ostream & os, std::size_t indentLevel ) const;
            virtual std::string ToString( void )                                               const;
            
            friend std::ostream & operator << ( std::ostream & os, const DisplayableObject & o );
    };
}

#endif /* ISOBMFF_DISPLAYABLE_OBJECT_HPP */


