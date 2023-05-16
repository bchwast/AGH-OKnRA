//requires additional changes to the code to make it work

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string>
#include <iostream>

#define REPEATS 50000

static double gtod_ref_time_sec = 0.0;

/* Adapted from the bl2_clock() routine in the BLIS library */

double dclock()
{
    double the_time, norm_sec;
    struct timeval tv;
    gettimeofday( &tv, NULL );
    if ( gtod_ref_time_sec == 0.0 )
        gtod_ref_time_sec = ( double ) tv.tv_sec;
    norm_sec = ( double ) tv.tv_sec - gtod_ref_time_sec;
    the_time = norm_sec + tv.tv_usec * 1.0e-6;
    return the_time;
}



void remove_ctrl(std::string const &s, std::string &result){
    result.clear();
    result.reserve(s.length());
    for (size_t begin = 0, i = begin, end = s.length(); begin < end; begin = i + 1){
        for (i = begin; i < end; i++){
            if (s[i] < 0x20)
                break;
        }
        result.append(s, begin, i - begin);
    }
}


int main( int argc, const char* argv[] )
{
    int i,j,k,iret;
    double dtime;

    std::cout << "call to remove\n";

    std::string s;
    std::string result;

    std::string line;
    while (getline(std::cin, line)){
        s += line + "\n";
    }

    dtime = dclock();
    for (int i = 0; i < REPEATS; i++){
        remove_ctrl(s, result);
    }
    dtime = dclock() - dtime;

    std::cout << result << "\n";
    std::cout << "Time: " << dtime << "\n";
    fflush( stdout );

    return iret;
}

