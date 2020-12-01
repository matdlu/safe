#include "gui.hpp"
#include "logo.xpm"

static const char* MAIN_WINDOW_LABEL = "Safe Crypto Tool";
static const ui MAIN_OFF = 20;

static const ui MAIN_BTN_WIDTH = 180 - 2 * MAIN_OFF;
static const ui MAIN_BTN_HEIGHT = 120 - 2 * MAIN_OFF;

static const ui MAIN_WINDOW_WIDTH = 2 * MAIN_BTN_WIDTH + 3 * MAIN_OFF;
static const ui MAIN_WINDOW_HEIGHT = 2 * MAIN_BTN_HEIGHT + 3 * MAIN_OFF;

static const char* DECRYPT_BTN_LABEL = "Decrypt";
static const char* ENCMESG_BTN_LABEL = "Encrypt message";
static const char* ENCFILE_BTN_LABEL = "Encrypt file";

void decrypt_btn_f(Fl_Widget* w, void*);
void encmesg_btn_f(Fl_Widget* w, void*);
void encfile_btn_f(Fl_Widget* w, void*);

extern "C" int main_window(int argc, char **argv) {
    Fl_Window *main_window = new Fl_Window(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    main_window->label(MAIN_WINDOW_LABEL);
    main_window->resizable(main_window);

    Fl_Button *decrypt_btn = new Fl_Button(MAIN_OFF, MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    decrypt_btn->label(DECRYPT_BTN_LABEL);
    decrypt_btn->callback(decrypt_btn_f);
    decrypt_btn->shortcut('d');

    Fl_Box  *logo_box = new Fl_Box(MAIN_BTN_WIDTH + 2 * MAIN_OFF, MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    Fl_Pixmap *pix = new Fl_Pixmap(logo);
    logo_box->image(pix);

    Fl_Button *encmesg_btn = new Fl_Button(MAIN_OFF, MAIN_BTN_HEIGHT + 2 * MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    encmesg_btn->label(ENCMESG_BTN_LABEL);
    encmesg_btn->callback(encmesg_btn_f);
    encmesg_btn->shortcut('m');

    Fl_Button *encfile_btn = new Fl_Button(MAIN_BTN_WIDTH + 2 * MAIN_OFF, MAIN_BTN_HEIGHT + 2 * MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    encfile_btn->label(ENCFILE_BTN_LABEL);
    encfile_btn->callback(encfile_btn_f);
    encfile_btn->shortcut('f');

    main_window->show(argc, argv);
    return Fl::run();
}

static const char* DECRYPT_WINDOW_LABEL = "Safe Crypto Tool - Decrypt";

void decrypt_btn_f(Fl_Widget*, void*) {
    Fl_Window *decrypt_window = new Fl_Window(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    decrypt_window->label(DECRYPT_WINDOW_LABEL);

    // todo: detect file or message

    // todo: drag and drop and file picker

    decrypt_window->show();
}

static const char* ENCMESG_WINDOW_LABEL = "Safe Crypto Tool - Encrypt message";

static const int ENCMESG_EDITOR_WIDTH = 320;
static const ui ENCMESG_EDITOR_HEIGHT = 280;

static const ui ENCMESG_BTN_WIDTH = ENCMESG_EDITOR_WIDTH * 0.5;
static const ui ENCMESG_BTN_HEIGHT = 30;

static const ui ENCMESG_WINDOW_WIDTH = ENCMESG_EDITOR_WIDTH;
static const ui ENCFILE_WINDOW_HEIGHT = ENCMESG_EDITOR_HEIGHT + ENCMESG_BTN_HEIGHT;

void btn_paste_f(Fl_Widget*, void* vp_editor);

void btn_encrypt_f(Fl_Widget*, void*);

struct Btn_Save_arg {
    Fl_Window* encmesg_window;
    Fl_Text_Buffer* buf;
};

void encmesg_btn_f(Fl_Widget*, void*) {
    Fl_Window *encmesg_window = new Fl_Window(ENCMESG_WINDOW_WIDTH, ENCFILE_WINDOW_HEIGHT);
    encmesg_window->label(ENCMESG_WINDOW_LABEL);
    encmesg_window->resizable(encmesg_window);

    Fl_Text_Buffer *buf = new Fl_Text_Buffer();
    Fl_Text_Editor *editor = new Fl_Text_Editor(0, 0, ENCMESG_EDITOR_WIDTH, ENCMESG_EDITOR_HEIGHT);
    editor->buffer(buf);
    // todo: drag and drop to paste

    Fl_Button *btn_paste = new Fl_Button(0, ENCMESG_EDITOR_HEIGHT, ENCMESG_BTN_WIDTH, ENCMESG_BTN_HEIGHT);
    btn_paste->label("Paste");
    btn_paste->shortcut(FL_CTRL + 'p');
    btn_paste->callback(btn_paste_f, editor);

    Btn_Save_arg *btn_save_arg = new Btn_Save_arg;
    btn_save_arg->encmesg_window = encmesg_window;
    btn_save_arg->buf = buf;

    Fl_Button *btn_encrypt = new Fl_Button(ENCMESG_BTN_WIDTH, ENCMESG_EDITOR_HEIGHT, ENCMESG_BTN_WIDTH, ENCMESG_BTN_HEIGHT);
    btn_encrypt->label("Encrypt");
    btn_encrypt->shortcut(FL_CTRL + 's');
    btn_encrypt->callback(btn_encrypt_f, btn_save_arg);

    encmesg_window->show();
}

void btn_paste_f(Fl_Widget*, void* vp_editor) {
    Fl::paste(*(Fl_Text_Editor*) vp_editor, 1, Fl::clipboard_plain_text);
}

static const ui PASSWORD_OFF = 20;

static const ui PASSWORD_INPUT_WIDTH = 200;
static const ui PASSWORD_INPUT_HEIGHT = 30;

static const ui PASSWORD_WINDOW_WIDTH = PASSWORD_INPUT_WIDTH + 2*PASSWORD_OFF;
static const ui PASSWORD_WINDOW_HEIGHT = 7.5*PASSWORD_OFF + 4*PASSWORD_INPUT_HEIGHT;

static const char* PASSWORD_BTN_SAVE_LABEL = "Save";
static const char* PASSWORD_FEEDBACK_NO_MATCH_LABEL = "Passwords do not match. ✗";
static const char* PASSWORD_FEEDBACK_BLANK_LABEL = "Password can't be blank. ✗";
static const char* PASSWORD_FEEDBACK_MATCH_LABEL = "Passwords match. ✓";

void btn_save_f(Fl_Widget*, void*);

void password_input_f(Fl_Widget*, void*);

int check_password(const char* pw1, const char* pw2);

struct Password_Input_arg {
    Fl_Secret_Input *in2;
    Fl_Output *password_feedback;
    Fl_Button *btn_save;
};

struct Btn_Save_arg_Secret_Input {
    Btn_Save_arg* btn_save_arg;
    Fl_Secret_Input* in1;
};

static const char* ERROR_EMPTY_MESSAGE = "Cannot encrypt an empty message!";

void btn_encrypt_f(Fl_Widget*, void* vp_arg) {
    Btn_Save_arg* btn_save_arg = (Btn_Save_arg*)vp_arg;
    if ( btn_save_arg->buf->length() == 0 ) {
        fl_message("%s", ERROR_EMPTY_MESSAGE);
        return;
    }

    Fl_Window *password_window = new Fl_Window(PASSWORD_WINDOW_WIDTH,PASSWORD_WINDOW_HEIGHT);
    password_window->label("Safe Crypto Tool - Encrypt message");
    password_window->resizable(password_window);

    Fl_Secret_Input *in1 = new Fl_Secret_Input(PASSWORD_OFF, 2*PASSWORD_OFF, PASSWORD_INPUT_WIDTH, PASSWORD_INPUT_HEIGHT);
    Fl_Secret_Input *in2 = new Fl_Secret_Input(PASSWORD_OFF, PASSWORD_INPUT_HEIGHT + 4*PASSWORD_OFF, PASSWORD_INPUT_WIDTH, PASSWORD_INPUT_HEIGHT);
    Fl_Output *password_feedback = new Fl_Output(PASSWORD_OFF, 2*PASSWORD_INPUT_HEIGHT + 5*PASSWORD_OFF, PASSWORD_INPUT_WIDTH, PASSWORD_INPUT_HEIGHT);
    Fl_Button *btn_save = new Fl_Button(PASSWORD_OFF, 3*PASSWORD_INPUT_HEIGHT + 6*PASSWORD_OFF, PASSWORD_INPUT_WIDTH, PASSWORD_INPUT_HEIGHT);

    Password_Input_arg *in1_arg = new Password_Input_arg;
    in1_arg->in2 = in2;
    in1_arg->password_feedback = password_feedback;
    in1_arg->btn_save = btn_save;

    in1->label("Password for the file:");
    in1->align(FL_ALIGN_TOP_LEFT);
    in1->when(FL_WHEN_CHANGED);
    in1->callback(password_input_f, in1_arg);

    Password_Input_arg *in2_arg = new Password_Input_arg;
    in2_arg->in2 = in1;
    in2_arg->password_feedback = password_feedback;
    in2_arg->btn_save = btn_save;

    in2->label("Confirm the password:");
    in2->align(FL_ALIGN_TOP_LEFT);
    in2->when(FL_WHEN_CHANGED);
    in2->callback(password_input_f, in2_arg);

    password_feedback->value(PASSWORD_FEEDBACK_BLANK_LABEL);
    // simulate label
    password_feedback->box(FL_NO_BOX);
    password_feedback->set_output();

    Btn_Save_arg_Secret_Input* arg = new Btn_Save_arg_Secret_Input;
    arg->btn_save_arg = btn_save_arg;
    arg->in1 = in1;

    btn_save->label(PASSWORD_BTN_SAVE_LABEL);
    btn_save->shortcut(FL_CTRL + 's');
    btn_save->callback(btn_save_f, arg);
    btn_save->deactivate();

    password_window->show();
};

void password_input_f(Fl_Widget* w_in1, void* vp_arg) {
    Password_Input_arg* arg = (Password_Input_arg*) vp_arg;

    Fl_Secret_Input *in1 = (Fl_Secret_Input*) w_in1;
    Fl_Secret_Input *in2 = arg->in2;

    Fl_Output *password_feedback = arg->password_feedback;
    Fl_Button *btn_save = arg->btn_save;

    password_feedback->hide(); // stops text from being put one on top of another
    switch( check_password(in1->value(), in2->value()) ) {
        case 0:
            password_feedback->value(PASSWORD_FEEDBACK_NO_MATCH_LABEL);
            btn_save->deactivate();
            break;
        case 1:
            password_feedback->value(PASSWORD_FEEDBACK_BLANK_LABEL);
            btn_save->deactivate();
            break;
        default:
            password_feedback->value(PASSWORD_FEEDBACK_MATCH_LABEL);
            btn_save->activate();
            break;
    }

    password_feedback->show();
}

int check_password(const char* pw1, const char* pw2) {
    int ret = strcmp(pw1, pw2);
    if ( ret ) {
        return 0;
    } else if ( mdlStrIsBlank(pw2) ) {
        return 1;
    } else {
        return 2;
    }
}

static const char* EXT = ".enc";
static const char* WRITE_ERROR = "Write error. Check directory permissions and available space.";

void btn_save_f(Fl_Widget* w, void* vp_arg) {
    Btn_Save_arg_Secret_Input* both = (Btn_Save_arg_Secret_Input*) vp_arg;
    Btn_Save_arg* arg = both->btn_save_arg;
    Fl_Secret_Input* in1 = both->in1;

    Fl_Text_Buffer* buf = arg->buf;

    Fl_Native_File_Chooser *fc = new Fl_Native_File_Chooser(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
    fc->filter(EXT);
    fc->show();
    //buf->savefile(msdStrCatNew(fc->filename(), EXT));
    char* path = mdlStrCatNew(fc->filename(), EXT); // filename() returns path
    printf("%s\n", buf->text());
    printf("%s\n", path);
    printf("%s\n", in1->value());


    // todo: perform verification whether the content of the file saved are the same as the file in memory

    // todo: overwrite memory of objects which contained sensitive information (children of password_window, buf) with zeroes

    if ( encEncryptMessage(path, buf->text(), in1->value()) ) {
        delete w->parent();
        delete arg->encmesg_window;
    } else {
        fl_message("%s", WRITE_ERROR);
    }

    // todo: display encrypted content in a window to copy then pase
}

static const char* ENCFILE_WINDOW_LABEL = "Safe Crypto Tool - Encrypt file";

void encfile_btn_f(Fl_Widget*, void*) {
    Fl_Window *encfile_window = new Fl_Window(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    encfile_window->label(ENCFILE_WINDOW_LABEL);

    // todo: text editor

    // todo: paste button
    // todo: save button file picker to choose where to save file

    encfile_window->show();
}
