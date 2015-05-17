/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2015 OSRE ( Open Source Render Engine ) by Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
#pragma once

#include <osre/Common/Types.h>

namespace OSRE {

namespace RenderBackend {
    struct Geometry;
}

namespace Scene {

//-------------------------------------------------------------------------------------------------
///	@class		::ZFXCE2::Scene::GeometryBuilder
///	@ingroup	Application
///
///	@brief  This class is used to create the geometry for base shapes like a triangle.
//-------------------------------------------------------------------------------------------------
class OSRE_EXPORT GeometryBuilder {
public:
    /// @brief  The class constructor.
    GeometryBuilder();

    /// @brief  The class destructor.
    ~GeometryBuilder();

    /// @brief  Will create a triangle geometry.
    /// @return The created geometry.
    RenderBackend::Geometry *createTriangle();

    /// @brief  Will create a box geometry.
    /// @return The created geometry.
    RenderBackend::Geometry *createBox( f32 w, f32 h, f32 d);
};

//-------------------------------------------------------------------------------------------------

} // Namespace Scene
} // namespace OSRE
