//
//  main.cpp
//  packager
//
//  Created by patrick parker on 19/03/2020.
//  Copyright © 2020 patrick parker. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "Packager.h"
void startPackager(){
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir("./debs");
    bool isOk = true;
    if (dpdf != NULL){
        while ((epdf = readdir(dpdf))){
            if(strcmp(epdf->d_name, ".DS_Store") == 0 || strcmp(epdf->d_name, "..") == 0 || strcmp(epdf->d_name, ".") == 0){
            } else {
                if(epdf->d_type == 8){
                    printf("[Packager]: found package: %s \n", epdf->d_name);
                } else {
                    printf("[Packager]: %s is of unknown file type\n", epdf->d_name);
                    isOk = false;
                }
            }
       }
    } else {
        isOk = false;
    }
    if(isOk){
        printf("[Packager]: Getting Packages control file\n");
        if(system("dpkg-scanpackages -m ./debs > Packages")){
            //dpkg spits out an error regardless :)
        } else {
            printf("[Packager]: Retreived information\n");
        }
        printf("[Packager]: Generating Packages\n");
        if(system("bzip2 Packages")){
            printf("[Packager]: There was an error zipping Packages\n");
        } else {
            printf("[Packager]: Finished\n");
        }
        return;
    } else {
        printf("[Packager]: There was an error, please ensure your file directories are correct\n");
    }
    closedir(dpdf);
}


int main(int argc, const char * argv[]) {
    printf("[Packager]: " ANSI_COLOR_BLUE  "Thanks for using Packager<3 \n" ANSI_COLOR_RESET);
    printf("[Packager]: " ANSI_COLOR_BLUE "Any problems, contact me via twitter @paddycodes\n" ANSI_COLOR_RESET);
    if(PLATFORM_NAME == "osx"){
        printf("[Packager]: detected OS " PLATFORM_NAME "\n");
        startPackager();
    } else {
        printf("[Packager]: Packager only currently supports OSX\n");
    }
    return 0;
}
