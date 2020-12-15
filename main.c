#include "gui.h"
#include "cmd.h"
#define MSD_IO_IMPL
#include "mdl_io.h"
#define MDL_STR_IMPL
#include "mdl_str.h"

int main(int argc, char **argv) {
    if ( encInit() < 0 ) return -1;
    
    if ( argc < 2 ) {
        return main_window(argc, argv);
    } else {
        return cmdLine(argc, argv);
    }
}