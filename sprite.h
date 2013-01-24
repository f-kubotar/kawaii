#ifndef __kawaii__sprite__
#define __kawaii__sprite__

#include "vertices.h"

#include <memory>
#include <string>

#include <OpenGLES/ES2/gl.h>

namespace kawaii {

class GLProgram;

class Sprite : Node {
public:
    Sprite();
    virtual ~Sprite() {}

    virtual void Render();

private:
    shared_ptr<Texture2D> texture_;
    GLenum blend_func_src_;
    GLenum blend_func_dst_;
    shared_ptr<GLProgram> shader_program_;
    Quad_P3F_C4B_T2F quad_;

    GLubyte opacity_;
    Color3B color_;

    bvec2 flip_;
};

}

#endif /* defined(__kawaii__sprite__) */
