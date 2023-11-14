#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

const int LETTER_OFFSET_IN_ASCII = 32, MIN_WORD_LEN = 4, SETW_SIZE = 15;

enum Menu {
    UPDATE_INPUT_FILE = 1, BUILD_BST, PRINT_BST, SEARCH_BST, DELETE_WORD, QUIT
};



class Node {
public:
    string word;
    int count = 0;
    Node* leftLink = nullptr;
    Node* rightLink = nullptr;
};

class BinarySearchTree {
public:
    /*pre:RHS tree must exist
    post: LHS will be a copy of RHS tree*/
    const BinarySearchTree& operator=(const BinarySearchTree& RHS);

    /*pre: root exists
    post: returns if the tree is empty*/
    bool IsEmpty() { return (root == nullptr); }

    /*pre:Inorder function exists
    post: prints the inorder traversal of the tree*/
    void TraverseInorder() { Inorder(root); }

    /*pre:Preorder function exists
    post: prints the preorder traversal of the tree*/
    void TraversePreorder() { Preorder(root); }

    /*pre: Postorder function exists
    post: prints the postorder traversal of the tree*/
    void TraversePostOrder() { Postorder(root); }

    /*pre: Height function exists
    post: returns the height of the tree*/
    int GetHeight() const { return Height(root); }

    /*pre: Destroy function exists
    post: tree is destroyed*/
    void DestroyTree() { Destroy(root); }

    /*pre: String must be correctly passed as a parameter
    post: returns if the string is in the tree*/
    void SearchTree(string word, bool& foundWord) { Search(root, word, foundWord); }

    /*pre: String must be correctly passed as a parameter
    post: inserts the string if it does not already exist in tree*/
    void InsertWord(string word);

    /*pre: otherTree exists
    post: A copy of otherTree is created*/
    BinarySearchTree(const BinarySearchTree& otherTree);

    /*pre:none
    post: tree object is created*/
    BinarySearchTree() { root = nullptr; }

    /*pre: Destroy function exists
    post: tree is destroyed*/
    ~BinarySearchTree() { Destroy(root); }

    /*pre: string must be passed as a parameter
    post: node is deleted from tree*/
    void deleteNode(const string& deleteItem, bool& found);

protected:
    Node* root = nullptr;

private:
    /*pre: two tree objects exist
    post: first object becomes copy of second*/
    void CopyTree(Node*& copiedTreeRoot, Node* otherTreeRoot);

    /*pre: none
    post: tree is destroyed*/
    void Destroy(Node*& p);

    /*pre: none
    post: prints the inorder traversal of the tree*/
    void Inorder(Node* p) const;

    /*pre: none
    post: prints the preorder traversal of the tree*/
    void Preorder(Node* p) const;

    /*pre: none
    post: prints the postorder traversal of the tree*/
    void Postorder(Node* p) const;

    /*pre: none
    post: returns height of the tree*/
    int Height(Node* p) const;

    /*pre: two integers must be passed in the parameters
    post: returns the larger of the two integers*/
    int Max(int x, int y) const;

    /*pre: correct parameters must be passed
    post: search results are printed to screen*/
    void Search(Node* p, string searchWord, bool& foundWord);

    /*pre: pointer to Node must be a parameter
    post: node is deleted from the tree*/
    void deleteFromTree(Node*& p);
};

/*pre: string variable must exist
post: lower case string is returned
*/
string ToLower(string str);

/*pre: string variable must exist
post: string is returned without any punctuation and letters after apostrophes are removed
*/
string ProcessWord(string str);

/*
pre: file name must exist and be properly declared
post: file will not include any puntuation and all words 4 characters or less are removed
*/
void ProcessInputFile(string FileName);

/*
pre: the Binary search tree must exist and the header musht exist
post: all the words will be printed to the screen
*/
void BuildBST(BinarySearchTree& BST, string fileName);

/*
pre:BST and header string must exist
post: the BST gets filled with words and printed to screen
*/
void BuildTree(BinarySearchTree& BST, string fileName);

/*
pre: none
post: clears cin, clears the keyboard buffer, prints an error message
*/
void ClearInvalidInput(string errMsg);

