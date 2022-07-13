#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <json-c/json.h>

int run_gacha() {
    int primogems = 79000,cost = 160,round = 0, num_weap = 130, num_chara = 48, random;
    char temp[100], item_type[100];
    struct dirent *gacha;
    DIR *dir;
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json, *name, *rarity;
    
    do {
        round += 1;
        primogems -= 160;
        if (round % 2 == 1){
            dir = opendir("characters");
            strcpy(item_type, "characters");
            random = rand() % num_chara;
            while (random--){
                gacha = readdir(dir);
            }
            printf("%s\n", gacha->d_name);
            // fp = fopen(gacha->d_name, "r");
            // fread(buffer, 1024, 1, fp);
	        // fclose(fp);
            // parsed_json = json_tokener_parse(buffer);

	        // json_object_object_get_ex(parsed_json, "name", &name);
            // json_object_object_get_ex(parsed_json, "rarity", &rarity);

	        // printf("Name: %s\n", json_object_get_string(name));
	        // printf("Rarity: %d\n", json_object_get_int(rarity));
        }
        else if (round % 2 == 0){
	        dir = opendir("weapons");
            strcpy(item_type, "weapons");
            random = rand() % num_weap;
            while (random--){
                gacha = readdir(dir);
            }
            printf("%s\n", gacha->d_name);
        }
    }
    while (primogems > 159);
}

void dl_database() {
    pid_t child_1, child_2;
    child_1 = fork();
    child_2 = fork();
    int status;

    if (child_1 == 0 && child_2 > 0 ) {
	// this is child
		char *argv[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/u/0/uc?id=1xYYmsslb-9s8-4BDvosym7R4EmPi6BHp&export=download", "-O", "db_character.zip"};
		execv("/bin/wget", argv);
    } 
    else if (child_1 > 0 && child_2 == 0) {
		char *argv[] = {"wget","-q", "--no-check-certificate", "https://drive.google.com/u/0/uc?id=1XSkAqqjkNmzZ0AdIZQt_eWGOZ0eJyNlT&export=download", "-O", "db_weapon.zip"};
		execv("/bin/wget", argv);
    } 

    else if (child_1 < 0 && child_2 < 0 ) {
        printf ("Gagal mengunduh database :(");
		exit(EXIT_FAILURE);
        // Jika gagal membuat proses baru, program akan berhenti
	}
    else if (child_1 > 0 && child_2 > 0 ) {
        while ((wait(&status)) > 0);
        char *argv1[] = {"unzip","*.zip"};
	    execv("/bin/unzip", argv1);   
    }

}


void st_directory(){
    pid_t child_1 = fork();
    if (child_1 < 0) {
        printf ("Gagal membuat folder gacha_gacha :(");
		exit(EXIT_FAILURE);
        // Jika gagal membuat proses baru, program akan berhenti
	}
    if (child_1 == 0) {
	// this is child
		char *argv[] = {"mkdir", "-p", "gacha_gacha"};
		execv("/bin/mkdir", argv);
    }
}

void zp_directory(){
    pid_t child_1 = fork();
    if (child_1 < 0) {
        printf ("Gagal membuat zip folder gacha_gacha :(");
		exit(EXIT_FAILURE);
        // Jika gagal membuat proses baru, program akan berhenti
	}
    if (child_1 == 0) {
	// this is child
		char *argv[] = {"zip", "--password", "satuduatiga", "not_safe_for_wibu.zip", "gacha_gacha/*"};
		execv("/bin/zip", argv);
    }
}

int main() {
    int status;
    dl_database();
    st_directory();
    //run_gacha();
    //zp_directory();
}
