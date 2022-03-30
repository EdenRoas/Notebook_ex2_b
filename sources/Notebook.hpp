#include <iostream>
#include <string>
#include "Direction.hpp"
#include <unordered_map>
using namespace std;


struct char_ 
{
    char blank = '_';
};

namespace ariel
{
    class Notebook{
        public:
        void write(int page, int row, int col, Direction way,const string &s_write );
        string read(int page, int row, int col, Direction way, int lentgh);
        void erase(int page, int row, int col, Direction way, int lentgh);
        void show(int page);

        private:
        unordered_map< int, unordered_map< int, unordered_map< int, char_>>> my_notebook;
        unordered_map< int,  int> last_line_in_use; 
        
    };
}