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
#pragma once

#include "EditorMain.h"
#include <osre/Common/Event.h>
#include <osre/Scene/Node.h>
#include <osre/App/AppBase.h>
#include <osre/Platform/PlatformInterface.h>
#include <osre/RenderBackend/RenderCommon.h>
#include <osre/App/Project.h>

namespace OSRE {

// Forward declarations ---------------------------------------------------------------------------
namespace Scene {
    class World;
    class Stage;
    class TrackBall;
}

namespace Platform {
    class PlatformInterface;
}

namespace NativeEditor {

class EditorApplication;

class MouseEventListener : public Platform::OSEventListener {
    EditorApplication *m_app;
public:
    MouseEventListener( EditorApplication *app )
    : OSEventListener( "Editor/MouseEventListener" )
    , m_app( app ) {
        // app
    }

    ~MouseEventListener() {
        // empty
    }

    void onOSEvent( const Common::Event &osEvent, const Common::EventData *data ) override {
        if (osEvent == Platform::MouseButtonDownEvent) {
            if (nullptr != data) {
                osre_info( "MouseEventListener", "mouse click" );
            }
        }
    }
};

struct SceneContext {
    Scene::World *ActiveWorld;
    int StageIndex;
    Scene::Stage ActiveStage;
};

class EditorApplication : public App::AppBase {
public:
    EditorApplication( int argc, char *argv[] );
    ~EditorApplication() override;
    int enqueueEvent( const Common::Event *ev, Common::EventData *evData );
    void newProject( const String &name );
    void openWorldAccess();
    void openStageAccess();
    void openNodeAccess();
    void closeNodeAccess();
    void closeStageAccess();
    void closeWorldAccess();
    int importAsset( const String &filename, int flags );
    Platform::PlatformInterface *getPlatformInterface() const;
    bool loadProject( const char *filelocation, int flags );
    bool saveProject( const char *filelocation, int flags );

protected:
    bool onCreate() override;
    void onUpdate() override;

private:
    bool m_worldAccess;
    Scene::World* m_world;
    Scene::Stage* m_stage;
    Scene::Node::NodePtr m_modelNode;
    RenderBackend::TransformMatrixBlock m_transformMatrix;
    Platform::PlatformInterface* m_platformInterface;
    App::Project m_project;
    Scene::TrackBall *m_trackball;
    f32 m_angle;
};

} // Namespace NativeEditor
} // Namespace OSRE
