// UMBC - CMSC 341 - Fall 2022 - Proj2
#include "streak.h"

Streak::Streak(){
    m_root = nullptr;
}

Streak::~Streak(){
    clear();
}

void Streak::insert(const Tiger& tiger){
    Tiger* temp = m_root;
    bool instered = false;
    while(!instered){
        if(temp -> m_id < tiger -> m_id){
            if(tiger -> m_right == nullptr){
                temp -> setRight(tiger);
                inserted = true;
            }else{
                temp = temp -> m_right;
            }
        }else{
            if(tiger -> m_left == nullptr){
                temp -> setLeft(tiger);
                instered = true;
            }else{
                temp = temp -> m_left;
            }
        }
    }
}

void Streak::clear(){
    clearTree(m_root);
    m_root = nullptr;
}

void Streak::remove(int id){
    delete search(id);
}

void Streak::updateHeight(Tiger* aTiger){
    
}

int Streak::checkImbalance(Tiger* aTiger){
    
}

Tiger* Streak::rebalance(Tiger* aTiger){
    
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

}

bool Streak::setState(int id, STATE state){
    search(id) -> setState(state);
}

void Streak::removeDead(){
    
}

bool Streak::findTiger(int id) const {
    return findTigerRecur()
}

int Streak::countTigerCubs() const{
    
}
