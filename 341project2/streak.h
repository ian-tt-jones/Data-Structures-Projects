// UMBC - CMSC 341 - Fall 2022 - Proj2
#ifndef STREAK_H
#define STREAK_H
#include <iostream>
using namespace std;
class Grader; // this class is for grading purposes, no need to do anything
class Tester; // this is your tester class, you add your test functions in this class
class STREAK; // this is the class that you implement
enum STATE {ALIVE, DEAD};
enum AGE {CUB, YOUNG, OLD};
enum GENDER {MALE, FEMALE, UNKNOWN};
const int MINID = 10000;
const int MAXID = 99999;
#define DEFAULT_HEIGHT 0
#define DEFAULT_ID 0
#define DEFAULT_STATE ALIVE
#define DEFAULT_AGE CUB
#define DEFAULT_GENDER UNKNOWN

class Tiger{
    public:
    friend class Grader;
    friend class Tester;
    friend class Streak;
    Tiger(int id, AGE age = DEFAULT_AGE, GENDER gender = DEFAULT_GENDER, STATE state = DEFAULT_STATE)
        :m_id(id),m_age(age),m_gender(gender),m_state(state) {
            m_left = nullptr;
            m_right = nullptr;
            m_height = DEFAULT_HEIGHT;
        }
    Tiger(){
        m_id = DEFAULT_ID;
        m_state = DEFAULT_STATE;
        m_age = DEFAULT_AGE;
        m_gender = DEFAULT_GENDER;
        m_left = nullptr;
        m_right = nullptr;
        m_height = DEFAULT_HEIGHT;
    }
    int getID() const {return m_id;}
    STATE getState() const {return m_state;}
    string getStateStr() const {
        string text = "";
        switch (m_state)
        {
        case DEAD:text = "DEAD";break;
        case ALIVE:text = "ALIVE";break;
        default:text = "UNKNOWN";break;
        }
        return text;
    }
    AGE getAge() const {return m_age;}
    string getAgeStr() const {
        string text = "";
        switch (m_age)
        {
        case CUB:text = "CUB";break;
        case YOUNG:text = "YOUNG";break;
        case OLD:text = "OLD";break;
        default:text = "UNKNOWN";break;
        }
        return text;
    }
    GENDER getGender() const {return m_gender;}
    string getGenderStr() const {
        string text = "";
        switch (m_gender)
        {
        case MALE:text = "MALE";break;
        case FEMALE:text = "FEMALE";break;
        case UNKNOWN:text = "UNKNOWN";break; 
        default:text = "UNKNOWN";break;
        }
        return text
        ;
    }
    int getHeight() const {return m_height;}
    Tiger* getLeft() const {return m_left;}
    Tiger* getRight() const {return m_right;}
    void setID(const int id){m_id=id;}
    void setState(STATE state){m_state=state;}
    void setAge(AGE age){m_age=age;}
    void setGender(GENDER gender){m_gender=gender;}
    void setHeight(int height){m_height=height;}
    void setLeft(Tiger* left){m_left=left;}
    void setRight(Tiger* right){m_right=right;}
    private:
    int m_id;
    AGE m_age;
    GENDER m_gender;
    STATE m_state;
    Tiger* m_left;//the pointer to the left child in the BST
    Tiger* m_right;//the pointer to the right child in the BST
    int m_height;//the height of node in the BST
};

class Streak{
    public:
    friend class Grader;
    friend class Tester;
    Streak();
    ~Streak();
    void insert(const Tiger& tiger);
    void clear();
    void remove(int id);
    void dumpTree() const;
    void listTigers() const;
    bool setState(int id, STATE state);
    void removeDead();//remove all dead tigers from the tree
    bool findTiger(int id) const;//returns true if the tiger is in tree
    int countTigerCubs() const;// returns the # of cubs in the streak
    private:
    Tiger* m_root;//the root of the BST
    bool isBalanced;
    bool allDead;
    bool bstProperty;

