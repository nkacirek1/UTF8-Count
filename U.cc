//Nicole Kacirek
//4.24.17
//CS253

#include "U.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

//Defualt Constructor
U::U() : mapIndex(0), size_(0){}

//Copy Constructor
U::U(const U& rhs) : mapIndex(rhs.mapIndex), size_(rhs.size_){
    UTF8 = rhs.UTF8;
    cp = rhs.cp;
}

//Filename constructor
U::U(const string& filename) : mapIndex(0), size_(0){
    ifstream file(filename);
    if(!file){
        throw (string)"The data file cannot be read\n";
    }
    else{
        bool workingOnChar;
        char c;
        while(file.get(c)){
            workingOnChar = true;
            string toBeChecked;
            string formatted = "";
            int byte = c;
            //calls help function to see how long the unicode will be
            int numBytes = howLong(byte);
            
            while(workingOnChar){
                ostringstream oss;
                int maskGen = 0x3F;
                
                if(numBytes == 1){
                    formatted += byte;
                    //adds the character to the map of all the characters and increments the index and size
                    cp[mapIndex] = byte;
                    UTF8[mapIndex] = formatted;
                    mapIndex++;
                    size_++;
                    workingOnChar = false;
                }
                else if(numBytes == 2){
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask2B = 0x1F;
                    int resultB1 = byte & mask2B;
                    
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;

                        int hexRep = 0x000;
                        hexRep = hexRep | resultB2;
                        int temp = resultB1 << 6;
                        hexRep = hexRep | temp;

                        //adds the character to the map of all the characters and increments the index and size
                        cp[mapIndex] = hexRep;
                        UTF8[mapIndex] = formatted;
                        mapIndex++;
                        size_++;
                        workingOnChar = false;
                    }
                    else throw (string)"Error: not a continuation byte; improperly formatted character"; 
                }
                else if(numBytes == 3){
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask3B = 0x0F;
                    int resultB1 = byte & mask3B;
                        
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;
                        
                        file.get(c);
                        byte = c;
                        if(continueB(byte)){
                            formatted += byte;
                            int resultB3 = byte & maskGen;
                            
                            int hexRep = 0x0000;
                            hexRep = hexRep | resultB3;
                            int temp = resultB2 << 6;
                            hexRep = hexRep | temp;
                            temp = resultB1 << 12;
                            hexRep = hexRep | temp;

                            //adds the character to the map of all the characters and increments the index and size
                            cp[mapIndex] = hexRep;
                            UTF8[mapIndex] = formatted;
                            mapIndex++;
                            size_++;
                            workingOnChar = false;
                        }
                        else throw (string)"Error: not a continuation byte; improperly formatted character";
                    }
                    else throw (string)"Error: not a continuation byte; improperly formatted character";
                }
                else{
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask4B = 0x07;
                    int resultB1 = byte & mask4B;
                        
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;

                        file.get(c);
                        byte = c;
                        if(continueB(byte)){
                            formatted += byte;
                            int resultB3 = byte & maskGen;

                            file.get(c);
                            byte = c;
                            if(continueB(byte)){
                                formatted += byte;
                                int resultB4 = byte & maskGen;

                                int hexRep = 0x000000;
                                hexRep = hexRep | resultB4;
                                int temp = resultB3 << 6;
                                hexRep = hexRep | temp;
                                temp = resultB2 << 12;
                                hexRep = hexRep | temp;
                                temp = resultB1 << 18;
                                hexRep = hexRep | temp;

                                //adds the character to the map of all the characters and increments the index and size
                                cp[mapIndex] = hexRep;
                                UTF8[mapIndex] = formatted;
                                mapIndex++;
                                size_++; 
                                workingOnChar = false;
                            }
                            else throw (string)"Error: not a continuation byte; improperly formatted character"; 
                        }
                        else throw (string)"Error: not a continuation byte; improperly formatted character";
                    }
                    else throw (string)"Error: not a continuation byte; improperly formatted character";
                }
            }   
        }
    }
}
    
//Assignment Operator
U& U::operator=(const U &rhs){
    mapIndex = rhs.mapIndex;
    size_ = rhs.size_;
    UTF8 = rhs.UTF8;
    cp = rhs.cp;
    return *this;
}

//Assignment Operator - u=string
U& U::operator=(const string &s){
    //clears all the previous u variables - fresh u
    clear();
    append(s);
    return *this;
}
    
