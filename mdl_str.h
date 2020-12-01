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

int mdlChIsSpace(const char c);
int mdlChIs(const char c, const char* chars);
int mdlStrIsBlank(const char* str);
int mdlStrFindFirst(const char* str, const char* chars);
char* mdlStrCat(char* s1, const char* s2);
char* mdlStrCatNew(const char* s1, const char* s2);
ul mdlStrLen(const char* str);
void mdlStrDebugPrintChars(const char* str);
int mdlStrCmp(const char* s1, const char* s2);
int mdlStrCntSpaces(char* str);

extern const char* MDL_STR_CHARS_WHITE;

typedef struct { char** a; ul l; } StrArr;
StrArr mdlStrSplit(char* str);
StrArr mdlStrSplitQuotes(char* str);
#endif //MDL_STR_H

#ifdef MDL_STR_IMPL
#define MDL_DS_IMPL
#include "mdl_ds.h"

const char* MDL_STR_CHARS_WHITE = " \n\t\v\f\r";

int mdlChIsSpace(const char c) {
    return c==' '||c=='\n'||c=='\t'||c=='\v'||c=='\f'||c=='\r';
}

int mdlChIs(const char c, const char* chars) {
    ul chars_l;
    for(chars_l = 0; chars[chars_l]; chars_l++)
        if (c == chars[chars_l] ) return 1;
    return 0;
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

/* mdlStrCat - appends s1 to s2 and returns a pointer to the end of the concatenated string
 * returns 0 if one of the arguments was 0 */
char* mdlStrCat(char* s1, const char* s2) {
    if ( s1 && s2 ) {
        while( *s1 ) s1++;
        while( *s1++ = *s2++ );
        return --s1;
    } else {
        return 0;
    }
}

char* mdlStrCatNew(const char* s1, const char* s2) {
    if ( s1 && s2 ) {
        ul s1_l = mdlStrLen(s1);
        ul s2_l = mdlStrLen(s2);

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

void mdlStrDebugPrintChars(const char* str) {
    ul str_l = mdlStrLen(str);
    int i;
    for(i = 0; i < str_l + 1; i++) {  // +1 to include '\0'
        printf("'%c' ", str[i]);
    }
    putchar('\n');
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

int mdlStrIsQuote(char c) {
    return c=='\''||c=='"';
}

StrArr mdlStrSplitQuotes(char* str) {
    int str_l;
    int ind = 0;
    int i = 0;
    StrArr out;

    MdlDsDynArr* da_words = mdlDsDynArrNew(sizeof(MdlDsDynArr*));
    MdlDsDynArr* da_word = mdlDsDynArrNew(sizeof(char));

    for(str_l = i = ind = 0; str[str_l]; str_l++) {
        //printf("%d %d %c %d %d\n", str_l, ind, str[str_l], out.sa_l, i);
        if (mdlStrIsQuote(str[str_l])) {
            ind++;
            if( ind % 2 == 0 ) {
                i = 0;
                mdlDsDynArrAdd(da_word, &i);
                mdlDsDynArrAdd(da_words, da_word);
                da_word = mdlDsDynArrNew(sizeof(char));
            }
        } else if ( ind % 2 != 0 ) {
            mdlDsDynArrAdd(da_word, &str[str_l]);
            i++;
        } else if ( ind % 2 == 0 ) {
            if ( ! mdlChIsSpace(str[str_l]) ) {
                mdlDsDynArrAdd(da_word, &str[str_l]);
                i++;
            } else if ( i > 1 ) {
                i = 0;
                mdlDsDynArrAdd(da_word, &i);
                mdlDsDynArrAdd(da_words, da_word);
                da_word = mdlDsDynArrNew(sizeof(char));
            }
        }
        ind = ind < INT_MAX ? ind : 0; // prevent integer overflow
    }
    if ( i > 1 || ind % 2 == 0) {
        i = 0;
        mdlDsDynArrAdd(da_word, &i);
        mdlDsDynArrAdd(da_words, da_word);
        mdlDsDynArrTrim(da_words);
    }

    out.a = (char **) da_words->a;
    out.l = da_words->l;

    return out;
}
#endif // MDL_STR_IMPL