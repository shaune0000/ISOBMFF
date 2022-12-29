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
 * @file        SIDX.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/SIDX.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/Utils.hpp>

namespace ISOBMFF
{
    class SIDX::IMPL
    {
    public:

        IMPL();
        IMPL(const IMPL& o);
        ~IMPL();

        int32_t                 _reference_id;
        int32_t                 _timescale;
        int64_t                 _earliest_presentation_time;
        int64_t                 _first_offset;
        uint16_t                _reference_count;

        std::vector< std::shared_ptr< SIDX::ReferenceObject > > _referenceObjects;

    };
    
    SIDX::SIDX():
        FullBox( "sidx" ),
        impl( std::make_unique< IMPL >() )
    {}
    
    SIDX::SIDX( const SIDX & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    SIDX::SIDX( SIDX && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }
    
    SIDX::~SIDX()
    {}
    
    SIDX & SIDX::operator =( SIDX o )
    {
        Box::operator=( o );
        swap( *( this ), o );
        
        return *( this );
    }
    
    void swap( SIDX & o1, SIDX & o2 )
    {
        using std::swap;
        
        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void SIDX::WriteDescription(std::ostream& os, std::size_t indentLevel) const
    {
        FullBox::WriteDescription(os, indentLevel);
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }
    
    void SIDX::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData(parser, stream);

        this->SetReference_ID( stream.ReadBigEndianUInt32() );
        this->SetTimeScale( stream.ReadBigEndianUInt32() );

        if (this->GetVersion() == 0)
        {
            this->SetEarliest_Presentation_Time(stream.ReadBigEndianUInt32());
            this->SetFirst_Offset(stream.ReadBigEndianUInt32());
        }
        else
        {
            this->SetEarliest_Presentation_Time(stream.ReadBigEndianUInt64());
            this->SetFirst_Offset(stream.ReadBigEndianUInt64());
        }

        auto reserved = stream.ReadBigEndianUInt16();
        auto reference_count = stream.ReadBigEndianUInt16();
        this->impl->_reference_count = reference_count;

        for (int i = 0; i < reference_count; i++)
        {
            this->AddReferenceObject(std::make_shared< ReferenceObject >(stream));
        }       
    }

    std::vector< std::shared_ptr< SIDX::ReferenceObject > > SIDX::GetReferenceObjects() const
    {
        return this->impl->_referenceObjects;
    }

    void SIDX::AddReferenceObject(std::shared_ptr< ReferenceObject > array)
    {
        this->impl->_referenceObjects.push_back(array);
    }
    
    std::vector< std::shared_ptr< DisplayableObject > > SIDX::GetDisplayableObjects() const
    {
        auto v(this->GetReferenceObjects());

        return std::vector< std::shared_ptr< DisplayableObject > >(v.begin(), v.end());
    }

    std::vector< std::pair< std::string, std::string > > SIDX::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );
        
        props.push_back( { "Reference ID",                  std::to_string(this->GetReference_ID()) } );
        props.push_back( { "Time Scale",                    std::to_string( this->GetTimeScale()) } );
        props.push_back( { "Earliest Presentation Time",    std::to_string( this->GetEarliest_Presentation_Time()) } );
        props.push_back( { "First Offset",                  std::to_string(this->GetFirst_Offset()) } );
        props.push_back( { "Reference Count",               std::to_string(this->impl->_reference_count) });

        /*
        auto v(this->GetReferenceObjects());
        auto v_g = v.begin();
        while (v_g != v.end())
        {
            auto ref_props(v_g->get()->GetDisplayableProperties());
            props.insert(props.end(), ref_props.begin(), ref_props.end());

            v_g++;
        }
        */
        
        return props;
    }    

    uint32_t SIDX::GetReference_ID() const
    {
        return this->impl->_reference_id;
    }
    
    uint32_t SIDX::GetTimeScale() const
    {
        return this->impl->_timescale;
    }
    
    uint64_t SIDX::GetEarliest_Presentation_Time() const
    {
        return this->impl->_earliest_presentation_time;
    }
    
    uint64_t SIDX::GetFirst_Offset( ) const
    {
        return this->impl->_first_offset;
    }   

    void SIDX::SetReference_ID( uint32_t value )
    {
        this->impl->_reference_id = value;
    }
    
    void SIDX::SetTimeScale( uint32_t value )
    {
        this->impl->_timescale = value;
    }
    
    void SIDX::SetEarliest_Presentation_Time( uint64_t value )
    {
        this->impl->_earliest_presentation_time = value;
    }

    void SIDX::SetFirst_Offset( uint64_t value )
    {
        this->impl->_first_offset = value;
    }
    
    SIDX::IMPL::IMPL()
    {}

    SIDX::IMPL::IMPL( const IMPL & o ):
        _reference_id( o._reference_id),
        _timescale( o._timescale),
        _first_offset( o._first_offset),
        _earliest_presentation_time( o._earliest_presentation_time )
    {}

    SIDX::IMPL::~IMPL()
    {}
}
