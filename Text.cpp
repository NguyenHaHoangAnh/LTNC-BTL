#include <iostream>
#include <string>
#include "game.h"

void getTime (int &time_val, Text &_time)
{
    int currentTime = max_time - time_val;
    if (currentTime >= 10)
        _time.text = to_string (currentTime);
    else
        _time.text = "0" + to_string (currentTime);
}
