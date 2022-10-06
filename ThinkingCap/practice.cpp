#include <iostream>
#include <string>
#include <stdlib.h>
#include "thinker.h"

using namespace std;

int main(void)
{
    ThinkingCap student;
    ThinkingCap fan;

    student.slots("Hello", "Goodbye");

    fan.slots("Go Cougars!", "Boo!");

    student.push_green();

    fan.push_green();

    student.push_red();

    return 0;
}