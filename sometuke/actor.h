#ifndef __sometuke__actor__
#define __sometuke__actor__

#include "sometuke/director.h"
#include "sometuke/vector.h"
#include "sometuke/actor_id.h"

#include <memory>
#include <uuid/uuid.h>

namespace sometuke {

typedef HashedString ActorType;

class Actor;
class Node;

struct ActorAddEvent : public Event {
    static const EventType TYPE;

    ActorAddEvent(const shared_ptr<Actor>& actor)
        : Event(TYPE),
          actor(actor) {
    }

    shared_ptr<Actor> actor;
};

struct ActorRemoveEvent : public Event {
    static const EventType TYPE;

    ActorRemoveEvent(const ActorId& actor_id)
        : Event(TYPE),
          actor_id(actor_id) {
    }

    ActorId actor_id;
};

class Actor {
public:
    Actor(const ActorType& t)
        : type_(t),
          id_() {
          id_.Generate();
    }
    
    virtual ~Actor() {}

    const ActorId& id() const {
        return id_;
    }

    void *id_ptr() {
        return static_cast<void *>(&id_);
    }

    const HashedString& type() const {
        return type_;
    }

    virtual shared_ptr<Node> CreateNode() = 0;

protected:
    ActorId id_;
    HashedString type_;
    // weak_ptr<ActorCollection> collection_;
};

}

#endif /* defined(__sometuke__actor__) */
