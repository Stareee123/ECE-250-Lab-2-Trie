#include "trie.h"
#include <fstream>
#include <vector>


//load function was given in the tutorial session
void Trie::load(){
    std::ifstream file;
    file.open("corpus.txt");
    std::string word;
    while (!file.eof()){
        file >> word;
        i (word, false);
    };
    std::cout << "success" << std::endl;
};

//i - insert function
void Trie::i(std::string word, bool load){      //extra bool input to not print success or failure for load function input
    TrieNode* current;
    current = root;

    for (int i = 0; word[i] != '\0'; ++i){      //loop for the number of characters in word input
        int location = word[i] - 'A';           //getting the location in the character array of the word input

        if (current -> character[location] == nullptr){         //if that location is empty, create a new node
            current -> character[location] = new TrieNode();
        };

        current = current -> character[location];       //update current pointer
    };

        if(current -> finish == false){     //if word already exits (which can also be made in the top for loop) but not set as finish of a word
            current -> finish = true;       //make it as a end of the word

            if(load == true){               //if statement for load function to print out multiple success for failure
                std::cout << "success" << std::endl;
            };
            word_num = word_num + 1;        //incrementing word number
        } else {                            //if word already exits return failure
            if (load == true){              
                std::cout << "failure" << std::endl;
            };
        };
};

//funciton that will return the node that has the last character of word input
TrieNode* Trie::get_node (std::string word){

    TrieNode* current = root;       //start the search from the root of the trie

    for (int i = 0; word[i] != '\0'; ++i){      //loop for number of characters in word input
        int location = word[i] - 'A';           //getting the location as above

        if (current -> character[location] == nullptr){     //if there don't exit a character return nullptr
            return nullptr;
        };

        current = current -> character[location];       //update current

    };

    return current;         //returning current = node that has the last character of word input
};


//function that will return the number of words (finish == true) that starts from the given node
int Trie::wordcount (TrieNode* node){
    if (node == nullptr){       //if node is nullptr return 0
        return 0;
    };

    int count = 0;      //counter value that will store the number of words

    for (int i = 0; i < 26; ++i){       //checking all alphabets' location for the node input

        if (node -> character[i] != nullptr){       //if any alphabet is not a nullptr, recursive back to wordcount.
            count = count + wordcount(node->character[i]);
        };
    };

    if (node->finish == true){         //corner case : check rather inputted node is also a end of the word.
        count = count + 1;
    };

    return count;       //returning total count value

};


void Trie::c(std::string prefix){
    int count = 0;
    TrieNode* search_node = get_node(prefix);       //get the address of the last character of the prefix via helper function
    if (search_node != nullptr){                    //if search_node is not nullptr, call the wordcount helper function and output the return value as the total number of words that contains the prefix
        count = wordcount(search_node);
        std::cout << "count is " << count << std::endl;
    } else {
        std::cout << "not found" << std::endl;      //if prefix is not found, return not found
    };
};

//function that checks rather a node has child or not
bool Trie::more_node (TrieNode* node, int location){        //get node and location input to check rather that alphabet has a child or not
    int num_of_children = 0;        //setting up counter that will contain the number of children

    for (int i = 0; i < 26; ++i){      //loop for all alphabets
        if (node->character[location] ->character[i] != nullptr){       //if that character has a child, increment the counter
            num_of_children = num_of_children + 1;
        };
    };

    //return true if given character has a child and false if it is a leaf
    if (num_of_children > 0){
        return true;
    } else {
        return false;
    };
};


//helper function of e that erases the word. 
//node will be the start point of word search, word will be the word input from original e function, index will be used for representing nth character that needs to be checked for a recursive call. 
void Trie::erase (TrieNode* node, std::string word, int index){


    int size = static_cast<int>(word.length());         //setting up variable for the length value of the input

    //if there is a word inside a tree, set that node's finish value as false and print out success. If that last node is not set as the end of the word, it means that word is not in the trie so print out failure.
    if (index == size){
        if (node -> finish == true){
            node -> finish = false;
            word_num = word_num - 1;


            std::cout << "success" << std::endl;
        }else{
            std::cout << "failure" << std::endl;
        };
        return;
    };

    int location = word[index] - 'A';

    // if the index value th character is inside the tree, recursive back with updated node and index value. If that character is not inside the trie, print out failure. 
    if (node -> character[location] != nullptr){
        erase(node -> character[location], word, index + 1);
    } else {
        std::cout << "failure" << std::endl;
        return;
    };

    //if the node that we are checking does not have a child and it is not set as the end of the word, delete it. 
    if (more_node(node, location) == false){
        if (node -> character[location] -> finish == false){
            delete node -> character[location];
            node -> character[location] = nullptr;
        };
    };

};