//Destructor
U::~U(){}

//readfile
void U::readfile(const string& filename){
    ifstream file(filename);
    if(!file){
        throw (string)"The data file cannot be read\n";
    }
    else{
        bool workingOnChar;
        char c;
        while(file.get(c)){
            workingOnChar = true;
            string toBeChecked;
            string formatted = "";
            int byte = c;
            //calls help function to see how long the unicode will be
            int numBytes = howLong(byte);
            
            while(workingOnChar){
                ostringstream oss;
                int maskGen = 0x3F;
                
                if(numBytes == 1){
                    formatted += byte;
                    //adds the character to the map of all the characters and increments the index and size
                    cp[mapIndex] = byte;
                    UTF8[mapIndex] = formatted;
                    mapIndex++;
                    size_++;
                    workingOnChar = false;
                }
                else if(numBytes == 2){
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask2B = 0x1F;
                    int resultB1 = byte & mask2B;
                    
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;

                        int hexRep = 0x000;
                        hexRep = hexRep | resultB2;
                        int temp = resultB1 << 6;
                        hexRep = hexRep | temp;

                        //adds the character to the map of all the characters and increments the index and size
                        cp[mapIndex] = hexRep;
                        UTF8[mapIndex] = formatted;
                        mapIndex++;
                        size_++;
                        workingOnChar = false;
                    }
                    else throw (string)"Error: not a continuation byte; improperly formatted character"; 
                }
                else if(numBytes == 3){
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask3B = 0x0F;
                    int resultB1 = byte & mask3B;
                        
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;
                        
                        file.get(c);
                        byte = c;
                        if(continueB(byte)){
                            formatted += byte;
                            int resultB3 = byte & maskGen;
                            
                            int hexRep = 0x0000;
                            hexRep = hexRep | resultB3;
                            int temp = resultB2 << 6;
                            hexRep = hexRep | temp;
                            temp = resultB1 << 12;
                            hexRep = hexRep | temp;

                            //adds the character to the map of all the characters and increments the index and size
                            cp[mapIndex] = hexRep;
                            UTF8[mapIndex] = formatted;
                            mapIndex++;
                            size_++;
                            workingOnChar = false;
                        }
                        else throw (string)"Error: not a continuation byte; improperly formatted character";
                    }
                    else throw (string)"Error: not a continuation byte; improperly formatted character";
                }
                else{
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask4B = 0x07;
                    int resultB1 = byte & mask4B;
                        
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;

                        file.get(c);
                        byte = c;
                        if(continueB(byte)){
                            formatted += byte;
                            int resultB3 = byte & maskGen;

                            file.get(c);
                            byte = c;
                            if(continueB(byte)){
                                formatted += byte;
                                int resultB4 = byte & maskGen;

                                int hexRep = 0x000000;
                                hexRep = hexRep | resultB4;
                                int temp = resultB3 << 6;
                                hexRep = hexRep | temp;
                                temp = resultB2 << 12;
                                hexRep = hexRep | temp;
                                temp = resultB1 << 18;
                                hexRep = hexRep | temp;

                                //adds the character to the map of all the characters and increments the index and size
                                cp[mapIndex] = hexRep;
                                UTF8[mapIndex] = formatted;
                                mapIndex++;
                                size_++; 
                                workingOnChar = false;
                            }
                            else throw (string)"Error: not a continuation byte; improperly formatted character"; 
                        }
                        else throw (string)"Error: not a continuation byte; improperly formatted character";
                    }
                    else throw (string)"Error: not a continuation byte; improperly formatted character";
                }
            }   
        }
    }              
}

