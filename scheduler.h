#ifndef __kawaii__scheduler__
#define __kawaii__scheduler__

#include "kawaii/types.h"

#include <memory>
#include <list>
#include <map>
#include <cassert>

namespace kawaii {
using namespace std;

class UpdateInterface {
public:
    virtual ~UpdateInterface() {}
    virtual void Update(const ii_time delta) = 0;
    virtual const bool sleeping() = 0;
};

class Timer : public UpdateInterface {
public:
    static const unsigned int REPEAT_FOREVER;
    
    Timer(shared_ptr<UpdateInterface> delegate)
        : delegate_(delegate),
          elapsed_(0),
          num_executed_(0),
          interval_(0),
          delay_(0),
          use_delay_(false),
          repeat_(REPEAT_FOREVER),
          run_forever_(true) {
    }

    Timer(shared_ptr<UpdateInterface> delegate, const ii_time interval)
        : delegate_(delegate),
          elapsed_(0),
          num_executed_(0),
          interval_(interval),
          delay_(0),
          use_delay_(false),
          repeat_(REPEAT_FOREVER),
          run_forever_(true) {
    }

    Timer(shared_ptr<UpdateInterface> delegate, const ii_time interval,
          const unsigned int repeat, const ii_time delay)
        : delegate_(delegate),
          elapsed_(0),
          num_executed_(0),
          interval_(interval),
          delay_(delay),
          use_delay_(delay > 0),
          repeat_(repeat),
          run_forever_(repeat == REPEAT_FOREVER) {
    }

    virtual bool Update(const ii_time delta);
    virtual bool sleeping() {
        return delegate_->sleeping();
    }

    shared_ptr<UpdateInterface> delegate() {
        return delegate_;
    }

private:    
    shared_ptr<UpdateInterface> delegate_;
    ii_time elapsed_;
    ii_time interval_;
    ii_time delay_;
    bool use_delay_;
    unsigned int repeat_;
    bool run_forever_;
    int num_executed_;
};

typedef list<shared_ptr<UpdateInterface> > UpdateList;

class Scheduler {
public:
    void Attach(shared_ptr<UpdateInterface> delegate);
    void Attach(shared_ptr<UpdateInterface> delegate, const ii_time interval);
    void Attach(shared_ptr<UpdateInterface> delegate, const ii_time interval,
                const unsigned int repeat, const ii_time delay);

    void Detach(shared_ptr<UpdateInterface> delegate);

    void ScheduleUpdateFor(shared_ptr<UpdateInterface> update_entry);
    void UnScheduleUpdateFor(shared_ptr<UpdateInterface> update_entry);

    bool Update(const ii_time delta_time);

private:
    UpdateList update_list_;
};

}

#endif /* defined(__kawaii__scheduler__) */
