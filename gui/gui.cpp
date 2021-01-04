#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Output.H>
#include <iostream>
extern "C" {
    #include "../mdl_str.h"
    #include "../mdl_io.h"
    #include "../enc.h"
};

#include "../config.h"
#include "loc.hpp"

#include "my.hpp"

#include "logo.xpm"

static const char* EXT = ".enc";
#ifdef __WIN_32__
static const char* TXT_EXT = ".txt";
#else
static const char* TXT_EXT = "";
#endif

enum GuiState {
    GUI_STATE_ENCRYPT_FILE,
    GUI_STATE_ENCRYPT_MESSAGE,
    GUI_STATE_DECRYPT,
    GUI_STATE_WRITE_FILE,
};
static GuiState gui_state;

static const int GUI_OFF = 20;

static const int MAIN_OFF = GUI_OFF;

static const int MAIN_BTN_WIDTH = 180 - 2 * MAIN_OFF;
static const int MAIN_BTN_HEIGHT = 120 - 2 * MAIN_OFF;

static const int MAIN_WINDOW_WIDTH = 2 * MAIN_BTN_WIDTH + 3 * MAIN_OFF;
static const int MAIN_WINDOW_HEIGHT = 2 * MAIN_BTN_HEIGHT + 3 * MAIN_OFF;

void d_btn_f(Fl_Widget*, void*);
void ef_btn_f(Fl_Widget*, void*);
void em_btn_f(Fl_Widget*, void*);
extern "C" int main_window(int argc, char **argv)
{
    Fl_Window* main_window = myWindowNew(MAIN_WINDOW_LABEL, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    Fl_Button *d_btn = new Fl_Button(MAIN_OFF, MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    myBtnCfg(d_btn, D_BTN_LABEL, 'd', d_btn_f, 0);

    Fl_Box  *logo_box = new Fl_Box(MAIN_BTN_WIDTH + 2 * MAIN_OFF, MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    Fl_Pixmap *pix = new Fl_Pixmap(logo);
    logo_box->image(pix);

    Fl_Button *em_btn = new Fl_Button(MAIN_OFF, MAIN_BTN_HEIGHT + 2 * MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    myBtnCfg(em_btn, EM_BTN_LABEL, 'm', em_btn_f, 0);

    Fl_Button *ef_btn = new Fl_Button(MAIN_BTN_WIDTH + 2 * MAIN_OFF, MAIN_BTN_HEIGHT + 2 * MAIN_OFF, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT);
    myBtnCfg(ef_btn, EF_BTN_LABEL, 'f', ef_btn_f, 0);

    main_window->show(argc, argv);

    return Fl::run();
}

#include "pw_w/next_btn_f.hpp"
#include "pw_w/e_pw_w.hpp"
#include "pw_w/d_pw_w.hpp"
#include "pf_w.hpp" // pick file window

/*
 * d - decrypt
 */
void d_btn_f(Fl_Widget*, void*) { // decrypt_button_function
    gui_state = GUI_STATE_DECRYPT;
    pf_w(D_WINDOW_LABEL);
}

/*
 * ef - encrypt file
 */
void ef_btn_f(Fl_Widget*, void*) { // encrypt_file_button_function
    gui_state = GUI_STATE_ENCRYPT_FILE;
    pf_w(EF_WINDOW_LABEL);
}

/*
 * em - encrypt message
 */
#include "em_btn_f.hpp" // encrypt_message_button_function
