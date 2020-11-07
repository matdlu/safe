#ifndef MSD_STR_H
#define MSD_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msd_type.h"

int msdStrIsSpace(char c);
int msdStrIsBlank(const char* str);
char* msdStrCat(char* s1, const char* s2);
char* msdStrCatNew(const char* s1, const char* s2);
uintll msdStrLen(const char* str);
void msdStrDebugPrintChars(const char* str);
int msdStrCmp(const char* s1, const char* s2);
int msdStrCntSpaces(char* str);
typedef struct {
    uintll sa_l;
    char** sa;
} MsdStrSplitOut;
MsdStrSplitOut msdStrSplit(char* str);

#endif //MSD_STR_H

#ifdef MSD_STR_IMPLEMENTATION

int msdStrIsSpace(char c) {
    return c==' '||c=='\n'||c=='\t'||c=='\v'||c=='\f'||c=='\r';
}

int msdStrIsBlank(const char* str) {
    if ( str ) {
        while( *str ) {
            if( !msdStrIsSpace(*str) ) return 0;
            str++;
        }
        return 1;
    } else {
        return 0;
    }
}

uintll msdStrLen(const char* str) {
    if ( str ) {
        uintll str_l = 0;
        while (str[str_l]) str_l++;
        return str_l--;
    } else {
        return 0;
    }
}

/* msdStrCat - appends s1 to s2 and returns a pointer to the end of the concatenated string
 * returns 0 if one of the arguments was 0 */
char* msdStrCat(char* s1, const char* s2) {
    if ( s1 && s2 ) {
        while( *s1 ) s1++;
        while( *s1++ = *s2++ );
        return --s1;
    } else {
        return 0;
    }
}

char* msdStrCatNew(const char* s1, const char* s2) {
    if ( s1 && s2 ) {
        uintll s1_l = msdStrLen(s1);
        uintll s2_l = msdStrLen(s2);

        char* str = (char*) malloc(s1_l + s2_l + 1); // +1 for \0 in the end

        int i;
        for(i = 0; i < s1_l; i++) str[i] = s1[i];

        for(i = 0; i < s2_l; i++) str[s1_l + i] = s2[i];

        str[s1_l+s2_l+1] = '\0';

        return str;
    } else {
        return 0;
    }
}

void msdStrDebugPrintChars(const char* str) {
    uintll str_l = msdStrLen(str);
    int i;
    for(i = 0; i < str_l + 1; i++) {  // +1 to include '\0'
        printf("'%c' ", str[i]);
    }
    putchar('\n');
}

int msdStrCmp(const char* s1, const char* s2) {
    if ( s1 && s2 ) {
        int r = 0;

        uintll s1_l = 0;
        uintll s2_l = 0;

        while( *(s1 + s1_l) && *(s2 + s2_l) ) {
            r = *(s1 + s1_l++) == *(s2 + s2_l++);
            if ( ! r ) return 0;
        }

        if ( *(s1 + s1_l) ^ *(s2 + s2_l) ) return 0;

        return r;
    } else {
        return 0;
    }
}

int msdStrCntSpaces(char* str) {
    int l = 0;
    char not_space = 0;
    int i;
    for(i = 0; str[i]; i++) {
        if (msdStrIsSpace(str[i + 1]) || str[i + 1] == 0 ) {
            if ( not_space ) l++;
            not_space = 0;
        } else {
            not_space = 1;
        }
    }

    return l;
}

MsdStrSplitOut msdStrSplit(char* str) {
    MsdStrSplitOut out;
    out.sa_l = 0;

    uintll str_l = 0;
    uintll not_space = 0;
    while( str[str_l] ) {
        if (msdStrIsSpace(str[str_l + 1]) || str[str_l + 1] == 0 ) {
            if ( not_space ) out.sa_l++;
            not_space = 0;
        } else {
            not_space = 1;
        }
        str_l++;
    }

    out.sa = (char**) malloc( out.sa_l * sizeof out.sa);

    out.sa_l = 0;
    not_space = 0;
    int i;
    for(i = 0; i < str_l + 1; i++) {
        if (msdStrIsSpace(str[i]) || str[i] == '\0' ) {
            if ( not_space ) {
                out.sa[out.sa_l] = (char*) malloc(not_space * sizeof(char*));
                memcpy(out.sa[out.sa_l], str + i - not_space, not_space);
                out.sa[out.sa_l][not_space] = '\0';
                out.sa_l++;
            }
            not_space = 0;
        } else {
            not_space++;
        }
    }

    return out;
}

//todo: make a splitting function based on overwriting the input placing \0 at the end of words and making a pointer array to begginings of these words

#endif // MSD_STR_IMPLEMENTATION
