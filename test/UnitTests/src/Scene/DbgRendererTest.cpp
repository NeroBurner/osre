/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2015-2019 OSRE ( Open Source Render Engine ) by Kim Kulling

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
#include "osre_testcommon.h"
#include <osre/RenderBackend/RenderBackendService.h>
#include <osre/Scene/DbgRenderer.h>

namespace OSRE {
namespace UnitTest {

class TestRenderBackendService : public RenderBackend::RenderBackendService {
public:
    TestRenderBackendService() : RenderBackendService() {}
    ~TestRenderBackendService(){}
};

using namespace ::OSRE::Scene;

class DbgRendererTest : public ::testing::Test {
    // empty
};

TEST_F( DbgRendererTest, create_Success ) {
    RenderBackend::RenderBackendService *tstRBSrv = new TestRenderBackendService;
    DbgRenderer::create( tstRBSrv );
    DbgRenderer::destroy();
    delete tstRBSrv;
}

TEST_F( DbgRendererTest, clearDbgCache_Success ) {
#ifdef OSRE_WINDOWS
    
    RenderBackend::RenderBackendService *tstRBSrv = new TestRenderBackendService;
    DbgRenderer::create( tstRBSrv );

    DbgRenderer::getInstance()->renderDbgText( 1, 1, 1, "xxx" );
    const size_t num_1( DbgRenderer::getInstance()->numDbgTexts() );
    EXPECT_EQ( 0, num_1 );
    DbgRenderer::getInstance()->clearDbgTextCache();
    const size_t num_2( DbgRenderer::getInstance()->numDbgTexts() );
    EXPECT_EQ( 0, num_2  );
    DbgRenderer::destroy();
    delete tstRBSrv;

#endif
}

} // Namespace UnitTest
} // Namespace OSRE
