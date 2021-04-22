#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/bind.h>

#include <stdio.h>
#include <math.h>

#include "glew.h"
#include "typedefs.h"

#define ARRAYSIZE(arr) sizeof(arr) / sizeof((arr)[0])
#define TIMER_START(name) f64 name = emscripten_performance_now()
#define DELTIME(name, del) f32 del = (f32) (emscripten_performance_now() - name)

struct Canvas
{
    i32 w;
    i32 h;
};

Canvas canvas = { 0, 0 };

i32 key(i32 evtType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
{
    return false;
}

i32 mouse(i32 evtType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    return false;
}

i32 wheel(i32 evtType, const EmscriptenWheelEvent *wheelEvent, void *userData)
{
    return false;
}

i32 touch(i32 evtType, const EmscriptenTouchEvent *touchEvent, void *userData)
{
     return false;
}

void initCallbacks()
{
    emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, key);
    emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, key);

    emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, mouse);
    emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, mouse);
    emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, mouse);

    emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, wheel);

    emscripten_set_touchstart_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, touch);
    emscripten_set_touchend_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, touch);
    emscripten_set_touchmove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, true, touch);
}

void initOpenGL()
{    
    EmscriptenWebGLContextAttributes attr;
	emscripten_webgl_init_context_attributes(&attr);

    attr.alpha = false;
	attr.enableExtensionsByDefault = 1;
	attr.majorVersion = 1;
	attr.minorVersion = 0;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);

	emscripten_webgl_make_context_current(ctx);
}


void resized()
{
    emscripten_get_canvas_element_size("#canvas", &canvas.w, &canvas.h);
    glViewport(0, 0, canvas.w, canvas.h);
}