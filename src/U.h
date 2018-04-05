//Nicole Kacirek
//4.24.17
//CS253

#ifndef U_H_INCLUDED
#define U_H_INCLUDED

#include <map>
#include <string>

class U{
    public:
        //Defualt Constructor
        U();
    
        //Copy Constructor
        U(const U &);
    
        //Filename constructor: Takes a data filename. The file is read as if readfile were called. Throws a string error message upon error
        U(const std::string&);
    
        //Assignment Operator
        U& operator=(const U&);
    
        //Assignment Operator - u=string
        U& operator=(const std::string&);
    
        //iterator CLASS
        class iterator {
            public:
//               
                //default ctor
                iterator(std::map<int,int> *p = nullptr, int i = 0) : ptr(p), currIndex(i) {}

                //copy ctor
                iterator(const iterator& it) : ptr(it.ptr), currIndex(it.currIndex) {}
                

                //assignment operator
                iterator& operator=(const iterator& it){
                    ptr = it.ptr;
                    currIndex = it.currIndex;
                    return *this;
                }

                //dtor
                ~iterator(){}

                //iterator==iterator
                bool operator==(const iterator& rhs) const{
                    if(currIndex != rhs.currIndex){
                        return false;
                    }
                    else return ptr==rhs.ptr;
                }

                //iterator!=iterator
                bool operator!=(const iterator& rhs) const{
                    return !(*this==rhs);
                }

                //pre-increment
                iterator& operator++(){
                    ++currIndex;
                    return *this;
                }

                //post-increment
                iterator operator++(int){
                    auto temp = *this;
                    ++*this;
                    return temp;
                }

                //pre-dec
                iterator& operator--(){
                    --currIndex;
                    return *this;
                }

                //post-dec
                iterator operator--(int){
                    auto temp = *this;
                    --*this;
                    return temp;
                }

                //*iterator
                int operator*() const{
                    return (*ptr)[currIndex];
                }
                int getIndex() const{
                    return currIndex;
                }
            private:
                std::map<int,int> *ptr; //pointer to the map
                int currIndex;
                
                
        };
    
        //Destructor
        ~U();
    
        //readfile
        void readfile(const std::string&);
    
        //append: Takes a std::string (NOT a filename), and treats the UTF8 characters in it as if they were the result of calling readfile. Throws a std::string error message upon error
        void append(const std::string&);
    
        //get
        std::string get() const;
    
        //get
        std::string get(const int) const;
    
        //get
        std::string get(const int, const int) const;
    
        //codepoint: takes an int index, and returns an int value representing the Unicode codepoint character at that point. The first UTF-8 character us at index 0. Throws a string error for an invalid index. It's like the one-arguement .get() expect that it returns an int
        int codepoint(const int) const;
        
        //size
        int size() const;
    
        //empty: returns true if the object is empty (no characters)
        bool empty() const;
    
        //clear: removes all data from the object. It should become identical to an object created with a default ctor
        void clear();
    
        //Concatenation - they don't change either operand (not +=)
        //u+u
        U operator+(const U&) const;
        //u+s
        U operator+(const std::string&) const;
    
        //Append - the only change the right-hand object
        //u += u
        U& operator+=(const U&);
        //u += s
        U& operator+=(const std::string&);
    
        //Subscripting: Extract the string representing a singel code point as UTF-8 characters like .get(int index)
        std::string operator[](const int) const;
    
        //friend decleration for << so it has access to U's private variables
        friend std::ostream& operator<<(std::ostream&, const U&);
    
        //Boolean evaluation: A U or P is false is it is empty
        operator bool() const;
        bool operator!() const;
    
        //Comparison - when comparing two U objects, or a U and a string, only compare the accumulated characters. Compare them in the normal way that string objects are usually compared
        // u == u
        bool operator==(const U&) const;
        // u == s
        bool operator==(const std::string&) const;
        // u != u
        bool operator!=(const U&) const;
        // u != s
        bool operator!=(const std::string&) const;
    
        template<typename iterator>
        U(const iterator begin, const iterator end) : mapIndex(0), size_(0){
            std::string s(begin, end);
            append(s);
        }
        
        //begin - returns a U::iterator that points to the first int codepoint
        iterator begin();
    
        //end - returns a U::iterator that points just past the last int codepoint
        iterator end();
    
        //front - returns the first int codepoint by value. Throw a std::error message if not available
        int front() const;
    
        //back - returns the last int codepoint by value. Throw a std::string error message if not avaiable
        int back() const;
        
    
    private:
        std::map<int, std::string> UTF8; //stores all the characters read from the file
        std::map<int, int> cp; //stores the code points of the UTF8's at the given index
        int mapIndex; //current max index of the last character in the map
        int size_; //stores the number of UTF8 Characters in the map
        int howLong(int); //returns the number of bytes that need to be read
        void upper(std::string &); //makes hex uppercase
        bool continueB(int);
};

//Concatenation - they don't change either operand (not +=)
// s + u
U operator+(const std::string&, const U&);

// ostream << u: send exactly the characters that were read - nothing extra
std::ostream& operator<<(std::ostream&, const U&);

//Comparison -> s == u
bool operator==(const std::string&, const U&);
// s != u
bool operator!=(const std::string&, const U&);

#endif /* U_H_INCLUDED */
