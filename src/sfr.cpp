#include "sfr.h"

namespace sfr {
    SerialRead* serialRead = new SerialRead(); 

    void cleaner(){
        delete serialRead; 
    }
}