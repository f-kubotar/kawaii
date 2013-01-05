#ifndef __kawaii__scene__
#define __kawaii__scene__

#include "actor.h"
#include "node.h"

#include <memory>
#include <map>

namespace kawaii {
using namespace std;

typedef map<actor_id, shared_ptr<Actor> > ActorTable;

class ProcessManager;

class Scene {
public:
    Scene();
    virtual ~Scene();

    const shared_ptr<ProcessManager> process_manager() const {
        return process_manager_;
    }

    const shared_ptr<Node> root_node() const {
        return root_node_;
    }

    virtual bool Initialize() = 0;

    void Update(const float delta_time);
    void Render();

    void AddActor(const shared_ptr<Actor>& actor);
    const shared_ptr<Actor> ActorById(const actor_id id);
    void AddChildFromActor(shared_ptr<Actor> actor);

protected:
    shared_ptr<ProcessManager> process_manager_;
    ActorTable actor_table_;
    std::map<actor_id, shared_ptr<Node> > node_for_actor_id_;

    shared_ptr<Node> root_node_;
};

}

#endif /* defined(__kawaii__scene__) */
