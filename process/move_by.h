#ifndef __skidarak__process_move_by__
#define __skidarak__process_move_by__

#include "skidarak/process/interval.h"
#include "skidarak/node/node.h"

namespace skidarak {

class MoveBy : public Interval {
public:
    static const HashedString TYPE;

    MoveBy(shared_ptr<Node> target, const ii_time duration, const vec3 delta)
        : target_(target),
          Interval(duration),
          delta_(delta) {
    }

    virtual ~MoveBy() {}

    virtual const HashedString& type() const {
        return MoveBy::TYPE;
    }

    virtual void OnEnter() {
        Interval::OnEnter();
        
        if (shared_ptr<Node> node = target_.lock()) {
            from_ = node->position();
        }
    }

    virtual bool Progress(const float progress) {
        if (shared_ptr<Node> node = target_.lock()) {
            vec3 pos = from_ + (delta_ * progress);
            node->set_position(pos);
            return true;
        }
        return false;
    }

private:
    weak_ptr<Node> target_;
    vec3 from_;
    vec3 delta_;
};


}

#endif /* defined(__skidarak__process_move_by__) */
