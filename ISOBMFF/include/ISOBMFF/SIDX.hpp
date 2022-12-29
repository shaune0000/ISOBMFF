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

#ifndef ISOBMFF_SIDX_HPP
#define ISOBMFF_SIDX_HPP

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
    //https://www.cnblogs.com/gardenofhu/p/10044853.html
    class ReferenceObject;
    class ISOBMFF_EXPORT SIDX: public FullBox, public DisplayableObjectContainer //Segment Index Box
    {
        public:
            
            SIDX();
            SIDX( const SIDX & o );
            SIDX( SIDX && o ) noexcept;
            virtual ~SIDX() override;
            
            SIDX & operator =( SIDX o );
            
            void                                                        ReadData( Parser & parser, BinaryStream & stream ) override;
            void                                                        WriteDescription(std::ostream& os, std::size_t indentLevel) const override;
            std::vector< std::pair< std::string, std::string > >        GetDisplayableProperties() const override;
            virtual std::vector< std::shared_ptr< DisplayableObject > > GetDisplayableObjects()    const override;
            
            uint32_t     GetReference_ID()  const;
            uint32_t     GetTimeScale()     const;
            uint64_t     GetEarliest_Presentation_Time()   const;
            uint64_t     GetFirst_Offset() const;
            
            void SetReference_ID(uint32_t value );
            void SetTimeScale(uint32_t value);
            void SetEarliest_Presentation_Time(uint64_t value);
            void SetFirst_Offset(uint64_t value);

            class ISOBMFF_EXPORT ReferenceObject : public DisplayableObject
            {
            public:

                ReferenceObject();
                ReferenceObject(BinaryStream& stream);
                ReferenceObject(const ReferenceObject& o);
                ReferenceObject(ReferenceObject&& o) noexcept;
                virtual ~ReferenceObject() override;

                std::string GetName() const;

                ReferenceObject& operator =(ReferenceObject o);

                bool        GetReferenceType() const;
                uint32_t    GetReference_Size() const;
                uint32_t    GetSubsegment_Duration() const;
                bool        GetStarts_with_SAP() const;     //whether the referenced subsegments start with a SAP
                uint32_t    GetSAP_Type() const;            //SAP type as specified in Annex I, or the value 0.
                uint32_t    GetSAP_delta_time() const;      //indicates TSAP of the first SAP, in decoding order, in the referenced subsegment for the reference stream

                void        SetReferenceType(bool value);
                void        SetReference_Size(uint32_t value);
                void        SetSubsegment_Duration(uint32_t value);
                void        SetStarts_with_SAP(bool value);
                void        SetSAP_Type(uint32_t value);
                void        SetSAP_delta_time(uint32_t value);

                virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;                

                ISOBMFF_EXPORT friend void swap(ReferenceObject& o1, ReferenceObject& o2);

            private:

                class IMPL;

                std::unique_ptr< IMPL > impl;
            };

            std::vector< std::shared_ptr< SIDX::ReferenceObject > >     GetReferenceObjects() const;
            void                                                        AddReferenceObject(std::shared_ptr< ReferenceObject > array);

            ISOBMFF_EXPORT friend void swap( SIDX & o1, SIDX & o2 );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_SIDX_HPP */
