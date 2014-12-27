#include <stdio.h>
#include <libconfig.h>
#include <stdlib.h>

int main(){
    config_t cfg;
    config_setting_t *setting;
    const char *str;

    config_init(&cfg);

    if(! config_read_file(&cfg, "dbt.conf")){
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return 1;
    }

    if(config_lookup_string(&cfg, "bgr_main_pic", &str)){
        printf("%s\n", str);
    }

    // system("gsettings set org.gnome.desktop.background picture-uri \"file://%s\"");

    config_destroy(&cfg);
    return 0;
}
