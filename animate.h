#ifndef __kawaii__animate__
#define __kawaii__animate__

#include "process.h"
#include "animation.h"

#include <memory>

namespace kawaii {
    
class Sprite;

class Animate : public Process {
public:
    static const HashedString TYPE;
    Animate(shared_ptr<Animation> animation, shared_ptr<Sprite> target) :
        animation_(animation),
        frame_num_(0),
        elapsed_(0),
        target_(target),
        original_frame_() {
    }

    virtual const HashedString& type() {
        return Animate::TYPE;
    }
    
    virtual void Update(ii_time delta_time);

private:
    shared_ptr<Sprite> target_;
    shared_ptr<SpriteFrame> original_frame_;
    unsigned int frame_num_;
    shared_ptr<Animation> animation_;
    ii_time elapsed_;
};

}

#endif /* defined(__kawaii__animate__) */
