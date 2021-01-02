/*
 * char and string utilities
 */
#ifndef MDL_STR_H
#define MDL_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef unsigned char      uc;
typedef unsigned short int us;
typedef unsigned int       ui;
typedef unsigned long int  ul;

/* ch - char */
int mdlChIs(const char c, const char* chars);
#define mdlChIsSpace(c) (c==' '||c=='\n'||c=='\t'||c=='\v'||c=='\f'||c=='\r')
#define mdlChIsQuote(c) (c=='\''||c=='"')

/* uca - unsigned char array */
char* mdlUcaToStr(unsigned char* uca, size_t uca_l);
char* mdlUcaToStrNew(unsigned char* uca, size_t uca_l);

int mdlStrIsBlank(const char* str);
int mdlStrFindFirst(const char* str, const char* chars);
char* mdlStrCat(const char* s1, const char* s2);
ul mdlStrLen(const char* str);
const char* mdlStrMax(const char* s1, const char* s2);
int mdlStrCmp(const char* s1, const char* s2);
int mdlStrCntSpaces(char* str);
char** mdlStrSplitQS(char* str, size_t* out_l);

/* debug */
void mdlStrDbgPrintChars(const char* str);
void mdlStrDbgPrint(char* str);
void mdlStrDbgPrintArr(char** arr);

size_t mdlNtaLen(void** arr);

typedef struct { char** a; ul l; } StrArr;
StrArr mdlStrSplit(char* str);
#endif //MDL_STR_H

#ifdef MDL_STR_IMPL
#define MDL_DS_IMPL
#include "mdl_ds.h"

int mdlChIs(const char c, const char* chars) {
    ul chars_l;
    for(chars_l = 0; chars[chars_l]; chars_l++)
        if (c == chars[chars_l] ) return 1;
    return 0;
}

char* mdlUcaToStr(unsigned char* uca, size_t uca_l) {
    if ( uca ) {
        uca = realloc(uca, uca_l+1);
        uca[uca_l] = '\0';
    }
    return uca;
}

char* mdlUcaToStrNew(unsigned char* uca, size_t uca_l) {
    if ( uca ) {
        char* str = malloc(uca_l + 1);
        memcpy(str, uca, uca_l);
        str[uca_l] = '\0';
        return str;
    } else {
        return 0;
    }
}

int mdlStrIsBlank(const char* str) {
    if ( str ) {
        while( *str ) {
            if( ! mdlChIsSpace(*str) ) return 0;
            str++;
        }
        return 1;
    }
    return 0;
}

int mdlStrFindFirst(const char* str, const char* chars) {
    if ( str ) {
        ul str_l, chars_l;
        for(str_l = 0; str[str_l]; str_l++)
            for(chars_l = 0; chars[chars_l]; chars_l++)
                if (str[str_l] == chars[chars_l]) return str_l;
    }
    return 0;
}

ul mdlStrLen(const char* str) {
    if ( str ) {
        ul str_l = 0;
        while (str[str_l]) str_l++;
        return str_l--;
    } else {
        return 0;
    }
}

const char* mdlStrMax(const char* s1, const char* s2) {
    return mdlStrLen(s1) > mdlStrLen(s2) ? s1 : s2;
}

char* mdlStrCat(const char* s1, const char* s2) {
    if ( s1 && s2 ) {
        ul s1_l = mdlStrLen(s1);
        ul s2_l = mdlStrLen(s2);

        char* str = malloc(sizeof(char)*(s1_l + s2_l + 1)); // +1 for \0 in the end
        memcpy(str, s1, s1_l);
        memcpy(str + s1_l, s2, s2_l);
        str[s1_l + s2_l] = '\0';

        return str;
    } else {
        return 0;
    }
}

void mdlStrDbgPrintChars(const char* str) {
    ul str_l = mdlStrLen(str);
    int i;
    for(i = 0; i < str_l + 1; i++) {  // +1 to include '\0'
        printf("'%c' ", str[i]);
    }
    putchar('\n');
}

void mdlStrDbgPrint(char* str) {
    if ( str == 0 ) return;

    int i, j;
    int n_space = 0, max = 10;
    char sep = ' ';

    for(i = 0; str[i] != 0; i++) {
        putchar(str[i]);
        if ( (i+1) % max == 0 ) {
            max *= 10;
            n_space += 1;
        }
        putchar(sep);
        for(j = 0; j < n_space; j++) putchar(' ');
    }
    putchar('\n');

    for(i = 0; str[i] != 0; i++)
        printf("%d%c", i, sep);
    putchar('\n');
}

