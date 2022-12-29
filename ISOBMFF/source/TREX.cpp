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
 * @file        TREX.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/TREX.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/Utils.hpp>

namespace ISOBMFF
{
    class TREX::IMPL
    {
    public:

        IMPL();
        IMPL(const IMPL& o);
        ~IMPL();

        uint32_t    _track_ID;
        uint32_t    _default_sample_description_index;
        uint32_t    _default_sample_duration;
        uint32_t    _default_sample_size;
        uint32_t    _default_sample_flags;

    };
    
    TREX::TREX():
        FullBox( "trex" ),
        impl( std::make_unique< IMPL >() )
    {}
    
    TREX::TREX( const TREX & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    TREX::TREX( TREX && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }
    
    TREX::~TREX()
    {}
    
    TREX & TREX::operator =( TREX o )
    {
        Box::operator=( o );
        swap( *( this ), o );
        
        return *( this );
    }
    
    void swap( TREX & o1, TREX & o2 )
    {
        using std::swap;
        
        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    
    void TREX::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData(parser, stream);

        this->SetTrack_ID( stream.ReadBigEndianUInt32() );
        this->SetDefault_Sample_Description_Index(stream.ReadBigEndianUInt32());
        this->SetDefault_Sample_Duration(stream.ReadBigEndianUInt32());
        this->SetDefault_Sample_Size(stream.ReadBigEndianUInt32());
        this->SetDefault_Sample_Flags(stream.ReadBigEndianUInt32());
    }

    uint32_t    TREX::GetTrack_ID()  const
    {
        return this->impl->_track_ID;
    }
    uint32_t    TREX::GetDefault_Sample_Description_Index()  const
    {
        return this->impl->_default_sample_description_index;
    }
    uint32_t    TREX::GetDefault_Sample_Duration()  const
    {
        return this->impl->_default_sample_duration;
    }
    uint32_t    TREX::GetDefault_Sample_Size()  const
    {
        return this->impl->_default_sample_size;
    }
    uint32_t    TREX::GetDefault_Sample_Flags()  const
    {
        return this->impl->_default_sample_flags;
    }

    void        TREX::SetTrack_ID(uint32_t value)
    {
        this->impl->_track_ID = value;
    }
    void        TREX::SetDefault_Sample_Description_Index(uint32_t value)
    {
        this->impl->_default_sample_description_index = value;
    }
    void        TREX::SetDefault_Sample_Duration(uint32_t value)
    {
        this->impl->_default_sample_duration = value;
    }
    void        TREX::SetDefault_Sample_Size(uint32_t value)
    {
        this->impl->_default_sample_size = value;
    }
    void        TREX::SetDefault_Sample_Flags(uint32_t value)
    {
        this->impl->_default_sample_flags = value;
    }


    std::vector< std::pair< std::string, std::string > > TREX::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Track ID",                  std::to_string(this->GetTrack_ID()) } );
        props.push_back( { "Default Sample Description Index",  std::to_string(this->GetDefault_Sample_Description_Index()) } );
        props.push_back( { "Default Sample Duration",   std::to_string(this->GetDefault_Sample_Duration()) } );
        props.push_back( { "Default Sample Size",       std::to_string(this->GetDefault_Sample_Size()) } );
        props.push_back( { "Default Sample Flags",      std::to_string(this->GetDefault_Sample_Flags()) } );
        
        return props;
    }    
    
    TREX::IMPL::IMPL()
    {}

    TREX::IMPL::IMPL( const IMPL & o ):
        _track_ID( o._track_ID),
        _default_sample_description_index(o._default_sample_description_index),
        _default_sample_duration(o._default_sample_duration),
        _default_sample_size(o._default_sample_size),
        _default_sample_flags(o._default_sample_flags)
    {}

    TREX::IMPL::~IMPL()
    {}
}
