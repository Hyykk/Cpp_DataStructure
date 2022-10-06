#include <iostream>
#include <stdlib.h>
#include <string>
#include "thinker.h"
#include <string.h>
#include <assert.h>

using namespace std;

void ThinkingCap::slots(char new_green[], char new_red[]){
    assert(strlen(new_green)<50);
    assert(strlen(new_red)<50);
    strcpy(green_string, new_green);
    strcpy(red_string, new_red);
}

void ThinkingCap::push_green(){
    cout << green_string << endl;
}

void ThinkingCap::push_red(){
    cout << red_string << endl;
}