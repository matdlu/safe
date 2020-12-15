/*
 * commandline input and output
 */
#ifndef MSD_IO_H
#define MSD_IO_H
#include <stdio.h>
#include <stdlib.h>

#define MSD_IO_LINE_MAX 1024

char* mdlIoGetLine();
char* mdlIoGetStr();
int mdlIoToFile(const void* p, size_t p_l, const char* path);

#endif //MDL_IO_H
#ifdef MSD_IO_IMPL

/* returns 0 if the line is longer than MSD_IO_LINE_MAX */
char* mdlIoGetLine() {
    char* line = malloc(MSD_IO_LINE_MAX);

    int line_l = 0;
    while ( (line[line_l] = getchar()) != '\n' && line_l++ < MSD_IO_LINE_MAX );

    return line_l < MSD_IO_LINE_MAX ? line : 0;
}

/* same as msdIoGetLine but removes the newline at the end */
char* mdlIoGetStr() {
    char* line = malloc(MSD_IO_LINE_MAX);

    int line_l = 0;
    while ( (line[line_l] = getchar()) != '\n' && line_l++ < MSD_IO_LINE_MAX );
    line[line_l] = '\0';

    return line_l < MSD_IO_LINE_MAX ? line : 0;
}

int mdlIoToFile(const void* p, size_t p_l, const char* path) {
    FILE* f_out = fopen(path, "wb");
    if ( f_out == 0 ) return -2;
    if ( fwrite(p, p_l, 1, f_out) != 1 ) return -3;
    if ( fclose(f_out) == EOF ) return -1;
    return 0;
}
#endif // MSD_IO_IMPL