//calling a helper function for erasing process
void Trie::e (std::string word){
    erase(root, word, 0);       //erase search should start from the root of the trie and the 0th character of word input
};


void Trie::p (){
    print_null = false;
    TrieNode* current = root;   
    print(current, "");     //calling a print helper function with root and empty std::string value
    if (print_null == true){
        std::cout << "" << std::endl;
    };
};

void Trie::print(TrieNode* node, std::string word){

    //if inputed node is the end of the word, print it out with one empty space behind it
    if (node -> finish == true){
        std::cout << word << " ";
    };

    //check for all the alphabets in the current node and if it is not a nullptr, recursive with the updated node and word (previous inputed word + the new alphabet that was not a nullptr) input.
    for (int i = 0; i < 26; ++i){
        if (node -> character[i] != nullptr){
            print(node->character[i], word + char(i + 'A'));
            print_null = true;
        };
    };
};


//spellcheck funtion
void Trie::spellcheck (std::string word){


    // if there is a word inside the tree -> the address that contains the last word should not be a nullptr & it should be marked as the end of the word.
    if (get_node(word) != nullptr && get_node(word) -> finish == true){
        std::cout << "correct" << std::endl;
        return;
    };
    
    //If the trie does not even contains the first character of the input, create a new line and print out nothing
    if (root -> character[word[0] - 'A'] == nullptr){
        std::cout << std::endl;
        return;
    };

    TrieNode* current = root;
    std::string output;
    int size = static_cast<int>(word.length());


    for (int i = 0; i < size; ++i){
        char check = word[i];
        int location = check - 'A';

        if (current -> character[location] == nullptr){     //if ith alphabet is not included in the trie, break the for loop so that we can check for the most fiting (longest) prefix
            break;
        };

        if (current -> character[location] != nullptr){     //if ith alphabet is in the tire, update the current pointer and output std::string value to contain that character. 
            current = current -> character[location];
            output = output + check;
        };
    };

    //now the output will contain the most fiting prefix that is in the tree. call the helper function printhelp which will print out all the words that contains that prefix. 
    if (current != nullptr){
        printhelp(current, output);
    };

    std::cout << "" << std::endl;


};

void Trie::printhelp (TrieNode* node, std::string word){

    //if inputed node is also a end of the word, print it out with spacing at the end
    if (node -> finish == true){
        std::cout << word << " ";
    };

    //check for all the alphabets in the current node and if it is not a nullptr, recursive with the updated node and word (previous inputed word + the new alphabet that was not a nullptr) input.
    for (int i = 0; i < 26; ++i){
        if (node -> character[i] != nullptr){
            printhelp(node -> character[i], word + char('A' + i));
        };
    };
};


//starting from the root, if any alphabet location is not a nullptr, call a deletenode helperfunction with that address.
void Trie::clear(){
    for (int i = 0; i < 26; ++i){
        if (root -> character[i] != nullptr){
            deletenode(root->character[i]);
            root -> character[i] = nullptr;
            
        };
    };
    std::cout << "success" << std::endl;
    word_num = 0;       //set the word_num counter to 0
};

void Trie::deletenode(TrieNode* node){

    //check all alphabets in the current node. If it is not a nullptr, recursive back with updated address and eventually set all the nodes to nullptr. This process will delete all the nodes inside the tree expcept for the root. 
    //root should not be deleted since trie can be reused. 
    for (int i = 0; i < 26; ++i){
        if (node -> character[i] != nullptr){
            deletenode(node -> character[i]);
            node -> character[i] = nullptr;
            
        };
    };

    delete node;
};

//this function will print out empty 1 if the word_num value is 0 and the trie is empty. If the trie is not empty, it will print out empty 0. 
void Trie::empty(){
    int output = 0;

    if (word_num == 0){
        output = 1;
        std::cout << "empty " << output << std::endl;
    } else {
        std::cout << "empty " << output << std::endl;
    };
};



//This function will print out the word_num variable to output the number of total words in the tree. 
void Trie::size(){
    std::cout << "number of words is " << word_num << std::endl;
};

//exit function will return false which will be used to exit the while loop in the main. 
bool Trie::exit(){
    return false;
};