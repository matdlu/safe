#include "cmd.h"

static int cmdParse(const char* str) {
    int i;
    for (i = 0; i < CMD_ENUM_LENGTH; i++) {
        if (msdStrCmp(str, CMD_STR[i]) || msdStrCmp(str, CMD_STR_SHORT[i]) ) {
            return i;
        }
    }
    return CMD_NO_CMD;
}

static int cmdEncryptMessage(const char* path, const char* message, const char* pw) {
    encInit();
    return encEncryptMessage(path, message, pw);
}
static int cmdEncryptFile(const char* in_path, const char* out_path, const char* pw) {
    encInit();
    return encEncryptFile(in_path, out_path, pw);
}

static int cmdDecrypt(const char* path, const char* pw) {
    encInit();
    EncDecryptFileOut out = encDecryptFile(path, pw);

    if( out.r > 0 ) {
        fwrite(out.m, out.m_l, 1, stdout);
        if (CMD_PROMPT_ON && out.m[out.m_l - 1] != '\n') putchar('\n');
    }

    encDecryptFileOutClear(&out);

    return out.r;
}

static int cmdDecryptToFile(const char* in_path, const char* out_path, const char* pw) {
    encInit();
    EncDecryptFileOut out = encDecryptFile(in_path, pw);

    if ( out.r > 0 ) {
        FILE *f_out = fopen(out_path, "wb");

        fwrite(out.m, out.m_l, 1, f_out);

        fclose(f_out);
    }

    encDecryptFileOutClear(&out);

    return out.r;
}

static int cmdRun(int cmd, char** arg);
static void cmdPrompt() {
    if ( CMD_PROMPT_ON != 1 ) { // to make nesting prompts impossible
        CMD_PROMPT_ON = 1;
        MsdStrSplitOut out;
        out.sa = 0;
        do {
            printf("%s", CMD_PROMPT_STR);
            free(out.sa);
            out = msdStrSplit(msdIoGetStr());
            //todo: make quotations " " group input
            //for(int i = 0; i < out.sa_l; i++) msd_str_printchars(out.sa[i]);
        } while ( cmdRun(cmdParse(out.sa[0]), out.sa + 1) == 0 );
        CMD_PROMPT_ON = 0;
    }
}

static void cmdHelp(const char* arg_cmd) {
    if ( ! arg_cmd ) {
        int i;
        for(i = 0; i < CMD_ENUM_LENGTH; i++) printf("%s\n", CMD_STR_HELP[i]);
        printf("\n%s\n", CMD_HELP_SHELL_HISTORY_WARNING);
    } else {
        printf("%s\n", CMD_STR_HELP[cmdParse(arg_cmd)]);
    }
}

/* returns 0 if everything is successful, 1 if there is a need to exit the program */
static int cmdRun(int cmd, char** arg) {
    switch (cmd) {
        case CMD_EXIT:
            return 1;
        case CMD_ENCRYPT_MESSAGE:
            cmdEncryptMessage(arg[0], arg[1], arg[2]);
            break;
        case CMD_ENCRYPT_FILE:
            cmdEncryptFile(arg[0], arg[1], arg[2]);
            break;
        case CMD_DECRYPT:
            cmdDecrypt(arg[0], arg[1]);
            break;
        case CMD_DECRYPT_TO_FILE:
            cmdDecryptToFile(arg[0], arg[1], arg[2]);
            break;
        case CMD_PROMPT:
            cmdPrompt();
            break;
        case CMD_HELP:
            cmdHelp(arg[0]);
            break;
    }
    return 0;
}

#define CMD_ARGC 1

int cmdLine(int argc, char **argv) {
    return cmdRun(cmdParse(argv[CMD_ARGC]), argv + 2);
}
