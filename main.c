#include "gui.h"
#include "cmd.h"
#define MSD_IO_IMPLEMENTATION
#include "msd_io.h"
#define MSD_STR_IMPLEMENTATION
#include "msd_str.h"

int main(int argc, char **argv) {
    if ( argc < 2 ) {
        return main_window(argc, argv);
    } else {
        return cmdLine(argc, argv);
    }
}