//append
void U::append(const string& literalData){
    istringstream file(literalData);
    if(!file){
        throw (string)"The data file cannot be read\n";
    }
    else{
        bool workingOnChar;
        char c;
        while(file.get(c)){
            workingOnChar = true;
            string toBeChecked;
            string formatted = "";
            int byte = c;
            //calls help function to see how long the unicode will be
            int numBytes = howLong(byte);
            
            while(workingOnChar){
                ostringstream oss;
                int maskGen = 0x3F;
                
                if(numBytes == 1){
                    formatted += byte;
                    //adds the character to the map of all the characters and increments the index and size
                    cp[mapIndex] = byte;
                    UTF8[mapIndex] = formatted;
                    mapIndex++;
                    size_++;
                    workingOnChar = false;
                }
                else if(numBytes == 2){
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask2B = 0x1F;
                    int resultB1 = byte & mask2B;
                    
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;

                        int hexRep = 0x000;
                        hexRep = hexRep | resultB2;
                        int temp = resultB1 << 6;
                        hexRep = hexRep | temp;

                        //adds the character to the map of all the characters and increments the index and size
                        cp[mapIndex] = hexRep;
                        UTF8[mapIndex] = formatted;
                        mapIndex++;
                        size_++;
                        workingOnChar = false;
                    }
                    else throw (string)"Error2: 2nd byte not a continuation byte; improperly formatted character"; 
                }
                else if(numBytes == 3){
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask3B = 0x0F;
                    int resultB1 = byte & mask3B;
                        
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;
                        
                        file.get(c);
                        byte = c;
                        if(continueB(byte)){
                            formatted += byte;
                            int resultB3 = byte & maskGen;
                            
                            int hexRep = 0x0000;
                            hexRep = hexRep | resultB3;
                            int temp = resultB2 << 6;
                            hexRep = hexRep | temp;
                            temp = resultB1 << 12;
                            hexRep = hexRep | temp;

                            //adds the character to the map of all the characters and increments the index and size
                            cp[mapIndex] = hexRep;
                            UTF8[mapIndex] = formatted;
                            mapIndex++;
                            size_++;
                            workingOnChar = false;
                        }
                        else throw (string)"Error3: 3rd byte not a continuation byte; improperly formatted character";
                    }
                    else throw (string)"Error3: 2nd byte not a continuation byte; improperly formatted character";
                }
                else{
                    //need to pull out the specific bits
                    formatted += byte;
                    int mask4B = 0x07;
                    int resultB1 = byte & mask4B;
                        
                    file.get(c);
                    byte = c;
                    if(continueB(byte)){
                        formatted += byte;
                        int resultB2 = byte & maskGen;

                        file.get(c);
                        byte = c;
                        if(continueB(byte)){
                            formatted += byte;
                            int resultB3 = byte & maskGen;

                            file.get(c);
                            byte = c;
                            if(continueB(byte)){
                                formatted += byte;
                                int resultB4 = byte & maskGen;

                                int hexRep = 0x000000;
                                hexRep = hexRep | resultB4;
                                int temp = resultB3 << 6;
                                hexRep = hexRep | temp;
                                temp = resultB2 << 12;
                                hexRep = hexRep | temp;
                                temp = resultB1 << 18;
                                hexRep = hexRep | temp;

                                //adds the character to the map of all the characters and increments the index and size
                                cp[mapIndex] = hexRep;
                                UTF8[mapIndex] = formatted;
                                mapIndex++;
                                size_++; 
                                workingOnChar = false;
                            }
                            else throw (string)"Error4: 4th byte not a continuation byte; improperly formatted character"; 
                        }
                        else throw (string)"Error4: 3rd byte not a continuation byte; improperly formatted character";
                    }
                    else throw (string)"Error4: 2nd byte not a continuation byte; improperly formatted character";
                }
            }   
        }
    }
}

//get - no arguements
string U::get() const{
    string s;
    for(auto val : UTF8){
        s+= val.second;
    }
    return s;
}

//get - one arguement
string U::get(const int index) const{
    if(index > mapIndex || index < 0){
        throw (string)"Invalid index passed to get() method\n";
    }
    return UTF8.at(index);
}

//get - two arguements
string U::get(const int start, const int end) const {
    if(start > mapIndex || start < 0 || end > mapIndex || end < 0 || end < start){
        throw (string)"Invalid index passed to get() method\n";
    }
    string s;
    for(int i = start; i < end; i++){
        s += UTF8.at(i);
    }
    return s;
}

//codepoint
int U::codepoint(const int index) const{
    if(index > mapIndex || index < 0){
        throw (string)"Invalid index passed to codepoint() method\n";
    }
    return cp.at(index);
}

//size
int U::size() const {
    return this->size_;
}

//empty
bool U::empty() const{
    if(UTF8.empty())
        return true;
    else
        return false;
}

//clear
void U::clear(){
    UTF8.clear();
    cp.clear();
    mapIndex = 0;
    size_ = 0;
}

