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
 * @file        TFHD.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/TFHD.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/Utils.hpp>

#define MOV_TFHD_BASE_DATA_OFFSET       0x01
#define MOV_TFHD_STSD_ID                0x02
#define MOV_TFHD_DEFAULT_DURATION       0x08
#define MOV_TFHD_DEFAULT_SIZE           0x10
#define MOV_TFHD_DEFAULT_FLAGS          0x20
#define MOV_TFHD_DURATION_IS_EMPTY  0x010000
#define MOV_TFHD_DEFAULT_BASE_IS_MOOF 0x020000

namespace ISOBMFF
{
    class TFHD::IMPL
    {
    public:

        IMPL();
        IMPL(const IMPL& o);
        ~IMPL();

        uint32_t    _track_ID;
        uint64_t    _base_data_offset;
        uint32_t    _sample_description_index;
        uint32_t    _default_sample_duration;
        uint32_t    _default_sample_size;
        uint32_t    _default_sample_flags;

    };
    
    TFHD::TFHD():
        FullBox( "tfhd" ),
        impl( std::make_unique< IMPL >() )
    {}
    
    TFHD::TFHD( const TFHD & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    TFHD::TFHD( TFHD && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }
    
    TFHD::~TFHD()
    {}
    
    TFHD & TFHD::operator =( TFHD o )
    {
        Box::operator=( o );
        swap( *( this ), o );
        
        return *( this );
    }
    
    void swap( TFHD & o1, TFHD & o2 )
    {
        using std::swap;
        
        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }



    void TFHD::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData(parser, stream);

        this->SetTrack_ID( stream.ReadBigEndianUInt32() );
        auto flags = this->GetFlags();
        if (flags & MOV_TFHD_BASE_DATA_OFFSET)
            this->SetBase_Data_Offset(stream.ReadBigEndianUInt64());
        else
            this->SetBase_Data_Offset(0);
        if (flags & MOV_TFHD_STSD_ID)
            this->SetSample_Description_Index(stream.ReadBigEndianUInt32());
        else
            this->SetSample_Description_Index(0);
        if (flags & MOV_TFHD_DEFAULT_DURATION)
            this->SetDefault_Sample_Duration(stream.ReadBigEndianUInt32());
        else
            this->SetDefault_Sample_Duration(0);
        if (flags & MOV_TFHD_DEFAULT_SIZE)
            this->SetDefault_Sample_Size(stream.ReadBigEndianUInt32());
        else
            this->SetDefault_Sample_Size(0);
        if (flags & MOV_TFHD_DEFAULT_FLAGS)
            this->SetDefault_Sample_Flags(stream.ReadBigEndianUInt32());
        else
            this->SetDefault_Sample_Flags(0);
    }

    uint32_t    TFHD::GetTrack_ID()  const
    {
        return this->impl->_track_ID;
    }
    uint64_t    TFHD::GetBase_Data_Offset()  const
    {
        return this->impl->_base_data_offset;
    }
    uint32_t    TFHD::GetSample_Description_Index()  const
    {
        return this->impl->_sample_description_index;
    }
    uint32_t    TFHD::GetDefault_Sample_Duration()  const
    {
        return this->impl->_default_sample_duration;
    }
    uint32_t    TFHD::GetDefault_Sample_Size()  const
    {
        return this->impl->_default_sample_size;
    }
    uint32_t    TFHD::GetDefault_Sample_Flags()  const
    {
        return this->impl->_default_sample_flags;
    }

    void        TFHD::SetTrack_ID(uint32_t value)
    {
        this->impl->_track_ID = value;
    }
    void        TFHD::SetBase_Data_Offset(uint64_t value)
    {
        this->impl->_base_data_offset = value;
    }
    void        TFHD::SetSample_Description_Index(uint32_t value)
    {
        this->impl->_sample_description_index = value;
    }
    void        TFHD::SetDefault_Sample_Duration(uint32_t value)
    {
        this->impl->_default_sample_duration = value;
    }
    void        TFHD::SetDefault_Sample_Size(uint32_t value)
    {
        this->impl->_default_sample_size = value;
    }
    void        TFHD::SetDefault_Sample_Flags(uint32_t value)
    {
        this->impl->_default_sample_flags = value;
    }


    std::vector< std::pair< std::string, std::string > > TFHD::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Track ID",                  std::to_string(this->GetTrack_ID()) } );
        props.push_back( { "Base Data Offset",          std::to_string(this->GetBase_Data_Offset()) } );
        props.push_back( { "Sample Description Index",  std::to_string(this->GetSample_Description_Index()) } );
        props.push_back( { "Default Sample Duration",   std::to_string(this->GetDefault_Sample_Duration()) } );
        props.push_back( { "Default Sample Size",       std::to_string(this->GetDefault_Sample_Size()) } );
        props.push_back( { "Default Sample Flags",      std::to_string(this->GetDefault_Sample_Flags()) } );
        
        return props;
    }    
    
    TFHD::IMPL::IMPL()
    {}

    TFHD::IMPL::IMPL( const IMPL & o ):
        _track_ID( o._track_ID),
        _base_data_offset(o._base_data_offset),
        _sample_description_index(o._sample_description_index),
        _default_sample_duration(o._default_sample_duration),
        _default_sample_size(o._default_sample_size),
        _default_sample_flags(o._default_sample_flags)
    {}

    TFHD::IMPL::~IMPL()
    {}
}
