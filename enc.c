#define ENC_IMPLEMENTATION
#include "enc.h"

#define ENC_KEY_L  8 * crypto_secretbox_KEYBYTES
#define ENC_NONCE_L  8 * crypto_secretbox_NONCEBYTES
#define ENC_SALT_L  8 * crypto_pwhash_SALTBYTES

int encInit() {
    return sodium_init();
}

static uintll encStrLen(const char* str) {
    if ( str ) {
        size_t str_l = 0;
        while (str[str_l]) str_l++;
        return str_l--;
    } else {
        return 0;
    }
}

/* encryption */

static void encPbkdf(const char* pw, const uchar* salt, uchar* key) {
    size_t pw_l = encStrLen(pw);

    if (crypto_pwhash
                (key, ENC_KEY_L, pw, pw_l, salt,
                 crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
                 crypto_pwhash_ALG_ARGON2ID13) != 0) {
        /* out of memory, propably ignore it, since it would propably be impossible on desktop */
    }
}

typedef struct {
    uchar salt[ENC_SALT_L];
    uchar nonce[ENC_NONCE_L];
    uintll m_l;
    uintll m_enc_l;
    uchar* m_enc;
} EncEncryptOut;

static void encEncryptOutClear(EncEncryptOut* out) {
    ENC_ZERO(out->salt, ENC_SALT_L);
    ENC_ZERO(out->nonce, ENC_NONCE_L);
    out->m_l = 0;
    out->m_enc_l = 0;
    ENC_ZERO_AND_FREE(out->m_enc)
}

static EncEncryptOut encEncrypt(uchar* m, const uintll m_l, const char* pw) {
    size_t m_enc_l = m_l + crypto_secretbox_MACBYTES; // + space for authentication header
    uchar* m_enc = ENC_ALLOC(m_enc_l);

    /* generate nonce */
    uchar nonce[ENC_NONCE_L];
    randombytes_buf(&nonce, ENC_NONCE_L);

    /* derive key from password */
    uchar salt[ENC_SALT_L];
    randombytes_buf(salt, ENC_SALT_L);
    uchar key[ENC_KEY_L];
    encPbkdf(pw, salt, key);

    /* actual encryption */
    crypto_secretbox_easy(m_enc, m, m_l, nonce, key);

    /* output handling */
    EncEncryptOut out;
    out.m_l = m_l;
    out.m_enc = m_enc;
    out.m_enc_l = m_enc_l;
    memcpy(out.nonce, nonce, ENC_NONCE_L); //for(int i = 0; i < ENC_NONCE_L; i++) out.nonce[i] = nonce[i];
    memcpy(out.salt, salt, ENC_SALT_L); //for(int i = 0; i < ENC_SALT_L; i++) out.salt[i] = salt[i];

    return out;
}

static uchar* encDecrypt(uchar* m_enc, const uintll m_enc_l, const uchar* nonce, const uchar* salt, const char* pw) {
    uchar *m_dec = ENC_ALLOC(m_enc_l - crypto_secretbox_MACBYTES); // todo: check if this screwed up something

    uchar key[ENC_KEY_L];
    encPbkdf(pw, salt, key);

    if ( crypto_secretbox_open_easy(m_dec, m_enc, m_enc_l, nonce, key) >= 0 ) {
        return m_dec;
    } else {
        return 0; // verification failed
    }
}

/* file IO */

/* encrypted header
 * uchar enc_metadata
 * uintll m_l
 * */

typedef struct { // todo: the first information could be the length of the header, in case the header would change, it would be possible to add backwards compatibility
    uintll salt_l;
    uchar salt[ENC_SALT_L];
    uintll nonce_l;
    uchar nonce[ENC_NONCE_L];
    uintll m_enc_l;
} EncNotEncryptedHeader;

static void encNotEncryptedHeaderClear(EncNotEncryptedHeader* neh) {
    ENC_ZERO(neh->salt, neh->salt_l);
    neh->salt_l = 0;
    ENC_ZERO(neh->nonce, neh->nonce_l);
    neh->nonce_l = 0;
    neh->m_enc_l = 0;
}

/* encrypts uchar array then saves it to file on path
 * returns 0 if writing failed */
