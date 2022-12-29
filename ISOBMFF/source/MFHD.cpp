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
 * @file        MFHD.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/MFHD.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/Utils.hpp>

namespace ISOBMFF
{
    class MFHD::IMPL
    {
    public:

        IMPL();
        IMPL(const IMPL& o);
        ~IMPL();

        uint32_t                 _sequence_number;

    };
    
    MFHD::MFHD():
        FullBox( "mfhd" ),
        impl( std::make_unique< IMPL >() )
    {}
    
    MFHD::MFHD( const MFHD & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    MFHD::MFHD( MFHD && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }
    
    MFHD::~MFHD()
    {}
    
    MFHD & MFHD::operator =( MFHD o )
    {
        Box::operator=( o );
        swap( *( this ), o );
        
        return *( this );
    }
    
    void swap( MFHD & o1, MFHD & o2 )
    {
        using std::swap;
        
        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    
    void MFHD::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData(parser, stream);

        this->SetSequence_Number( stream.ReadBigEndianUInt32() );     
    }

    uint32_t MFHD::GetSequence_Number()  const
    {
        return this->impl->_sequence_number;
    }

    void MFHD::SetSequence_Number(uint32_t value)
    {
        this->impl->_sequence_number = value;
    }

    std::vector< std::pair< std::string, std::string > > MFHD::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Sequence Number",               std::to_string(this->GetSequence_Number()) } );
        
        return props;
    }    
    
    MFHD::IMPL::IMPL()
    {}

    MFHD::IMPL::IMPL( const IMPL & o ):
        _sequence_number( o._sequence_number)
    {}

    MFHD::IMPL::~IMPL()
    {}
}
