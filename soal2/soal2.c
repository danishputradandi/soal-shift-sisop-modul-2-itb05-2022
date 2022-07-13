#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>

void unzip(char *namazip, char *tujuan) {
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id == 0) {
            char *argv[6] = {"unzip", namazip , "*.png", "-d", tujuan, NULL};
            execv("/usr/bin/unzip", argv);
            exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void CreateShiftDir(char *shift) {
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id == 0) {
            char *argv[3] = {"mkdir", "-p", shift};
            execv("/bin/mkdir", argv);
            exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void bikinFolder(char *nama) {
    char objek[100];
    sprintf(objek, "%s", nama);
    DIR *dir = opendir(nama);
    if (dir) {
        return;
    }
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id == 0) {
        char *argv[3] = {"mkdir", objek};
        execv("/bin/mkdir", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void mengcopy(char *folder, char *nama_awal, char *genre) {
    char sumber[100];
    sprintf(sumber, "%s", nama_awal);
    char tujuan[100];
    sprintf(tujuan, "%s/%s.png", folder, genre);
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id == 0) {
        char *argv[4] = { "cp", sumber, tujuan};
        execv("/bin/cp", argv);
        exit(EXIT_SUCCESS); 
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void menghapus(char *nama) {
    char objek[100];
    sprintf(objek, "%s/", nama);
    pid_t child_id;
    child_id = fork();
    if (child_id == 0) {
        char *argv[4] = {"rm","-rf", objek};
        execv("/bin/rm", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        wait(NULL);
    }
}

void data(char *folder, char *title, char *release) {
    char filename[50];
    sprintf(filename, "%s/data.txt", folder);
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id == 0) {
        FILE *fptr;
        fptr = fopen(filename, "a");
        fprintf(fptr, "nama : %s\nrilis : %s\n\n", title, release);
        fclose(fptr);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void checking(char *nama) {
    char nama_awal[100];
    sprintf(nama_awal, "%s", nama);
    DIR *dir = opendir(nama);
    if (dir) { menghapus(nama_awal);
    } else {
        char *pch;
        char *format[3];
        pch = strtok(nama, ";_");
        while (pch != NULL) {
            int i = 0;
            while (i < 3) {
                format[i] = pch;
                pch = strtok(NULL, ";_");
                i++;
            }
            char *title = format[0]; char *release = format[1]; char *genre = format[2];
            //Menghapus .png
            char *png;
            png = strstr(genre, ".png");
            if (png != NULL) {
                int new = png - genre;
               sprintf(genre, "%.*s", new, genre);
            }
            bikinFolder(genre);
            mengcopy(genre, nama_awal, title);
            data(genre, title, release);
        }
    }
    closedir(dir);
}

void copyzip(char *namazip, char *tujuan) {
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id == 0) {
            char *argv[5] = {"cp", namazip, tujuan, NULL};
            execv("/bin/cp", argv);
            exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

int main()
{
    CreateShiftDir("shift2");

    copyzip("drakor.zip", "shift2");

    chdir("/home/mutiararflnsh/shift2/");

    unzip("drakor.zip", "drakor");
    struct dirent *dp;
    DIR *dir = opendir("drakor");
    if (!dir) {
        exit(EXIT_FAILURE);
    }
    chdir("drakor");
    while (dp = readdir(dir)) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            checking(dp->d_name);
        }
    }
    return 0;
}