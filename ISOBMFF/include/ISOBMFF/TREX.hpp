/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 DigiDNA - www.digidna.net
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
 * @header      SIDX.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_TREX_HPP
#define ISOBMFF_TREX_HPP

#include <memory>
#include <algorithm>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <ISOBMFF/DisplayableObject.hpp>
#include <ISOBMFF/DisplayableObjectContainer.hpp>
#include <string>
#include <vector>
#include <cstdint>

namespace ISOBMFF
{
    //https://www.cnblogs.com/gardenofhu/p/10040122.html
    class ReferenceObject;
    class ISOBMFF_EXPORT TREX: public FullBox //Movie Fragment Header Box
    {
        public:
            
            TREX();
            TREX( const TREX & o );
            TREX( TREX && o ) noexcept;
            virtual ~TREX() override;
            
            TREX & operator =( TREX o );
            
            void                                                        ReadData( Parser & parser, BinaryStream & stream ) override;
            std::vector< std::pair< std::string, std::string > >        GetDisplayableProperties() const override;
            
            uint32_t    GetTrack_ID()  const;     
            uint32_t    GetDefault_Sample_Description_Index()  const;
            uint32_t    GetDefault_Sample_Duration()  const;
            uint32_t    GetDefault_Sample_Size()  const;
            uint32_t    GetDefault_Sample_Flags()  const;

            void        SetTrack_ID(uint32_t value);
            void        SetDefault_Sample_Description_Index(uint32_t value);
            void        SetDefault_Sample_Duration(uint32_t value);
            void        SetDefault_Sample_Size(uint32_t value);
            void        SetDefault_Sample_Flags(uint32_t value);

            ISOBMFF_EXPORT friend void swap( TREX & o1, TREX & o2 );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_TREX_HPP */
