#include "drawing_primitives.h"

#include "shader_cache.h"
#include "color.h"
#include "OpenGL_Internal.h"

#include <memory>

namespace kawaii {

static bool __initialized = false;
static shared_ptr<GLProgram> gl_program_;
static GLint color_location_ = -1;
static Color4F color_(1,1,1,1);
static int point_size_location_ = -1;
static GLfloat point_size_ = 1;

static void __lazy_init() {
    if (!__initialized) {
        gl_program_ = ShaderCache::Instance()[kShader_Position_uColor];
        color_location_      = glGetUniformLocation(gl_program_->id(), "u_Color");
        point_size_location_ = glGetUniformLocation(gl_program_->id(), "u_PointSize");
        __initialized = true;
    }    
}

void DrawLine(const vec2& origin, const vec2& destination) {
    __lazy_init();

    vec2 vertices[2] = { origin, destination} ;

    gl_program_->Use();
    gl_program_->SetUniformsForBuiltins();

    glUniform4f(color_location_, color_.r, color_.g, color_.b, color_.a);
    CHECK_GL_ERROR();

    glEnableVertexAttribArray(kVertexAttrib_Position);
    glVertexAttribPointer(kVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_LINES, 0, 2);
}

}

