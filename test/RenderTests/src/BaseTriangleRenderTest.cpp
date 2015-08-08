#include "AbstractRenderTest.h"
#include "RenderTestUtils.h"

#include <osre/Common/Logger.h>
#include <osre/RenderBackend/RenderBackendService.h>
#include <osre/RenderBackend/RenderCommon.h>
#include <src/RenderBackend/OGLRenderer/OGLShader.h>
#include <osre/Scene/GeometryBuilder.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef WIN32
#   include "GL/wglew.h"
#endif

#include <iostream>

namespace OSRE {
namespace RenderTest {

using namespace ::OSRE::RenderBackend;

glm::mat4 P = glm::mat4( 1 );
glm::mat4 M = glm::mat4( 1 );
glm::mat4 V = glm::mat4( 1 );

// vertex array and vertex buffer object IDs
float angle = 0.0f;

//-------------------------------------------------------------------------------------------------
///	@class		::OSRE::RenderTest::BaseTriangleRenderTest
///	@ingroup	Test
///
///	@brief  This class implements a base triangle render test.
//-------------------------------------------------------------------------------------------------
class BaseTriangleRenderTest : public AbstractRenderTest {
    TransformMatrixBlock m_transformMatrix;

public:
    BaseTriangleRenderTest()
    : AbstractRenderTest( "rendertest/basetrianglerendertest" ) {
        // empty
    }

    virtual ~BaseTriangleRenderTest() {
        // empty
    }

    virtual bool onCreate( RenderBackend::RenderBackendService *pRenderBackendSrv ) {
        pRenderBackendSrv->sendEvent( &OnAttachViewEvent, nullptr );
        AttachGeoEventData *attachGeoEvData = new AttachGeoEventData;
        
        Scene::GeometryBuilder myBuilder;
        Geometry *pGeometry = myBuilder.createTriangle();
        attachGeoEvData->m_numGeo = 1;
        attachGeoEvData->m_pGeometry = pGeometry;

        m_transformMatrix.m_model = glm::rotate( m_transformMatrix.m_model, 0.0f, glm::vec3( 1, 1, 0 ) );

        Parameter *parameter = Parameter::create( "MVP", PT_Mat4 );
        ::memcpy( parameter->m_data.m_data, glm::value_ptr( m_transformMatrix.m_projection*m_transformMatrix.m_view*m_transformMatrix.m_model ), sizeof( glm::mat4 ) );

        pGeometry->m_parameter = parameter;
        pGeometry->m_numParameter++;

        pRenderBackendSrv->sendEvent( &OnAttachSceneEvent, attachGeoEvData );

        return true;
    }

    //---------------------------------------------------------------------------------------------
    virtual bool onRender( d32 timediff, RenderBackend::RenderBackendService *pRenderBackendSrv ) {
        return true;
    }
};

ATTACH_RENDERTEST( BaseTriangleRenderTest )

//-------------------------------------------------------------------------------------------------

} // Namespace RenderTest
} // Namespace OSRE
