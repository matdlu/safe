#ifndef CHEST_ENC_H
#define CHEST_ENC_H

#include <sodium.h>
#include <string.h> // memcpy
#include <stdio.h> // files
#include "msd_type.h"

/* should be called before using any function in this header
 * returns < 0 if not properly initialized */
int encInit();

enum ENC_METADATA {
    ENC_METADATA_FILE = 1,
    ENC_METADATA_MESSAGE = 2,
};

typedef struct {
    int r; // is -1 if verification failed, 0 if reading failed
    uchar enc_metadata;
    uintll m_l;
    uchar* m;
    uchar* m_with_header;
} EncDecryptFileOut;
void encDecryptFileOutClear(EncDecryptFileOut* out);

#ifdef ENC_IMPLEMENTATION
#define ENC_ALLOC(m) sodium_allocarray(m, 1);
#define ENC_ZERO(m, m_l) sodium_memzero(m, m_l);
#define ENC_ZERO_AND_FREE(m) sodium_free(m);

void encDecryptFileOutClear(EncDecryptFileOut* out) {
    // not clearing the return value intentionally
    out->enc_metadata = 0;
    out->m_l = 0;
    ENC_ZERO_AND_FREE(out->m_with_header);
}
#endif // ENC_IMPLEMENTATION

/* loads a file, decrypts it and returns it's contents in uchar array */
EncDecryptFileOut encDecryptFile(const char* path, const char* pw); // loads a file from disk into heap buffer

/* encrypts file as message, see crypto.h metadata */
int encEncryptMessage(const char* path, const char* message, const char* pw);

/* encrypts file as file, see crypto.h metadata */
int encEncryptFile(const char* in_path, const char* out_path, const char* pw);

#endif //CHEST_CRYPTO_H
