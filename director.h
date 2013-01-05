#ifndef __kawaii__director__
#define __kawaii__director__

#include <vector>
#include <memory>
#include <map>

#include <OpenGLES/ES2/gl.h>

namespace kawaii {
using namespace std;

class EventManager;
class Scene;

class Director {
public:
    Director();
    ~Director();
    void ReshapeProjection();
    void MainLoop(const float delta_time);

    void RunWithScene(shared_ptr<Scene> scene);
    // void ReplaceScene(shared_ptr<Scene> scene);
    // void PushScene(shared_ptr<Scene> scene);
    // void PopScene();

    // void SetNextScene(shared_ptr<Scene> scene);

    void End();

private:
    EventManager *event_manager_;
    vector<shared_ptr<Scene> > scene_stack_;
    shared_ptr<Scene> running_scene_;
    shared_ptr<Scene> next_scene_;
};

}

#endif /* defined(__kawaii__director__) */
