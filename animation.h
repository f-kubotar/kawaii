#ifndef __skidarake__animation__
#define __skidarake__animation__

#include "skidarake/types.h"
#include "skidarake/event_dispatcher.h"
#include "skidarake/sprite_frame_cache.h"
#include "skidarake/logger.h"

#include <vector>
#include <memory>
#include <string>

namespace skidarake {
using namespace std;

struct AnimationFrame {
    AnimationFrame(shared_ptr<SpriteFrame> f, ii_time t, shared_ptr<Event> e = NULL)
        : sprite_frame(f),
          time(t) {
    }

    shared_ptr<SpriteFrame> sprite_frame;
    ii_time time;
};

struct Animation {
    explicit Animation(vector<AnimationFrame> f, unsigned int l=1)
        : frame_size(f.size()),
          loops(l),
          frames(f) {
    }

    explicit Animation(unsigned int l=1)
        : frame_size(),
          loops(l) {
    }

    void Push(const char *sprite_frame_name, ii_time t, shared_ptr<Event> e = NULL) {
        SpriteFrameCache& cache = SpriteFrameCache::Instance();
        shared_ptr<SpriteFrame> sprite_frame = cache[sprite_frame_name];
        if (!sprite_frame) {
            IIERROR("sprite frame name %s not found", sprite_frame_name);
        }

        AnimationFrame frame(sprite_frame, t, e);
        frames.push_back(frame);
        frame_size = frames.size();
    }

    unsigned int frame_size;
    unsigned int loops;
    vector<AnimationFrame> frames;
};

}

#endif /* defined(__skidarake__animation__) */