    void dump(Tiger* aTiger) const;//helper for recursive traversal
    void updateHeight(Tiger* aTiger);
    int checkImbalance(Tiger* aTiger);
    Tiger* rebalance(Tiger* aTiger);

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
    Tiger* Search(Tiger* aTiger, int id){
        if(aTiger == nullptr or aTiger -> m_id == id){
            return aTiger;
        }

        if(id < aTiger -> m_id){
            return Search(aTiger -> m_left, id);
        }

        return Search(aTiger -> m_right, id);
    }

    Tiger* insertRecur(Tiger* aTiger, const Tiger& tiger){
        if(aTiger == nullptr){
            Tiger* newTiger = new Tiger(tiger.getID(), tiger.getAge(), tiger.getGender(), tiger.getState());
            newTiger -> setHeight(0);
            return newTiger;
        }
        if(tiger.getID() < aTiger -> getID()){
            aTiger -> setLeft(insertRecur(aTiger -> getLeft(), tiger));
        }
        else if(tiger.getID() > aTiger -> getID()){
            aTiger -> setRight(insertRecur(aTiger -> getRight(), tiger));
        }else{
            return aTiger;
        }

        updateHeight(aTiger);
        int bf = checkImbalance(aTiger);
        if(bf > 1 and tiger.m_id < aTiger -> m_left -> m_id){
            return rightRotation(aTiger);
        }
        if(bf < -1 and tiger.m_id > aTiger -> m_right -> m_id){
            return leftRotation(aTiger);
        }
        if(bf > 1 and tiger.m_id > aTiger -> m_left -> m_id){
            aTiger -> m_left = leftRotation(aTiger -> m_left);
            return rightRotation(aTiger);
        }
        if(bf < -1 and tiger.m_id < aTiger -> m_right -> m_id){
            aTiger -> m_right = rightRotation(aTiger -> m_right);
            return leftRotation(aTiger);
        }
        return aTiger;
    }

    Tiger* removeRecur(Tiger* root, int id){
        if(root == nullptr){
            return root;
        }
        if(id < root -> m_id){
            root -> m_left = removeRecur(root -> m_left, id);
        }
        else if(id > root -> m_id){
            root -> m_right = removeRecur(root -> m_right, id);
        }
        else{
            if((root -> m_left == nullptr) or (root -> m_right == nullptr)){
                Tiger* temp = root -> m_left ? root -> m_left : root -> m_right;
                // no child
                if(temp == nullptr){
                    temp = root;
                    root = nullptr;
                }
                // one child
                else{
                    root = temp;
                }
                delete temp;
            }
            else{
                Tiger* temp = findReplacement(root -> m_right);
                copyData(root, temp);
                root -> m_right = removeRecur(root -> m_right, temp -> m_id);
            }
          
        }
        // tree with one node
        if(root == nullptr){
            return root;
        }
        updateHeight(root);
        int bf = checkImbalance(root);
        if(bf > 1 and id < root -> m_left -> m_id){
            return rightRotation(root);
        }
        if(bf < -1 and id > root -> m_right -> m_id){
            return leftRotation(root);
        }
        if(bf > 1 and id > root -> m_left -> m_id){
            root -> m_left = leftRotation(root -> m_left);
            return rightRotation(root);
        }
        if(bf < -1 and id < root -> m_right -> m_id){
            root -> m_right = rightRotation(root -> m_right);
            return leftRotation(root);
        }
        return root;
    }

    void clearTree(Tiger* root){
        if(root == nullptr){
            return;
        }
        clearTree(root -> m_left);
        clearTree(root -> m_right);
        delete root;
    }

    void listTigerRecur(Tiger* root) const{
       if(root == nullptr){
            return;
        }
        listTigerRecur(root -> m_left);
        listTigerRecur(root -> m_right);
        cout << root -> m_id << ":";
        cout << root -> m_age << ":";
        cout << root -> m_gender << ":";
        cout << root -> m_state << endl;
    }