void mdlStrDbgPrintArr(char** arr) {
    if ( arr == 0 ) return;
    int i;
    for (i = 0; arr[i] != 0; i++)
        printf("%d: |%s|\n", i, arr[i]);
}

int mdlStrCmp(const char* s1, const char* s2) {
    if ( s1 && s2 ) {
        int r = 0;

        ul s1_l = 0;
        ul s2_l = 0;

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

int mdlStrCntSpaces(char* str) {
    int l = 0;
    char not_space = 0;
    int i;
    for(i = 0; str[i]; i++) {
        if (mdlChIsSpace(str[i + 1]) || str[i + 1] == 0 ) {
            if ( not_space ) l++;
            not_space = 0;
        } else {
            not_space = 1;
        }
    }

    return l;
}

StrArr mdlStrSplit(char* str) {
    StrArr out;
    out.a = 0;
    out.l = 0;

    ul str_l = 0;
    ul not_space = 0;
    while( str[str_l] ) {
        if (mdlChIsSpace(str[str_l + 1]) || str[str_l + 1] == 0 ) {
            if ( not_space ) out.l++;
            not_space = 0;
        } else {
            not_space = 1;
        }
        str_l++;
    }

    out.a = (char**) malloc( out.l * sizeof out.a);

    out.l = 0;
    not_space = 0;
    int i;
    for(i = 0; i < str_l + 1; i++) {
        if (mdlChIsSpace(str[i]) || str[i] == '\0' ) {
            if ( not_space ) {
                out.a[out.l] = (char*) malloc(not_space * sizeof(char*));
                memcpy(out.a[out.l], str + i - not_space, not_space);
                out.a[out.l][not_space] = '\0';
                out.l++;
            }
            not_space = 0;
        } else {
            not_space++;
        }
    }

    return out;
}

/* returns null terminated array of strings
 * strings are from words enclosed with quotes or words seperated by spaces
 * out_l becomes length of returned array
 * returns 0 if there are unterminated quotes */
char** mdlStrSplitQS(char* str, size_t* out_l) {
    register int a;
    register int b;
    register int c;
    register int i;

    a = 0;
    if ( str[0] != ' ') a++;
    for(i = 0; str[i] != 0; i++) {
        if ( mdlChIsQuote(str[i]) ) {
            if ( ! mdlChIsSpace(str[i-1]) ) a++;
            a++;
            i++;
            while( ! mdlChIsQuote(str[i]) ) {
                if ( str[i] == 0 ) return 0;
                i++;
            }
            a++;
            i++;
            if ( ! mdlChIsSpace(str[i]) ) a++;
        } else if ( i > 0 ) {
            if ( mdlChIsSpace(str[i-1]) && ! mdlChIsSpace(str[i]) ) a++;
            if ( ! mdlChIsSpace(str[i-1]) && mdlChIsSpace(str[i])) a++;
        }
    }
    if ( str[i-1] != ' ' ) a++;

    c = a;
    int aux[c]; // array contains start and end indexes of tokens from str

    a = 0; // aux index
    if ( str[0] != ' ' ) aux[a++] = -1;
    for(i = 0; str[i] != 0; i++) {
        if ( mdlChIsQuote(str[i]) ) {
            if ( ! mdlChIsSpace(str[i-1]) ) aux[a++] = i;
            aux[a++] = i;
            i++;
            while( ! mdlChIsQuote(str[i]) ) i++;
            aux[a++] = i;
            i++;
            if ( ! mdlChIsSpace(str[i]) ) aux[a++] = i - 1;
        } else if ( i > 0 ) {
            if ( mdlChIsSpace(str[i-1]) && ! mdlChIsSpace(str[i]) ) aux[a++] = i - 1;
            if ( ! mdlChIsSpace(str[i-1]) && mdlChIsSpace(str[i])) aux[a++] = i;
        }
    }
    if ( str[i-1] != ' ' ) aux[a] = i;

    c /= 2; // out length
    if ( out_l != 0 ) *out_l = c;

    char** out = malloc((c+1) * sizeof *out);
    out[c] = 0;

    for(i = 0; i < c; i++) {
        a = aux[2*i]; // start
        b = aux[2*i+1] - a; // size = end - start
        out[i] = malloc(b * sizeof out[0]);
        memcpy(out[i], str + a + 1, (b - 1) * sizeof out[0]);
        out[i][b - 1] = '\0';
    }

    return out;
}

size_t mdlNtaLen(void** arr) {
    if ( arr == 0 ) return 0;
    register size_t l;
    for(l = 0; arr[l] != 0; l++);
    return l;
}

#endif // MDL_STR_IMPL