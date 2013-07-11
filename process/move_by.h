#ifndef __skidarake__process_move_by__
#define __skidarake__process_move_by__

#include "skidarake/process/interval.h"
#include "skidarake/node/node.h"

namespace skidarake {

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

#endif /* defined(__skidarake__process_move_by__) */
