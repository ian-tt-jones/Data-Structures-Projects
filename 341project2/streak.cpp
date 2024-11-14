// UMBC - CMSC 341 - Fall 2022 - Proj2
#include "streak.h"

Streak::Streak(){
    m_root = nullptr;
    isBalanced = true;
    allDead = true;
    bstProperty = true;
}

Streak::~Streak(){
    clear();
}

void Streak::insert(const Tiger& tiger){
    if(m_root != nullptr){
        insertRecur(m_root, tiger);
    }else{
        Tiger* newTiger = new Tiger(tiger.getID(), tiger.getAge(), tiger.getGender(), tiger.getState());
        m_root = newTiger;
    }
}

void Streak::clear(){
    clearTree(m_root);
    m_root = nullptr;
}

void Streak::remove(int id){
    if(m_root -> m_id == id){
        if(m_root -> m_right == nullptr){
            if(m_root -> m_left == nullptr){
                delete m_root;
                m_root = nullptr;
            }else{
                removeRecur(m_root, id);
            }
        }else{
            removeRecur(m_root, id);
        }
    }else{
        removeRecur(m_root, id);
    }
    
}

void Streak::updateHeight(Tiger* aTiger){
    if(aTiger != nullptr){
        if(aTiger -> m_left == nullptr and
            aTiger -> m_right == nullptr){
            aTiger -> setHeight(0);
        }
        else if(aTiger -> m_left == nullptr){
            aTiger -> setHeight(aTiger -> m_right -> getHeight() + 1);
        }
        else if(aTiger -> m_right == nullptr){
            aTiger -> setHeight(aTiger -> m_left -> getHeight() + 1);
        }
        else if(aTiger -> m_left -> m_height >
            aTiger -> m_right -> m_height){
            aTiger -> setHeight(aTiger -> m_left -> getHeight() + 1);
        }else{
            aTiger -> setHeight(aTiger -> m_right -> getHeight() + 1);
        }
    }
}

int Streak::checkImbalance(Tiger* aTiger){
    if(aTiger != nullptr){
        updateHeight(aTiger);
        if(aTiger -> m_left == nullptr){
            if(aTiger -> m_right != nullptr){
                return -1 - aTiger -> m_right -> getHeight();
            }else{
                return 0;
            }
        }else{
            if(aTiger -> m_right == nullptr){
                return 1 + aTiger -> m_left -> getHeight();
            }
        }
        return aTiger -> m_left -> getHeight()
            - aTiger -> m_right -> getHeight();
    }
    return 0;
}

Tiger* Streak::rebalance(Tiger* aTiger){
    Tiger* temp;
    updateHeight(aTiger);
    if(checkImbalance(aTiger) < -1){
        // RR or RL imbalance
        if((checkImbalance(aTiger -> m_right -> m_right) >
                    checkImbalance(aTiger -> m_right -> m_left) or aTiger -> m_right -> m_left
                    == nullptr)){
            // RR imbalance
            temp = leftRotation(aTiger);
        }else{
            // RL imbalance
            aTiger -> setRight(rightRotation(aTiger -> m_right));
            temp = leftRotation(aTiger); 
        }
    }
    else if(checkImbalance(aTiger) > 1){
        // LL or LR imbalance
        if((checkImbalance(aTiger -> m_left -> m_left) >
                    checkImbalance(aTiger -> m_left -> m_right) or aTiger -> m_left -> m_right
                    == nullptr)){
            // RR imbalance
            temp = rightRotation(aTiger);
        }else{
            // RL imbalance
            aTiger -> setLeft(leftRotation(aTiger -> m_left));
            temp = rightRotation(aTiger); 
        }
    }
    return temp;
}

void Streak::dumpTree() const {dump(m_root);}

void Streak::dump(Tiger* aTiger) const{
    if (aTiger != nullptr){
        cout << "(";
        dump(aTiger->m_left);//first visit the left child
        cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
        dump(aTiger->m_right);//third visit the right child
        cout << ")";
    }
}

void Streak::listTigers() const {
    listTigerRecur(m_root);
}

bool Streak::setState(int id, STATE state){
    Search(m_root, id) -> setState(state);
    return true;
}

void Streak::removeDead(){
    removeDeadRecur(m_root);
}

bool Streak::findTiger(int id) const {
    Tiger* temp = m_root;
    while(temp -> m_left != nullptr and 
        temp -> m_right != nullptr){
        if(temp -> m_id == id){
            return true;
        }
        if(temp -> m_id < id){
            temp = temp -> m_right;
        }else{
            temp = temp -> m_left;
        }
    }
    return false;
}

int Streak::countTigerCubs() const{
    int total = 0;
    total = countTigerCubsRecur(m_root);
    return total;
}
