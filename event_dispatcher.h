#ifndef __skidarak__event_dispatcher__
#define __skidarak__event_dispatcher__

#include "skidarak/types.h"
#include "skidarak/events.h"
#include "skidarak/memory_pool.h"

#include <memory>
#include <list>
#include <map>
#include <ctime>

#include <uuid/uuid.h>

namespace skidarak {
using namespace std;

typedef enum {
    kScriptDefined,             // Event is defined in script.
    kCodeEventOnly,             // Event is defined by main code, and is NOT callable from script.
    kCodeEventScriptCallable,   // Event is defined by code, but is callable from script.
} EventCallable;

struct EventTypeMetadata {
    explicit EventTypeMetadata(EventCallable c) : callable(c) {}
    EventCallable callable;
};

class EventListener {
public:
    virtual ~EventListener() {}
    virtual bool HandleEvent(shared_ptr<Event> e) = 0;
    virtual bool listening() = 0;
};

template <typename T>
class EventDelegator : public EventListener {
public:
    EventDelegator(weak_ptr<T> handler)
        : handler_(handler) {
    }

    virtual ~EventDelegator() {}

    virtual bool HandleEvent(shared_ptr<Event> e) {
        if (shared_ptr<T> handler_ptr = handler_.lock()) {
            return handler_ptr->HandleEvent(e);
        } else {
            return false;
        }
    }

    virtual bool listening() {
        return !!handler_.lock();
    }

private:
    weak_ptr<T> handler_;
};

class EventDispatcher {
public:
    typedef multimap<EventType, shared_ptr<EventListener> > EventListenerTable;

    EventDispatcher() :
        active_queue_index_(0) {
    }

    bool On(const EventType& type, shared_ptr<EventListener> listener);
    bool Off(const EventType& type, shared_ptr<EventListener> listener);
    bool Off(const EventType& type);
    bool Off(shared_ptr<EventListener> listener);

    template <typename E>
    bool On(shared_ptr<EventListener> listener) {
        return On(E::TYPE, listener);
    }

    template <typename E>
    bool Off() {
        return Off(E::TYPE);
    }

    template <typename E>
    bool Off(shared_ptr<EventListener> listener) {
        return Off(E::TYPE, listener);
    }

    bool Trigger(shared_ptr<Event> event);

    template <class T>
    bool Trigger() {
        shared_ptr<T> event(new T);
        return Trigger(event);
    }

    template <class T, class Arg1, class... Args>
    bool Trigger(Arg1&& arg1, Args&& ... args) {
        shared_ptr<T> event(new T(std::forward<Arg1>(arg1), std::forward<Args>(args)...));
        return Trigger(event);
    }

    bool Queue(shared_ptr<Event> event);

    template<class T>
    bool Queue() {
        shared_ptr<T> event = New<T>();
        return Queue(event);
    }

    template<class T, class Arg1, class... Args>
    bool Queue(Arg1&& arg1, Args&& ... args) {
        shared_ptr<T> event(New<T>(std::forward<Arg1>(arg1), std::forward<Args>(args)...));
        return Queue(event);
    }

    bool Tick(const ii_time max_time);

    template <typename T>
    shared_ptr<EventListener> CreateListener(T *handler) {
        shared_ptr<T> handler_ptr =
            static_pointer_cast<T>(handler->shared_from_this());
        shared_ptr<EventListener> listener(new EventDelegator<T>(handler_ptr));
        return listener;
    }

private:
    bool IsValidType(const EventType& type) const;
    bool IsListerningType(const EventType& type) const;

    enum {
        NUM_QUEUES = 2
    };

    list<shared_ptr<Event> > queues_[NUM_QUEUES];
    int active_queue_index_;

    // EventTypeTable types_;
    EventListenerTable listeners_;
};

}

#endif /* defined(__skidarak__event_dispacher__) */