//helper method: how long
int U::howLong(const int first8){
    int maskB1 = 0x80; //if AND and result is x00 then 7 bits
    int maskB2 = 0xE0; //if AND and result is xC0 then 11 bits
    int maskB3 = 0xF0; //if AND and result is xE0 then 16 bits
    int maskB4 = 0xF8; //if AND and result is xF0 then 21 bits
    int result1 = first8 & maskB1;
    int result2 = first8 & maskB2;
    int result3 = first8 & maskB3;
    int result4 = first8 & maskB4;
    
    if(result1 == 0x00){
        return 1;   
    }
    else if(result2 == 0xC0){
        return 2;
    }
    else if(result3 == 0xE0){
        return 3;
    }
    else if(result4 == 0xF0){
        return 4;
    }
    else{
        ostringstream oss;
        oss<< setw(2) << setfill('0') << hex << first8;
        string s_ = oss.str();
        throw (string)"Improperly formatted first byte from file\n";
    }
}

//helper method: how long
bool U::continueB(int byte){
    byte = byte >> 6;
    if(byte == -2){
        return true;
    }
    else return false;
}

//Concatenation: u+u
U U::operator+(const U &rhs) const{
    U rv;
    rv.mapIndex = mapIndex + rhs.mapIndex;
    rv.size_ = size_ + rhs.size_;
    
    rv.UTF8.insert(UTF8.begin(), UTF8.end());
    rv.UTF8.insert(rhs.UTF8.begin(), rhs.UTF8.end());
    
    rv.cp.insert(cp.begin(), cp.end());
    rv.cp.insert(rhs.cp.begin(), rhs.cp.end());
   
    return rv;
}
//Concatenation: u+s
U U::operator+(const string &s) const{
    U rhs;
    rhs = s;
    return *this + rhs;
}

//Append: u += u
U& U::operator+=(const U &rhs){
    //+= the ints
    size_ += rhs.size_;
    //insert for the maps
    int tempMI = mapIndex;
    for(auto val : rhs.UTF8){
        UTF8[tempMI] = val.second;
        tempMI++;
    }
    for(auto val : rhs.cp){
        cp[mapIndex] = val.second;
        mapIndex++;
    }
    return *this;
}

//Append: u += s
U& U::operator+=(const string &s){
    //create a U object based off the string
    U rhs;
    rhs = s;
    *this += rhs;
    return *this;
}

//Subscripting
string U::operator[](const int index) const{
    return get(index);
}

//Boolean evaluation
U::operator bool() const{
    if(empty()){
        return false;
    }
    else return true;
}

bool U::operator!() const{
    if(empty()){
        return true;
    }
    else return false;
}

//Comparison
bool U::operator==(const U &u) const{
    //first check if the two maps have the same size - if not return false
    bool rv = true;
    if(size_ != u.size_){
        return false;
    }
    else{
        string sthis  = "";
        for(auto val : UTF8){
            sthis += val.second;
        }
        string sother = "";
        for(auto val : u.UTF8){
            sother += val.second;
        }
        if(sthis.compare(sother) != 0){
            rv = false;
        }
    }    
    return rv;
}
// u == s
bool U::operator==(const string &s) const{
    U u;
    u = s;
    return *this == u;
}
// u != u
bool U::operator!=(const U &u) const{
    return !(*this == u);
}
// u != s
bool U::operator!=(const string &s) const{
    return !(*this == s);
}

//begin
U::iterator U::begin() {
    map<int,int>* p = &cp;
    iterator it(p);
    return it;
}

//end
U::iterator U::end() {
    map<int,int>* p = &cp;
    iterator it(p, size_);
    return it;
}
    
//front - returns the first int codepoint by value. Throw a std::error message if not available
int U::front() const{
    return cp.at(0);
}
    
//back - returns the last int codepoint by value. Throw a std::string error message if not avaiable
int U::back() const{
    return cp.at(size_ - 1);
}

//Concatenation: s+u
U operator+(const string &s, const U &u){
    return u + s;
}

// ostream << u
ostream& operator<<(ostream& out, const U& u){
   for(auto val : u.UTF8){
       out << val.second;
   }
   return out;
}

//Comparison -> s == u
bool operator==(const string &s, const U &u){
    return u==s;
}
// s != u
bool operator!=(const string &s, const U &u){
    return u!=s;
}
