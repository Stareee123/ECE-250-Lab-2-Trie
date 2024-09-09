// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"


int main(){
    
    // your code goes here...  
    std::string command = " ";

    //variable used to run a while loop that runs till program is over
    bool program_run = true;

    //variables for function intake
    std::string word;

    //creating object for Trie header file
    Trie Trieobject;

    //while loop will lopp till the exit function is called and program_run is set to false
    while (program_run){
        std::cin >> command;

        if (command == "i"){                //if command input is i, get the word input and call the i function
            std::cin >> word;
            Trieobject.i(word, true);
        }else if (command == "c"){          //if command input is c, get the word input and call the c function
            std::cin >> word;
            Trieobject.c(word);
        }else if (command == "e"){          //if command input is e, get the word input and call the e function
            std::cin >> word;
            Trieobject.e(word);
        }else if (command == "p"){          //if command input is p, call the p function
            Trieobject.p();
        }else if (command == "spellcheck"){ //if command input is spellcheck, get the word input and call the spellcheck function
            std::cin >> word;
            Trieobject.spellcheck(word);
        }else if (command == "empty"){      //if command input is empty, call the empty function
            Trieobject.empty();
        }else if (command == "clear"){      //if command input is clear, call the clear function
            Trieobject.clear();             
        }else if (command == "size"){       //if command input is size, call the size function
            Trieobject.size();
        }else if (command == "exit"){       //if command input is exit, call the exit function
            program_run = Trieobject.exit();
        }else if (command == "load"){       //if command input is load, call the load function
            Trieobject.load();
        };
    };

    return 0;
};