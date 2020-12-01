#include "gui.h"
#include "cmd.h"
#define MSD_IO_IMPL
#include "mdl_io.h"
#define MDL_STR_IMPL
#include "mdl_str.h"

int main(int argc, char **argv) {
    //char* str1 = "test \"dsa \"sdsa \"   \" fdsf \"safd aks\"     hfdhafs alkfs end";
    //char* str2 = "test";
    //char* str3 "d file asd";
    //char* str4 = "h";
    //char* str = str1;
    //printf("%s\n", str);
    //StrArr arr = msdStrSplitQuotes(str);
    //int i;
    //for(i = 0 ; i < arr.l; i++) {
    //    printf("\"%s\"\n", arr.a[i]);
    //}
    //return 0;
    if ( argc < 2 ) {
        return main_window(argc, argv);
    } else {
        return cmdLine(argc, argv);
    }
}