/*pre: none
post: search results are printed*/
void EnterSearchSubmenu(BinarySearchTree& BST);

/*pre: none
post: word is deleted from tree and input file*/
//Deletes exact match
void DeleteWordWrapper(BinarySearchTree& BST, string fileName);

/*pre: word exists in file
post: word is replaced with exclamation marks*/
void DeleteWordFromFile(string fileName, string wordToDelete);


//MAIN


int main()
{
    int userChoice;
    string fileName = "Test_Data.txt";
    BinarySearchTree BST;
    stringstream headerSS;
    headerSS << left << setw(SETW_SIZE) << "WORD" << "COUNT" << "\n\n";
    string header = headerSS.str();
    cout << left;

    do {
        cout << "\n\nMENU: \n"
            "1. UPDATE INPUT FILE\n"
            "2. BUILD BST\n"
            "3. PRINT TREE\n"
            "4. SEARCH\n"
            "5. DELETE WORD\n"
            "6. QUIT\n\n";
        cin >> userChoice;

        switch (userChoice) {
        case UPDATE_INPUT_FILE:
            ProcessInputFile(fileName);
            break;
        case BUILD_BST:
            BuildTree(BST, fileName);
            break;
        case PRINT_BST:
            BST.TraverseInorder();
            break;
        case SEARCH_BST:
            EnterSearchSubmenu(BST);
            break;
        case DELETE_WORD:
            DeleteWordWrapper(BST, fileName);
            break;
        case QUIT:
            cout << "\nQUITTING..." << endl;
            break;
        default:
            ClearInvalidInput("INVALID MENU SELECTION");
        }
    } while (userChoice != QUIT);

    return 0;
}


//BST METHODS

//LAB 7 METHODS

void BinarySearchTree::Inorder(Node* p) const {
    if (p == root) { //checks if tree is empty
        if (root == nullptr) {
            cout << "\nCANNOT PRINT AN EMPTY TREE\n";
        }
        else {
            cout << setw(SETW_SIZE) << "WORD" << "COUNT" << "\n\n";
        }
    }
    if (p != nullptr) {
        Inorder(p->leftLink);
        cout << setw(SETW_SIZE) << p->word << p->count << "\n";
        Inorder(p->rightLink);
    }
}

void BinarySearchTree::Preorder(Node* p) const {
    if (p != nullptr) {
        cout << setw(SETW_SIZE) << p->word << p->count << "\n";
        Preorder(p->leftLink);
        Preorder(p->rightLink);
    }
}

void BinarySearchTree::Postorder(Node* p) const {
    if (p != nullptr) {
        Postorder(p->leftLink);
        Postorder(p->rightLink);
        cout << setw(SETW_SIZE) << p->word << p->count << "\n";
    }
}

int BinarySearchTree::Height(Node* p) const {
    if (p == nullptr) {
        return 0;
    }
    else {
        return 1 + Max(Height(p->leftLink), Height(p->rightLink));
    }
}

int BinarySearchTree::Max(int x, int y) const {
    if (x > y) {
        return x;
    }
    else {
        return y;
    }
}

void BinarySearchTree::CopyTree(Node*& copiedTreeRoot, Node* otherTreeRoot) {
    if (otherTreeRoot == nullptr) {
        copiedTreeRoot = nullptr;
    }
    else {
        copiedTreeRoot = new Node;
        copiedTreeRoot->word = otherTreeRoot->word;
        copiedTreeRoot->count = otherTreeRoot->count;
        CopyTree(copiedTreeRoot->leftLink, otherTreeRoot->leftLink);
        CopyTree(copiedTreeRoot->rightLink, otherTreeRoot->rightLink);
    }
}

void BinarySearchTree::Destroy(Node*& p) {
    if (p != nullptr) {
        Destroy(p->leftLink);
        Destroy(p->rightLink);
        delete p;
        p = nullptr;
    }
}

const BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& RHS) {
    Node* tempRoot = nullptr;
    try {
        if (this != &RHS) {
            if (RHS.root == nullptr) {
                root = nullptr;
            }
            else {
                CopyTree(tempRoot, RHS.root);
                Destroy(root);
                root = tempRoot;
            }
        }
    }
    catch (std::bad_alloc error) {
        Destroy(tempRoot);
        std::cerr << "Exception caught, Could not allocate memory. Copy Failed, original tree is intact " << error.what() << "\n";
    }
    return *this;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& otherTree) {
    try {
        if (otherTree.root == nullptr) {
            root = nullptr;
        }
        else {
            CopyTree(root, otherTree.root);
        }
    }
    catch (std::bad_alloc error) {
        Destroy(root);
        root = nullptr;
        std::cerr << "Exception caught, Could not allocate memory. Copy Failed " << error.what() << "\n";
    }
}

void BinarySearchTree::InsertWord(string insertWord) {

    Node* current = nullptr;
    Node* trailCurrent = nullptr;
    Node* newNode;

    newNode = new Node;
    newNode->word = insertWord;
    newNode->count = 1;
    newNode->leftLink = nullptr;
    newNode->rightLink = nullptr;

    bool wordInTree = false;

    if (root == nullptr) {
        root = newNode;
    }
    else
    {
        current = root;
        while (current != nullptr && !wordInTree)
        {
            trailCurrent = current;
            if (current->word == insertWord) {
                current->count += 1;
                wordInTree = true;
            }
            else if (current->word > insertWord) {
                current = current->leftLink;
            }
            else {
                current = current->rightLink;
            }
        }
        if (!wordInTree) {
            if (trailCurrent->word > insertWord) {
                trailCurrent->leftLink = newNode;
            }
            else {
                trailCurrent->rightLink = newNode;
            }
        }
    }
}

//LAB 8 METHODS

void BinarySearchTree::Search(Node* p, string searchWord, bool& foundWord) {
    if (p != nullptr) {
        Search(p->leftLink, searchWord, foundWord);

        string tempWord = p->word;
        if (tempWord.find(searchWord) != std::string::npos) {

            if (!foundWord) {
                cout << "Words containing \"" << searchWord << "\": \n"
                    << setw(SETW_SIZE) << "WORD" << "COUNT" << "\n\n"; //cout header before printing first word to screen;
            }

            cout << setw(SETW_SIZE) << p->word << p->count << "\n";
            foundWord = true;
        }

        Search(p->rightLink, searchWord, foundWord);
    }

}

void BinarySearchTree::deleteFromTree(Node*& p) {
    Node* current;
    Node* trailCurrent;
    Node* temp;

    if (p == nullptr) {
        cout << "The word you are trying to delete does not exist\n";
    }
    else if (p->leftLink == nullptr && p->rightLink == nullptr) {
        temp = p;
        p = nullptr;
        delete temp;
    }
    else if (p->leftLink == nullptr) {
        temp = p;
        p = temp->rightLink;
        delete temp;
    }
    else if (p->rightLink == nullptr) {
        temp = p;
        p = temp->leftLink;
        delete temp;
    }
    else {
        current = p->leftLink;
        trailCurrent = nullptr;

        while (current->rightLink != nullptr) {
            trailCurrent = current;
            current = current->rightLink;
        }

        p->word = current->word;
        p->count = current->count;
        if (trailCurrent == nullptr) {
            p->leftLink = current->leftLink;
        }
        else {
            trailCurrent->rightLink = current->leftLink;
        }
        delete current;
    }
}

void BinarySearchTree::deleteNode(const string& deleteItem, bool& found) {
        Node* current;
        Node* trailCurrent;
        //bool found = false;
        if (root == nullptr)
            cout << "Cannot delete from an empty dictionary.\n";
        else {
            current = root;
            trailCurrent = root;
            while (current != nullptr && !found)
            {
                if (current->word == deleteItem)
                    found = true;
                else
                {
                    trailCurrent = current;
                    if (current->word > deleteItem)
                        current = current->leftLink;
                    else
                        current = current->rightLink;
                }
            }
            if (current == nullptr) {
                cout << "The word you are trying to delete is not in the dictionary.\n";
            }
            else if (found) {
                if (current == root) {
                    deleteFromTree(root);
                }
                else if (trailCurrent->word > deleteItem) {
                    deleteFromTree(trailCurrent->leftLink);
                }
                else {
                    deleteFromTree(trailCurrent->rightLink);
                }
                cout << "\"" << deleteItem << "\"" << " was deleted successfully\n";
            }
            else
                cout << "The word you are trying to delete is not in the dictionary.\n";
        }
}

