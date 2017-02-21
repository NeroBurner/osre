/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2015-2016 OSRE ( Open Source Render Engine ) by Kim Kulling

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

#include <osre/Common/AbstractService.h>
#include <osre/Common/Event.h>
#include <osre/Common/TObjPtr.h>
#include <osre/RenderBackend/BlendState.h>
#include <osre/RenderBackend/ClearState.h>
#include <osre/RenderBackend/SamplerState.h>
#include <osre/RenderBackend/StencilState.h>
#include <osre/RenderBackend/Pipeline.h>
#include <cppcore/Container/THashMap.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Parameter.h"

namespace OSRE {

// Forward declarations
namespace Platform {
    class AbstractSurface;
}

namespace Properties {
    class Settings;
}

namespace Threading {
    class SystemTask;
}

namespace RenderBackend {

struct BufferData;
struct Geometry;
struct GeoInstanceData;
struct UniformVar;
struct TransformMatrixBlock;

// Event declarations
DECL_EVENT( OnAttachEventHandlerEvent );
DECL_EVENT( OnDetatachEventHandlerEvent );
DECL_EVENT( OnCreateRendererEvent );
DECL_EVENT( OnDestroyRendererEvent );
DECL_EVENT( OnAttachViewEvent );
DECL_EVENT( OnDetachViewEvent );
//DECL_EVENT( OnAttachSceneEvent );
//DECL_EVENT( OnUpdateGeoEvent );
DECL_EVENT( OnClearSceneEvent );
DECL_EVENT( OnDetachSceneEvent );
DECL_EVENT( OnSetRenderStates );
DECL_EVENT( OnRenderFrameEvent );
DECL_EVENT( OnSetParameterEvent );
DECL_EVENT( OnCommitFrameEvent );

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
struct OSRE_EXPORT CreateRendererEventData : public Common::EventData {
    CreateRendererEventData( Platform::AbstractSurface *pSurface )
    : EventData( OnCreateRendererEvent, nullptr )
    , m_activeSurface( pSurface ) 
    , m_defaultFont( "" )
    , m_pipeline( nullptr ) {
        // empty
    }

    Platform::AbstractSurface *m_activeSurface;
    String                     m_defaultFont;
    Pipeline                  *m_pipeline;
};

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
struct OSRE_EXPORT AttachViewEventData : public Common::EventData {
    AttachViewEventData()
    : EventData( OnAttachViewEvent, nullptr ) {
        // empty
    }
};

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
/*struct OSRE_EXPORT AttachGeoEventData : public Common::EventData {
    AttachGeoEventData()
    : EventData( OnAttachSceneEvent, nullptr )
    , m_numGeo( 0 )
    , m_geo( nullptr )
    , m_numInstances( 0 )
    , m_geoInstanceData( nullptr ) {
        // empty
    }

    ui32             m_numGeo;
    Geometry       **m_geo;
    ui32             m_numInstances;
    GeoInstanceData *m_geoInstanceData; 
};*/

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
/*struct OSRE_EXPORT UpdateGeoEventData : public Common::EventData {
    UpdateGeoEventData() 
    : EventData( OnUpdateGeoEvent, nullptr )
    , m_numGeo( 0 )
    , m_geo( nullptr ) {
        // empty
    }
    
    ui32 m_numGeo;
    Geometry *m_geo;
};*/

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
/*struct OSRE_EXPORT SetParameterEventData : public Common::EventData {
    SetParameterEventData()
    : EventData( OnSetParameterEvent, nullptr )
    , m_numParam( 0 )
    , m_param( nullptr ) {
        // empty
    }

    ui32 m_numParam;
    UniformVar **m_param;
};*/

struct OSRE_EXPORT CommitFrameEventData : Common::EventData {
    CommitFrameEventData()
    : EventData( OnCommitFrameEvent, nullptr )
    , m_frame( nullptr ) {
        // empty            
    }

    Frame *m_frame;
};

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief  This class implements the render back-end service.
///
/// A render service implements the low-level API of the rendering. The API-calls will be performed 
/// in its separate render system task. The render back-end handling is implemented by a 
/// API-specific render event handler.
//-------------------------------------------------------------------------------------------------
class OSRE_EXPORT RenderBackendService : public Common::AbstractService {
public:
    /// @brief  The class constructor.
    RenderBackendService();

    /// @brief  The class destructor, virtual.
    virtual ~RenderBackendService();

    /// @brief  Set the configuration for the render service.
    /// @param  config          [in] The render configuration.
    /// @param  moveOwnership   [in] true when ownership shall be moved.
    void setSettings( const Properties::Settings *config, bool moveOwnership );
    
    /// @brief  Returns the render configuration.
    /// @return The render configuration.
    const Properties::Settings *getSettings() const;
        
    /// @brief  Will send a new event to the render system task.
    /// @param  ev          [in] The event identifier.
    /// @param  eventData   [in] The event data.
    void sendEvent( const Common::Event *ev, const Common::EventData *eventData );

    void setMatrix( const String &name, const glm::mat4 &matrix );

    void attachGeo( Geometry *geo );

    void attachGeo( const CPPCore::TArray<Geometry*> &geoArray );

    void attachGeoUpdate( Geometry *geo );

    void attachGeoUpdate( const CPPCore::TArray<Geometry*> &geoArray );

    void attachView( TransformMatrixBlock &transform );

protected:
    /// @brief  The open callback.
    virtual bool onOpen();

    /// @brief  The close callback.
    virtual bool onClose();
    
    /// @brief  The update callback.
    virtual bool onUpdate( d32 timediff );

    /// @brief  Will apply all used parameters
    void commitNextFrame();

private:
    Common::TObjPtr<Threading::SystemTask> m_renderTaskPtr;
    const Properties::Settings *m_settings;
    bool m_ownsSettingsConfig;

    Frame m_nextFrame;
    CPPCore::TArray<Geometry*> m_newGeo;
    CPPCore::TArray<Geometry*> m_geoUpdates;
    CPPCore::THashMap<ui32, UniformVar*>  m_variables;
    CPPCore::TArray<UniformVar*> m_uniformUpdates;
};

} // Namespace RenderBackend
} // Namespace OSRE
