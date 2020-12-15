/*
 * e_pw_w - encrypt_password_window
 */

static const int E_PW_OFF = GUI_OFF;

static const int E_PW_INPUT_WIDTH = 200;
static const int E_PW_INPUT_HEIGHT = 30;

static const int E_PW_WINDOW_WIDTH = E_PW_INPUT_WIDTH + 2 * E_PW_OFF;
static const int E_PW_WINDOW_HEIGHT = 7.5 * E_PW_OFF + 4 * E_PW_INPUT_HEIGHT;

void two_si_f (Fl_Widget* w, void* p);
void e_pw_w(Fl_Widget*, void* p)
{
    void** vpa = (void**) p;
    if ( gui_state == GUI_STATE_ENCRYPT_MESSAGE && ((Fl_Text_Buffer *) vpa[0])->length() == 0 ) {
        fl_message("%s", E_PW_EMPTY_MESSAGE_ERROR);
        return;
    }

    auto* pw_w = myWindowNew(E_PW_WINDOW_LABEL, E_PW_WINDOW_WIDTH, E_PW_WINDOW_HEIGHT);

    auto* input1_si = new Fl_Secret_Input(E_PW_OFF, 2 * E_PW_OFF, E_PW_INPUT_WIDTH, E_PW_INPUT_HEIGHT);
    auto* input2_si = new Fl_Secret_Input(E_PW_OFF, E_PW_INPUT_HEIGHT + 4 * E_PW_OFF, E_PW_INPUT_WIDTH, E_PW_INPUT_HEIGHT);

    auto* feedback_out = new Fl_Box(E_PW_OFF, 2 * E_PW_INPUT_HEIGHT + 5 * E_PW_OFF, E_PW_INPUT_WIDTH, E_PW_INPUT_HEIGHT);
    myBoxLabelCfg(feedback_out, E_PW_W_FEEDBACK_LABEL_BLANK);

    auto* next_btn = new Fl_Button(E_PW_OFF, 3 * E_PW_INPUT_HEIGHT + 6 * E_PW_OFF, E_PW_INPUT_WIDTH, E_PW_INPUT_HEIGHT);

    void** vpa1 = new void*[3] {input2_si, feedback_out, next_btn };
    mySecretInputCfg(input1_si, E_PW_INPUT1_LABEL, two_si_f, vpa1);

    void** vpa2 = new void*[3] {input1_si, feedback_out, next_btn };
    mySecretInputCfg(input2_si, E_PW_INPUT2_LABEL, two_si_f, vpa2);

    void** vpa3 = new void*[3] { input1_si, vpa[0], vpa[1] };
    myBtnCfg(next_btn, E_PW_NEXT_BTN_LABEL, FL_CTRL + 's', next_btn_f, vpa3);
    next_btn->deactivate();

    pw_w->show();
}

int pw_cmp (const char* pw1, const char* pw2);
void two_si_f (Fl_Widget* w, void* p)
{
    void** vpa = (void**)p;

    auto* input1_si = (Fl_Secret_Input*) w;
    auto* input2_si = (Fl_Secret_Input*) vpa[0];
    auto* feedback_out = (Fl_Box*) vpa[1];
    auto* next_btn = (Fl_Button*) vpa[2];

    feedback_out->hide(); // stops text from being put one on top of another
    switch( pw_cmp(input1_si->value(), input2_si->value()) ) {
        case 0:
            feedback_out->label(E_PW_FEEDBACK_LABEL_NO_MATCH);
            next_btn->deactivate();
            break;
        case 1:
            feedback_out->label(E_PW_W_FEEDBACK_LABEL_BLANK);
            next_btn->deactivate();
            break;
        default:
            feedback_out->label(E_PW_FEEDBACK_LABEL_MATCH);
            next_btn->activate();
            break;
    }

    feedback_out->show();
}

int pw_cmp (const char* pw1, const char* pw2)
{
    return strcmp(pw1, pw2) ? 0 : ( mdlStrIsBlank(pw2) ? 1 : 2 );
}
