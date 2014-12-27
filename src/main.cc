#include <stdio.h>
#include <libconfig.h++>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cairo.h>
#include <unistd.h>
#include <time.h>

using namespace std;
using namespace libconfig;

int pid=0;

int log(string logstr){
    printf("[dbt(%i)] %s\n",pid,logstr.c_str());
}

int setPic(string pic){
    if(system((string("gsettings set org.gnome.desktop.background picture-uri \"file://")+pic+string("\"")).c_str())>0){
        log(string("set backgrand to ")+pic+string(" faild."));
        return false;
    }else{
        log(string("set backgrand to ")+pic);
        return true;
    }
}

string timettostr(time_t t){
    tm* timetm=localtime(&t);
    string mh=string(":");
    string tmmin;
    if(timetm->tm_min<10){
        tmmin=string("0")+to_string(timetm->tm_min);
    }else{
        tmmin=to_string(timetm->tm_min);
    }
    return to_string(timetm->tm_hour)+mh+tmmin;
}

int main(){
    pid=getpid();
    Config cfg;

    cfg.readFile("dbt.conf");

    string mfname=cfg.lookup("bgr_main_pic");
    log(string("Use main pic: "+mfname));

    string tmp=cfg.lookup("tmp");
    unsigned int inv=cfg.lookup("interval");

    log(string("use interval ")+to_string(inv)+string("ms"));

    inv*=1000;

    string tmppath=cfg.lookup("tmp");

    cairo_surface_t * imgsf = cairo_image_surface_create_from_png(mfname.c_str());
    int width=cairo_image_surface_get_width(imgsf), height=cairo_image_surface_get_height(imgsf);

    log(string("start main loop.."));

    while(true){
        time_t timev;
        time(&timev);
        string time = timettostr(timev);
        log(string("loop - ")+time);
        cairo_surface_t *surface;
        cairo_t *cr;

        surface =
            cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
        cr = cairo_create (surface);
        cairo_set_source_surface(cr, imgsf, 0, 0);
        cairo_paint(cr);
        const Setting& root = cfg.getRoot();
        const Setting& bkg = root["bkgs"];
        int count = bkg.getLength();
        for(int i=0; i<count; i++){
            const Setting &pb = bkg[i];
            string type;
            pb.lookupValue("type",type);
            if(type==string("text")){
                string text, ff;
                int x, y;
                const Setting& col = pb["color"];
                double fs, r, g, b;
                pb.lookupValue("text",text);
                pb.lookupValue("ff", ff);
                pb.lookupValue("x", x);
                pb.lookupValue("y", y);
                pb.lookupValue("fs", fs);
                col.lookupValue("r", r);
                col.lookupValue("g", g);
                col.lookupValue("b", b);
                cairo_set_source_rgb (cr, r, g, b);
                cairo_select_font_face (cr, ff.c_str(),
                        CAIRO_FONT_SLANT_NORMAL,
                        CAIRO_FONT_WEIGHT_NORMAL);
                cairo_set_font_size (cr, fs);
                cairo_move_to (cr, x, y);
                cairo_show_text (cr, text.c_str());
            }else if(type==string("time")){
                string text, ff;
                int x, y;
                const Setting& col = pb["color"];
                double fs, r, g, b;
                int withsec;
                text=time;
                pb.lookupValue("ff", ff);
                pb.lookupValue("x", x);
                pb.lookupValue("y", y);
                pb.lookupValue("fs", fs);
                col.lookupValue("r", r);
                col.lookupValue("g", g);
                col.lookupValue("b", b);
                pb.lookupValue("withSec",withsec);
                cairo_set_source_rgb (cr, r, g, b);
                cairo_select_font_face (cr, ff.c_str(),
                        CAIRO_FONT_SLANT_NORMAL,
                        CAIRO_FONT_WEIGHT_NORMAL);
                cairo_set_font_size (cr, fs);
                cairo_move_to (cr, x, y);
                if(withsec>0){
                    text=text+string(":");
                    tm* timetm=localtime(&timev);
                    int sec=timetm->tm_sec;
                    if(sec<10){
                        text=text+string("0")+to_string(sec);
                    }else{
                        text=text+to_string(sec);
                    }
                }
                cairo_show_text (cr, text.c_str());
            }
        }
        const char* fname=(tmppath+"/dk.png").c_str();
        remove(fname);
        cairo_surface_write_to_png (surface, fname);
        fname=(tmppath+"/dk.png").c_str();
        setPic(fname);
        cairo_surface_destroy(surface);
        usleep(inv);
    }
    return 0;
}
