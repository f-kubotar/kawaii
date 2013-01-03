#ifndef __kawaii__director__
#define __kawaii__director__

#include "vertices.h"
#include "actor.h"

#include <vector>
#include <memory>
#include <map>

#include <OpenGLES/ES2/gl.h>

namespace kawaii {
using namespace std;

class Texture2D;
class EventManager;
class ProcessManager;
class Scene;

typedef map<actor_id, shared_ptr<Actor> > ActorTable;

class Director {
public:
    Director();
    ~Director();
    bool Initialize();
    void Update(float delta_time);
    void AddActor(const shared_ptr<Actor>& actor);
    const shared_ptr<Actor> ActorById(const actor_id id);

private:
    ActorTable actor_table_;
    EventManager *event_manager_;
    ProcessManager *process_manager_;
    vector<shared_ptr<Scene> > scene_stack_;
    shared_ptr<Scene> running_scene_;
    shared_ptr<Scene> next_scene_;

    // debug
    shared_ptr<Texture2D> texture_;
    GLenum blend_func_src_;
    GLenum blend_func_dst_;
    Quad_P3F_C4B_T2F quad_;
};

}

#endif /* defined(__kawaii__director__) */
