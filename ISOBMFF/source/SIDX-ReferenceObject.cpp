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
 * @file        SIDX-ReferenceObject.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/SIDX.hpp>

namespace ISOBMFF
{
    class SIDX::ReferenceObject::IMPL
    {
        public:
            
            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();            

            bool        _referenceType;
            uint32_t    _reference_Size;
            uint32_t    _subsegment_Duration;
            bool        _starts_with_SAP;     //whether the referenced subsegments start with a SAP
            uint32_t    _SAP_Type;            //SAP type as specified in Annex I, or the value 0.
            uint32_t    _SAP_delta_time;      //indicates TSAP of the first SAP, in decoding order, in the referenced subsegment for the reference stream
    };
    
    SIDX::ReferenceObject::ReferenceObject():
        impl( std::make_unique< IMPL >() )
    {}
    
    SIDX::ReferenceObject::ReferenceObject( BinaryStream & stream ):
        impl( std::make_unique< IMPL >() )
    {
        auto vf = stream.ReadBigEndianUInt32();

        this->SetReferenceType(static_cast<bool>(vf >> 31));
        this->SetReference_Size(static_cast<uint32_t>(vf & 0x7fffffff));

        this->SetSubsegment_Duration(stream.ReadBigEndianUInt32());

        vf = stream.ReadBigEndianUInt32();
        this->SetStarts_with_SAP(static_cast<bool>(vf >> 31));
        
        this->SetSAP_Type(static_cast<uint32_t>(vf >> 28 & 0x0fff));
        this->SetSAP_delta_time(static_cast<uint32_t>(vf & 0x0fffffff));
    }
    
    SIDX::ReferenceObject::ReferenceObject( const ReferenceObject & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    SIDX::ReferenceObject::ReferenceObject( ReferenceObject && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }
    
    SIDX::ReferenceObject::~ReferenceObject()
    {}
    
    SIDX::ReferenceObject & SIDX::ReferenceObject::operator =( SIDX::ReferenceObject o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    void swap( SIDX::ReferenceObject & o1, SIDX::ReferenceObject & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    std::string SIDX::ReferenceObject::GetName() const
    {
        return "Reference";
    }
    
    void SIDX::ReferenceObject::SetReferenceType(bool value)
    {
        this->impl->_referenceType = value;
    }

    void SIDX::ReferenceObject::SetReference_Size(uint32_t value)
    {
        this->impl->_reference_Size = value;
    }

    void SIDX::ReferenceObject::SetSubsegment_Duration(uint32_t value)
    {
        this->impl->_subsegment_Duration = value;
    }

    void SIDX::ReferenceObject::SetStarts_with_SAP(bool value)
    {
        this->impl->_starts_with_SAP = value;
    }

    void SIDX::ReferenceObject::SetSAP_Type(uint32_t value)
    {
        this->impl->_SAP_Type = value;
    }

    void SIDX::ReferenceObject::SetSAP_delta_time(uint32_t value)
    {
        this->impl->_SAP_delta_time = value;
    }

    bool        SIDX::ReferenceObject::GetReferenceType() const
    {
        return this->impl->_referenceType;
    }

    uint32_t    SIDX::ReferenceObject::GetReference_Size() const
    {
        return this->impl->_reference_Size;
    }

    uint32_t    SIDX::ReferenceObject::GetSubsegment_Duration() const
    {
        return this->impl->_subsegment_Duration;
    }

    bool        SIDX::ReferenceObject::GetStarts_with_SAP() const
    {
        return this->impl->_starts_with_SAP;
    }

    uint32_t    SIDX::ReferenceObject::GetSAP_Type() const
    {
        return this->impl->_SAP_Type;
    }

    uint32_t    SIDX::ReferenceObject::GetSAP_delta_time() const
    {
        return this->impl->_SAP_delta_time;
    }
    
    std::vector< std::pair< std::string, std::string > > SIDX::ReferenceObject::GetDisplayableProperties() const
    {
        return
        {
            { "Reference Type",         std::to_string( this->GetReferenceType() ) },
            { "Reference Size",         std::to_string(this->GetReference_Size()) },
            { "Subsegment Duration",    std::to_string(this->GetSubsegment_Duration()) },
            { "Starts with SAP",        std::to_string(this->GetStarts_with_SAP()) },
            { "SAP Type",               std::to_string(this->GetSAP_Type()) },
            { "SAP delta time",         std::to_string(this->GetSAP_delta_time()) },
        };
    }
    
    SIDX::ReferenceObject::IMPL::IMPL()
    {}

    SIDX::ReferenceObject::IMPL::IMPL( const IMPL & o ) : 
        _referenceType( o._referenceType),
        _reference_Size( o._reference_Size ),
        _subsegment_Duration( o._subsegment_Duration ),
        _starts_with_SAP( o._starts_with_SAP ),
        _SAP_Type( o._SAP_Type ),
        _SAP_delta_time( o._SAP_delta_time )
    {}

    SIDX::ReferenceObject::IMPL::~IMPL()
    {}
}