    void removeDeadRecur(Tiger* root){
        if(root == nullptr){
            return;
        }
        removeDeadRecur(root -> m_left);
        removeDeadRecur(root -> m_right);
        if(root -> getState() == DEAD){
            // delete tiger
            remove(root -> m_id);
        }
    }

    int countTigerCubsRecur(Tiger* root) const{
        int count;
        if(root -> getAge() == CUB){
            count = 1;
        }
        else{
            count = 0;
        }
        if(root -> m_left != nullptr){
            count += countTigerCubsRecur(root -> m_left);
        }
        if(root -> m_right != nullptr){
            count += countTigerCubsRecur(root -> m_right);
        }
            return count;
    }

 
    Tiger* rightRotation(Tiger* root){
        bool rootChange = false;
        Tiger* newRoot = root -> m_left;
        Tiger* tree;
        if(newRoot -> m_right == nullptr){
            tree = nullptr;
        }
        else{
            tree = newRoot -> m_right;
        }
        if(root -> m_id == m_root -> m_id){
            rootChange = true;
        }

        // rotate
        newRoot -> setRight(root);
        root -> setLeft(tree);
        if(rootChange){
            m_root = newRoot;
        }

        // update heights
        updateHeight(root);
        updateHeight(newRoot);

        return newRoot;
    }

    Tiger* leftRotation(Tiger* root){
        bool rootChange = false;
        Tiger* newRoot = root -> m_right;
        Tiger* tree = newRoot -> m_left;
        if(root -> m_id == m_root -> m_id){
            rootChange = true;
        }

        // rotate
        newRoot -> setLeft(root);
        root -> setRight(tree);
        if(rootChange){
            m_root = newRoot;
        }

        // update heights
        updateHeight(root);
        updateHeight(newRoot);

        return newRoot;
    }

    void checkBalance(Tiger* root){
        if(root == nullptr){
            return;
        }
        checkBalance(root -> m_left);
        checkBalance(root -> m_right);
        if(checkImbalance(root) < -1 or checkImbalance(root) > 1){
            isBalanced = false;
        }
    }

    Tiger* balanceTree(Tiger* root){
        if(root == nullptr){
            return root;
        }
        rebalance(root);
        balanceTree(root -> m_left);
        balanceTree(root -> m_right);
    }

    Tiger* findParent(int id){
        Tiger* temp = m_root;
        while(temp -> m_left -> m_id != id and temp -> m_right -> m_id != id){
            if(temp -> m_id < id){
                temp = temp -> m_right;
            }
            else{
                temp = temp -> m_left;
            }
        }
        return temp;
    }

    Tiger* findReplacement(Tiger* aTiger){
        Tiger* temp = aTiger;
        temp = temp -> m_right;
        while(temp -> m_left != nullptr){
            temp = temp -> m_left;
        }
        if(temp -> m_right != nullptr){
            return temp -> m_right;
        }
        else{
            return temp;
        }
        return temp;
    }

    void copyData(Tiger* &t1, Tiger* &t2){
        t1 -> setState(t2 -> getState());
        t1 -> setGender(t2 -> getGender());
        t1 -> setID(t2 -> getID());
        t1 -> setAge(t2 -> getAge());
    }

    Tiger* updateAllHeights(Tiger* root){
        if(root == nullptr){
            return root;
        }
        updateHeight(root);
        updateAllHeights(root -> m_left);
        updateAllHeights(root -> m_right);
    }

    void searchForDead(Tiger* root){
        if(root == nullptr){
            return;
        }
        searchForDead(root -> m_left);
        searchForDead(root -> m_right);
        if(root -> getState() == DEAD){
            allDead = false;
        }
    }

    void bstRecur(Tiger* root){
        if(root == nullptr){
            return;
        }
        bstRecur(root -> m_left);
        bstRecur(root -> m_right);
        if(root -> m_left != nullptr){
            if(root -> m_id < root -> m_left -> m_id){
                bstProperty = false;
            }
        }
        if(root -> m_right != nullptr){
            if(root -> m_id > root -> m_right -> m_id){
                bstProperty = false;
            }
        }
    }
};
#endif