static int encEncryptToFile(const char* path, const uchar* m, const uintll m_l, const char* pw, const uchar enc_metadata) {
    uintll m_with_header_l = m_l + sizeof enc_metadata + sizeof m_l;
    uchar* m_with_header = ENC_ALLOC(m_with_header_l);

    /* copy EncEncryptedHeader data to m_with_header */
    *m_with_header = enc_metadata;
    memcpy(m_with_header + sizeof enc_metadata, &m_l, sizeof m_l);
    memcpy(m_with_header + sizeof enc_metadata + sizeof m_l, m, m_l); //for(int i = 0; i < m_l; i++) m_with_header[i + sizeof eh] = m[i];

    EncEncryptOut encrypt_out = encEncrypt(m_with_header, m_with_header_l, pw);

    /* clear m_with_header */
    ENC_ZERO_AND_FREE(m_with_header);

    EncNotEncryptedHeader neh;
    neh.salt_l = ENC_SALT_L;
    memcpy(neh.salt, encrypt_out.salt, ENC_SALT_L); //for(int i = 0; i < ENC_SALT_L; i++) neh.salt[i] = encrypt_out.salt[i];
    neh.nonce_l = ENC_NONCE_L;
    memcpy(neh.nonce, encrypt_out.nonce, ENC_NONCE_L); //for(int i = 0; i < ENC_NONCE_L; i++) neh.nonce[i] = encrypt_out.nonce[i];
    neh.m_enc_l = encrypt_out.m_enc_l;

    FILE *f = fopen(path, "wb");
    if ( ! fwrite(&neh.salt_l, 8, 1, f) ) return 0;
    if ( ! fwrite(neh.salt, neh.salt_l, 1, f) ) return 0;
    if ( ! fwrite(&neh.nonce_l, 8, 1, f) ) return 0;
    if ( ! fwrite(neh.nonce, neh.nonce_l, 1, f) ) return 0;
    if ( ! fwrite(&neh.m_enc_l, 8, 1, f) ) return 0;
    if ( ! fwrite(encrypt_out.m_enc, encrypt_out.m_enc_l, 1, f) ) return 0;
    fclose(f);

    encEncryptOutClear(&encrypt_out);

    encNotEncryptedHeaderClear(&neh);

    // todo: do something to overwrite the internal fwrite buffer, or use an unbuffered function
    return 1;
}

EncDecryptFileOut encDecryptFile(const char* path, const char* pw) { // loads a file from disk into heap buffer
    EncDecryptFileOut out;
    EncNotEncryptedHeader neh;

    FILE *f = fopen(path, "rb");
    if ( ! fread(&neh.salt_l, 8, 1, f) ) { out.r = 0; return out; }
    if ( ! fread(neh.salt,neh.salt_l, 1, f) ) { out.r = 0; return out; }
    if ( ! fread(&neh.nonce_l, 8, 1, f) ) { out.r = 0; return out; }
    if ( ! fread(neh.nonce, neh.nonce_l, 1, f) ) { out.r = 0; return out; }
    if ( ! fread(&neh.m_enc_l, 8, 1, f) ) { out.r = 0; return out; }
    uchar* m_enc = ENC_ALLOC(neh.m_enc_l);
    if ( ! fread(m_enc, neh.m_enc_l, 1, f) ) { out.r = 0; return out; }
    fclose(f);

    uchar* m_with_header = encDecrypt(m_enc, neh.m_enc_l, neh.nonce, neh.salt, pw);
    out.r = m_with_header ? 1 : -1;

    encNotEncryptedHeaderClear(&neh);

    if ( out.r > 0 ) {
        out.enc_metadata = *m_with_header;
        memcpy(&out.m_l, m_with_header + sizeof out.enc_metadata, sizeof out.m_l);

        out.m = m_with_header + 1 + sizeof out.m_l;
        out.m_with_header = m_with_header;
    }

    return out;
}

/* convenience functions */

int encEncryptMessage(const char* path, const char* message, const char* pw) {
    return encEncryptToFile(path, message, encStrLen(message), pw, ENC_METADATA_MESSAGE); // todo: check if encEncryptToFile accepts m as const and change it if it does else make message not const
}

/* todo: use something better than fseek to get rid of fseek 2GB limitation */
int encEncryptFile(const char* in_path, const char* out_path, const char* pw) {
    FILE *f_in = fopen(in_path, "rb");

    fseek(f_in, 0l, SEEK_END);
    int f_l = ftell(f_in); // todo: error handling if -1
    fseek(f_in, 0l, SEEK_SET);

    uchar* buf = ENC_ALLOC(f_l);
    fread(buf, f_l, 1, f_in);

    int r = encEncryptToFile(out_path, buf, f_l, pw, ENC_METADATA_FILE);

    ENC_ZERO_AND_FREE(buf);
    f_l = 0;

    return r;
}
