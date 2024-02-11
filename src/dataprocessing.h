#pragma once

#include <iostream>
#include <map> 
#include <unordered_map>

/**
 * The Class that stores the static member function that will read serial data, and then
 * update the serialValues map with said data for the GUI's components to draw accurately. 
*/
class SerialRead {
    private: 
    public: 
        /**
         * Stores the values that are read from RATS. 
        */
        static std::unordered_map<std::string, float> serialValues;
        /**
         * Updates the serialValues map by reading in data. 
        */
        static void updateSerialValues(); 

}; 