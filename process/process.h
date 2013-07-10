#ifndef __skidarak__process_process__
#define __skidarak__process_process__

#include "skidarak/application.h"
#include "skidarak/hashed_string.h"
#include "skidarak/types.h"
#include "skidarak/memory_pool.h"
#include "skidarak/process/process_manager.h"
#include "skidarak/logger.h"

#include <memory>

namespace skidarak {
using namespace std;

class Sequence;

class Process : public enable_shared_from_this<Process> {
public:
    Process()
        : running_(false),
          sleeping_(false) {
    }
    
    virtual ~Process() {}

    const bool running() {
        return running_;
    }

    const bool sleeping() const {
        return sleeping_;
    }

    void Sleep()  { sleeping_ = true; }
    void Wakeup() { sleeping_ = false; }

    virtual EventDispatcher& dispatcher() const {
        return Application::Instance().director().dispatcher();
    }

    void Enter() {
        if (!running_) {
            OnEnter();
            running_ = true;
        }
    }

    void Exit() {
        OnExit();
        running_ = false;
    }

    virtual bool Update(const ii_time delta) = 0;
    
    virtual const HashedString& type() const = 0;

    shared_ptr<Process> Repeat(int repeat = -1);
    shared_ptr<Process> Delay(const ii_time duration);
    shared_ptr<Process> Interval(const ii_time interval);
    shared_ptr<Process> Timer(const ii_time interval,
                              const unsigned int repeat, const ii_time delay);

    template<class T>
    shared_ptr<Sequence> Chain();
    
    template<class T, class Arg1, class... Args>
    shared_ptr<Sequence> Chain(Arg1&& arg1, Args&& ... args);

protected:
    bool running_;
    bool killed_;
    bool sleeping_;

    virtual void OnEnter() {}
    virtual void OnExit() {}

private:
    Process(const Process&);
    Process& operator=(const Process&);
};

}

#endif /* defined(__skidarak__process_process__) */
