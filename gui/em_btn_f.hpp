/*
 * em_btn_f - encrypt_message_function
 */

static const int EM_EDITOR_WIDTH = 320;
static const int EM_EDITOR_HEIGHT = 280;

static const int EM_BTN_WIDTH = EM_EDITOR_WIDTH * 0.5;
static const int EM_BTN_HEIGHT = 30;

static const int EM_WINDOW_WIDTH = EM_EDITOR_WIDTH;
static const int EM_WINDOW_HEIGHT = EM_EDITOR_HEIGHT + EM_BTN_HEIGHT;

static void paste_btn_f(Fl_Widget*, void* p);
void em_btn_f(Fl_Widget*, void* p)
{
    gui_state = GUI_STATE_ENCRYPT_MESSAGE;

    Fl_Window* em_w = myWindowNew(EM_WINDOW_LABEL, EM_WINDOW_WIDTH, EM_WINDOW_HEIGHT);

    Fl_Text_Buffer* buf = new Fl_Text_Buffer();
    if ( p != 0 ) buf->text((char*)p);
    Fl_Text_Editor* editor = new Fl_Text_Editor(0, 0, EM_EDITOR_WIDTH, EM_EDITOR_HEIGHT);
    editor->buffer(buf);

    // todo: drag and drop to paste

    Fl_Button* paste_btn = new Fl_Button(0, EM_EDITOR_HEIGHT, EM_BTN_WIDTH, EM_BTN_HEIGHT);
    myBtnCfg(paste_btn, EM_PASTE_BTN_LABEL, FL_CTRL + 'p', paste_btn_f, editor);

    void** vpa = new void*[2] { buf, em_w };
    Fl_Button* encrypt_btn = new Fl_Button(EM_BTN_WIDTH, EM_EDITOR_HEIGHT, EM_BTN_WIDTH, EM_BTN_HEIGHT);
    myBtnCfg(encrypt_btn, EM_ENCRYPT_BTN_LABEL, FL_CTRL + 's', e_pw_w, vpa);

    em_w->show();
}

static void paste_btn_f(Fl_Widget*, void* p)
{
    Fl::paste(*(Fl_Text_Editor*) p, 1, Fl::clipboard_plain_text);
}
