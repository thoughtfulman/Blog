extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
struct dt_rectangle_s {
    double left;
    double bottom;
    double right;
    double top;
} dt_rectangle_t;
