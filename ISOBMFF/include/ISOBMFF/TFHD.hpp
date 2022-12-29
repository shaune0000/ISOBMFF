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

#ifndef ISOBMFF_TFHD_HPP
#define ISOBMFF_TFHD_HPP

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
    /*
        0x000001 base‐data‐offset‐present: 表示 base‐data‐offset。其为每个track run的数据偏移（data offse）中提供了 一个清晰的锚点。如果此项没有提供或者default‐base‐is‐moof标志没有设置，在movie fragment 中的第一个track 的base‐data‐offset 是Movie Fragment Box的第一个byte的位置，对于第二个和接下来的track fragments，默认项是由前一个fragment的数据的结尾。Fragments 以这种必须都使用相同的数据引用的方式“继承”它们的偏移量。(也就是，这些track的数据必须在同一个文件中。)
        0x000002 sample‐description‐index‐present: 默认在Track Extends Box中设置。此处则是对其覆盖。
        0x000008 default‐sample‐duration‐present
        0x000010 default‐sample‐size‐present
        0x000020 default‐sample‐flags‐present
        0x010000 duration‐is‐empty: 表示duration 为0，无论是 default-sample duration或者是 Track Extends Box的 default-sample。也就是说，这个时间片中没有sample。在面两种情况同时存在时，在Moive Box中有 edit lists，且有empty-duration fragments，此时 make a presentation是错误的。
        0x020000 default‐base‐is‐moof: 若果 base‐data‐offset‐present 是 1, 此标志忽略。如果 base‐dataoffset‐present 为 0 ，则意味着此track fragment 的 base‐data‐offset 是 enclosing Movie Fragment Box的第一个byte的位置。假设 default‐base‐is-moof 在 ‘iso5’ brand 是需要的，其不能在早于iso5之前的brands或者兼容brands中使用。
        NOTE 使用default-base-is-moof标志会破坏与早期品牌文件格式的兼容性，因为它为偏移计算设置的锚点与以前不同。因此，当“ftyp” box 中包含早期品牌时，无法设置default-base-is-moof标志。
     */
    //https://www.cnblogs.com/gardenofhu/p/10040122.html
    class ReferenceObject;
    class ISOBMFF_EXPORT TFHD: public FullBox //Movie Fragment Header Box
    {
        public:
            
            TFHD();
            TFHD( const TFHD & o );
            TFHD( TFHD && o ) noexcept;
            virtual ~TFHD() override;
            
            TFHD & operator =( TFHD o );
            
            void                                                        ReadData( Parser & parser, BinaryStream & stream ) override;
            std::vector< std::pair< std::string, std::string > >        GetDisplayableProperties() const override;
            
            uint32_t    GetTrack_ID()  const;   
            uint64_t    GetBase_Data_Offset()  const;   
            uint32_t    GetSample_Description_Index()  const;
            uint32_t    GetDefault_Sample_Duration()  const;
            uint32_t    GetDefault_Sample_Size()  const;
            uint32_t    GetDefault_Sample_Flags()  const;

            void        SetTrack_ID(uint32_t value);
            void        SetBase_Data_Offset(uint64_t value);
            void        SetSample_Description_Index(uint32_t value);
            void        SetDefault_Sample_Duration(uint32_t value);
            void        SetDefault_Sample_Size(uint32_t value);
            void        SetDefault_Sample_Flags(uint32_t value);

            ISOBMFF_EXPORT friend void swap( TFHD & o1, TFHD & o2 );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_TFHD_HPP */
