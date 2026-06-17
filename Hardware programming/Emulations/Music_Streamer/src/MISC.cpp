#include "MISC.h"
#include "globals.h"

int constrain(int amt, int low, int high){
    if(amt > high) return high;
    if(amt < low) return low;
    return amt;
}