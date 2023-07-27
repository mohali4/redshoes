#include <iostream>
#include "redshoes.h"
#include "keyboard.h"
#include "form.h"
#include "cli.h"
#include "redsocks.h"
#include "editor.h"
#include "iptables.h"

//Form* Form::Showing;

std::string message_text;
Form* keyboard_focus;
void focus_on_form(Form* the_form){
    keyboard_focus = the_form;
}

void keyHandler (std::string key){
    if(key==Right_key){
    }else if(key==Left_key){
    }else if(key==Down_key){
        keyboard_focus->Down();
    }else if(key==Up_key) {
        keyboard_focus->Up();
    }else if(key==Enter_key){
        keyboard_focus->focused()->click();
    }
}

slash_progress_letter redsocks_anim(200);
std::string redsocks_status_header (){
    std::string body = "";
    body += "Redsocks";
    if (not status_redsocks){
        body += " is off ";
        redsocks_anim.set(".");

    }else{
        body += " is running ";
        redsocks_anim.start();
    }
    body += *(redsocks_anim.letter);
    if (not status_redsocks){
        body += "    ";
    }

    return body ;
}

std::string redsocks_button (){
    std::string body = "";
    if (status_redsocks){
        body += "Stop  ";
    }else{
        body += "Start";
    }
    return body;
}

void redsocks_button_click (){
    if (status_redsocks){
        stop_redsocks();
    }else{
        start_redsocks();
    }
}


std::string message_bar(){
    return message_text;
}

void message_set(std::string text){
    message_text = text;
}

int inter_page_dyn_sizeX(){
    int inter_page = size_width()/2;
    return inter_page;
}

void redsocks_configure_click(){
    system_sleep = true;
    run_vim(REDSOCKS_CONFIG_FILE_PATH);
    system_sleep = false;
}

dot_progress_letter iptable_on_anim(500,5,"*"," ");

dot_progress_letter iptable_off_anim(500,5," ","-");

std::string iptables_stat_body(){
    std::string result = "tunnel is ";
    if ( tunnel_status ){
        result += "on <" + *(iptable_on_anim.letter) + ">";
    }else{
        result += "off <" + *(iptable_off_anim.letter) + ">";
    }
    result += "  ";
    return result;
}
//int startUp(){
Form* main_form = new Form(0,0,&size_width,10);
LogZone* main_log = new LogZone(&inter_page_dyn_sizeX,0,&size_width,&size_height);
FormObject* redsocks_stat_FO = new FormObject(&redsocks_status_header,true,"left",0);
FormObject* redsocks_button_FO = new FormObject(&redsocks_button,&redsocks_button_click,false,"left",1);
FormObject* message_bar_FO = new FormObject(&message_bar,true,"left",5);
FormObject* redsocks_configure_FO = new FormObject("Configure",&redsocks_configure_click,false,"left",1);
FormObject* iptables_stat_FO = new FormObject(&iptables_stat_body,true,"left",0);
key_handler keyHandlerObject(&keyHandler);
//}