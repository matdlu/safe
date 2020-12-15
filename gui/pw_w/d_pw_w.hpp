/*
 * d_pw_w - decrypt_password_window
 */

static const int D_PW_OFF = GUI_OFF;

static const int D_PW_INPUT_WIDTH = 200;
static const int D_PW_INPUT_HEIGHT = 30;

static const int D_PW_WINDOW_WIDTH = D_PW_INPUT_WIDTH + 2 * D_PW_OFF;
static const int D_PW_WINDOW_HEIGHT = 8.5 * D_PW_OFF + 2 * D_PW_INPUT_HEIGHT;

void one_si_f (Fl_Widget* w, void* p);
void d_pw_w(Fl_Widget*, void* p)
{
    auto* pw_w = myWindowNew(D_PW_WINDOW_LABEL, D_PW_WINDOW_WIDTH, D_PW_WINDOW_HEIGHT);

    auto* file_box = new Fl_Output(D_PW_OFF, 2 * D_PW_OFF, D_PW_INPUT_WIDTH, D_PW_INPUT_HEIGHT);
    file_box->label(D_PW_FILE_LABEL);
    file_box->align(FL_ALIGN_TOP_LEFT);
    file_box->box(FL_FRAME_BOX);
    file_box->value((char*) p);
    file_box->position(file_box->size());

    auto* input_si = new Fl_Secret_Input(D_PW_OFF, 4 * D_PW_OFF + D_PW_INPUT_HEIGHT, D_PW_INPUT_WIDTH, D_PW_INPUT_HEIGHT);

    auto* next_btn = new Fl_Button(D_PW_OFF, 5.5 * D_PW_OFF + 2 * D_PW_INPUT_HEIGHT, D_PW_INPUT_WIDTH, D_PW_INPUT_HEIGHT);
    mySecretInputCfg(input_si, D_PW_INPUT_LABEL, one_si_f, next_btn);

    void** vpa = new void*[2] { input_si, p };
    myBtnCfg(next_btn, D_PW_NEXT_BTN_LABEL, FL_CTRL + 'd', next_btn_f, vpa);
    next_btn->deactivate();

    pw_w->show();
}

void one_si_f (Fl_Widget* w, void* p)
{
    auto* next_btn = (Fl_Button*) p;
    if ( strlen( ((Fl_Secret_Input*) w)->value() ) <= 0 )
        next_btn->deactivate();
    else
        next_btn->activate();
}
