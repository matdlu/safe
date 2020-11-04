#ifndef CHEST_CLI_H
#define CHEST_CLI_H

#include <stdio.h>
#include <stdlib.h>
#include "msd_str.h"
#include "msd_io.h"
#include "enc.h"

enum CMD {
    CMD_NO_CMD,
    CMD_EXIT,
    CMD_ENCRYPT_MESSAGE,
    CMD_ENCRYPT_FILE,
    CMD_DECRYPT,
    CMD_DECRYPT_TO_FILE,
    CMD_PROMPT,
    CMD_HELP,
    CMD_ENUM_LENGTH
};

static const char* CMD_STR[CMD_ENUM_LENGTH] = {
        "",
        "exit",
        "encrypt_message",
        "encrypt_file",
        "decrypt",
        "decrypt_to_file",
        "prompt",
        "help",
};

static const char* CMD_STR_SHORT[CMD_ENUM_LENGTH] = {
        "",
        "q",
        "em",
        "ef",
        "d",
        "dtf",
        "p",
        "h",
};

static const char* CMD_STR_HELP[CMD_ENUM_LENGTH] = {
        "<nothing> - when no command is specified the gui is launched.",
        "q, exit - quit's program.",
        "em, encrypt_message <path> <message> <password> - encrypts a <message> using <password> then saves it to <path>.",
        "ef, encrypt_file <input path> <output path> <password> - loads a file on <input path> then encrypts it using <passsword> then saves it to <output path>.",
        "d, decrypt <path> <password> - loads a file on <path> then decrypts it using <password> then outputs content to stdout.",
        "dtf, decrypt_to_file <input path> <output path> <password> - loads a file on <input path> then decrypts it using <password> then saves it to <output path>.",
        "p, prompt - launches the interactive prompt.",
        "h, help <command> - displays description of all possible commands or of a single command if <command> parameter is specified.",
};

static const char* CMD_HELP_SHELL_HISTORY_WARNING = "WARNING!\nSome shells (e.g. bash) depending on the configuration will record executed commands including their parameters in a history file on the disk. This means that for example command: \"d file password\" will leak the password to the history file.\nWhen you have history enabled in your shell do not use command line parameters that contain your password. Instead use the program built-in GUI or prompt or disable history in your shell.";

// todo: error messages, handle encInit errors, read/write errors, out of memory errors

static const char* CMD_PROMPT_STR = ">";
static char CMD_PROMPT_ON = 0;

int cmdLine(int argc, char **argv);

void cmdPrompt(); //tmp

#endif //CHEST_CLI_H