//MAIN FUNCTIONS

string ProcessWord(string str) {
    string processedWord = "";
    size_t strLen = str.length();
    for (int i = 0; i < strLen; i++) {
        char ch = str[i];
        if (((ch >= 'a') && (ch <= 'z'))) {
            processedWord += ch;
        }
        else if (ch == '\'') { //skips everything after apostrophe
            i = strLen;
        }
    }
    if (!(processedWord.length() > MIN_WORD_LEN)) {
        processedWord = "";
    }
    return processedWord;
}

string ToLower(string str) {
    string lowerCaseStr = "";
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (((ch >= 'A') && (ch <= 'Z'))) {
            ch += LETTER_OFFSET_IN_ASCII; //converts char to lower case
        }
        lowerCaseStr += ch;
    }
    return lowerCaseStr;
}

void ProcessInputFile(string FileName) {
    std::fstream ioFile{ FileName, std::ios::in | std::ios::out };

    if (!ioFile) {
        cout << "Input file not found. Exiting the program." << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
    if (ioFile.peek() == EOF) {
        cout << "The input file is empty. Quitting the program." << endl;
        ioFile.close();
        system("pause");
        exit(EXIT_FAILURE);
    }
    string word;
    while (ioFile >> word) {
        stringstream fillSpace("");
        int originalLen = word.length();

        word = ToLower(word);
        word = ProcessWord(word);

        fillSpace << setw(originalLen) << word;

        ioFile.seekg(-1 * originalLen, std::ios::cur);
        ioFile << fillSpace.str();
        ioFile.seekg(ioFile.tellg(), std::ios::beg);
    }
    cout << "INPUT FILE UPDATED\n";
    ioFile.close();
}


void DeleteWordFromFile(string fileName, string wordToDelete) {

    std::fstream ioFile{ fileName, std::ios::in | std::ios::out };

    if (!ioFile) {
        cout << "Input file not found. Exiting the program." << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
    if (ioFile.peek() == EOF) {
        cout << "The input file is empty. Quitting the program." << endl;
        ioFile.close();
        system("pause");
        exit(EXIT_FAILURE);
    }

    string word;
    while (ioFile >> word) {
        stringstream fillSpace("");
        int originalLen = word.length();
        if (wordToDelete == word) {
            fillSpace << setfill('!') << setw(originalLen) << "";
        }
        else {
            fillSpace << word;
        }
        ioFile.seekg(-1 * originalLen, std::ios::cur);
        ioFile << fillSpace.str();
        ioFile.seekg(ioFile.tellg(), std::ios::beg);
    }
    cout << "\nWORD DELETED FROM INPUT FILE\n";
    ioFile.close();

}

void BuildBST(BinarySearchTree& BST, string fileName) {
    BST.DestroyTree();
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Input file not found. Exiting the program." << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
    if (inFile.peek() == EOF) {
        cout << "The input file is empty. Quitting the program." << endl;
        inFile.close();
        system("pause");
        exit(EXIT_FAILURE);
    }

    string word;
    while (inFile >> word) {
        BST.InsertWord(word);
    }
    inFile.close();
}

void BuildTree(BinarySearchTree& BST, string fileName) {
    try {
        BuildBST(BST, fileName);
        cout << "BUILD SUCCESSFUL\n";
    }
    catch (const std::bad_alloc error) {
        std::cerr << "Exception caught, Could not allocate memory. Destroying Tree " << error.what() << "\n";
        BST.DestroyTree();
    }
}

void ClearInvalidInput(string errMsg) {
    cout << "\n" << errMsg << "\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void EnterSearchSubmenu(BinarySearchTree& BST) {
    string keyword;
    bool foundWords = false;
    cout << "Enter a word to search by: ";
    cin >> keyword;
    cout << "\n";
    keyword = ToLower(keyword);

    BST.SearchTree(keyword, foundWords);
    if (!foundWords) {
        cout << "No words containing the string \"" << keyword << "\" found.\n";
    }
}


//Deletes exact match
void DeleteWordWrapper(BinarySearchTree& BST, string fileName) {
    string wordToDelete;
    bool wordFound = false;
    cout << "Enter a word you want to delete: ";
    cin >> wordToDelete;
    cout << "\n";
    wordToDelete = ToLower(wordToDelete);

    BST.deleteNode(wordToDelete, wordFound);
    if (wordFound) {
        DeleteWordFromFile(fileName, wordToDelete);
    }
    
}


//TEST 1
/*

MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

1
INPUT FILE UPDATED


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

2
BUILD SUCCESSFUL


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

3
WORD           COUNT

about          1
accurately     2
actually       1
addition       1
agenda         1
agree          2
almost         1
always         1
anything       1
basically      1
because        4
become         1
believe        1
close          1
congress       6
democrat       1
democrats      2
different      2
divided        1
division       1
either         3
everyone       1
falcon         1
fewer          1
focused        1
forced         1
fully          1
going          1
hinders        1
ideas          2
impact         1
increase       1
instead        1
major          1
members        2
might          1
other          2
parties        2
partisan       1
partisanship   1
party          2
passed         1
passing        1
people         4
population     1
power          1
problems       1
professor      1
progress       1
rather         1
reality        1
represent      4
representing   1
republican     1
republicans    2
should         1
showing        1
sides          2
siding         1
solving        1
split          1
states         2
stopping       1
supposed       2
their          3
umbrella       1
under          1
united         1
voted          2
voters         1


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

4
Enter a word to search by: be

Words containing "be":
WORD           COUNT

because        4
become         1
believe        1
members        2


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

5
Enter a word you want to delete: their

INPUT FILE UPDATED
"their" was deleted from the tree


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

3
WORD           COUNT

about          1
accurately     2
actually       1
addition       1
agenda         1
agree          2
almost         1
always         1
anything       1
basically      1
because        4
become         1
believe        1
close          1
congress       6
democrat       1
democrats      2
different      2
divided        1
division       1
either         3
everyone       1
falcon         1
fewer          1
focused        1
forced         1
fully          1
going          1
hinders        1
ideas          2
impact         1
increase       1
instead        1
major          1
members        2
might          1
other          2
parties        2
partisan       1
partisanship   1
party          2
passed         1
passing        1
people         4
population     1
power          1
problems       1
professor      1
progress       1
rather         1
reality        1
represent      4
representing   1
republican     1
republicans    2
should         1
showing        1
sides          2
siding         1
solving        1
split          1
states         2
stopping       1
supposed       2
umbrella       1
under          1
united         1
voted          2
voters         1


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

6

QUITTING...
*/

//Test 2 (empty input file)
/*
MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

1
The input file is empty. Quitting the program.
Press any key to continue . . .

*/

//Test 3 (input file not found)
/*
MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

1
Input file not found. Exiting the program.
Press any key to continue . . .

*/

//Test 4 (no search results)
/*

MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

2
BUILD SUCCESSFUL


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

4
Enter a word to search by: asdf

No words containing the string "asdf" found.


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

6

QUITTING...

*/

//Test 5 (word to be deleted not found)
/*
MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

2
BUILD SUCCESSFUL


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

5
Enter a word you want to delete: dsafd

The word you are trying to delete is not in the tree.


MENU:
1. UPDATE INPUT FILE
2. BUILD BST
3. PRINT TREE
4. SEARCH
5. DELETE WORD
6. QUIT

6

QUITTING...
*/

//Test 6 (replaced letters of word with '!')
/*
  agree      professor falcon     believe      congress     become     partisan because            focused    democrats     republicans rather      actually solving  problems
    impact         increase    partisanship         fewer          passed because         sides              stopping       other
    addition congress members         supposed    represent     population    people     voted                      siding      either party     going      !!!!!  agenda
     hinders progress because    congress    split close                     sides               !!!!! power             other           passing anything                 fully agree
congress    supposed    represent     people        united  states                      representing either republicans     democrats
     showing                different states        represent     voters accurately because               everyone under     umbrella    either republican    democrat          reality people might      different  ideas
congress     almost always      divided          major  parties         division should    about ideas instead     parties
     members    congress     basically forced              !!!!!  party              accurately represent     people     voted
*/