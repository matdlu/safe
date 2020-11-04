#include "gui.h"
#include "cmd.h"

#include "enc.h"
//#include "msd_rnd.h"

#define MSD_STR_IMPLEMENTATION
#include "msd_str.h"
#define MSD_IO_IMPLEMENTATION
#include "msd_io.h"

#include <limits.h>

int main(int argc, char **argv) {
    // printf("%llu\n", msdStrCat(0, 0));

    //char* str="h\r\n";
    //printf("%llu\n", msdStrCntSpaces(str));
    //MsdStrSplitOut out = msdStrSplit(str);
    //for(int i = 0; i < out.sa_l; i++) msd_str_printchars(out.sa[i]);

    cmdPrompt();

    //if ( ! argv[1] ) {
    //    main_window(argc, argv);
    //} else {
    //    if( ! cmdLine(argc, argv) ) main_window(argc, argv);
    //}
}