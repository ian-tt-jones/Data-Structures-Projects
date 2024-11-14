//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
#include "railroad.h"

class Tester{ // Tester class to implement test functions
    public:

    /**************************************
    * Test function declarations go here! *
    **************************************/
    bool extendAtHeadNormal();
    bool extendAtHeadError();
    bool extendAtTailNormal();
    bool extendAtTailError();
    bool removeStationNormal();
    bool removeStationError();
    bool assignmentOperator();
    bool assignmentOperatorEdge();
    bool copyConstructor();
    bool copyConstructorEdge();
};

int main(){
    Tester test;
    if(test.extendAtHeadNormal()){
        cout << "SUCCESS: normal head extend" << endl;
    }else{
        cout << "FAIL: normal head extend" << endl;
    }
    if(test.extendAtHeadNormal()){
        cout << "SUCCESS: error head extend" << endl;
    }else{
        cout << "FAIL: error head extend" << endl;
    }

    if(test.extendAtHeadError()){
        cout << "SUCCESS: error head extend" << endl;
    }else{
        cout << "FAIL: error head extend" << endl;
    }

    if(test.extendAtTailNormal()){
        cout << "SUCCESS: normal tail extend" << endl;
    }else{
        cout << "FAIL: normal tail extend" << endl;
    }

    if(test.extendAtTailError()){
        cout << "SUCCESS: error tail extend" << endl;
    }else{
        cout << "FAIL: error tail extend" << endl;
    }

    if(test.removeStationNormal()){
        cout << "SUCCESS: remove station Normal" << endl;
    }else{
        cout << "FAIL: remove station Normal" << endl;
    }

    if(test.removeStationError()){
        cout << "SUCCESS: remove station Error" << endl;
    }else{
        cout << "FAIL: remove station Error" << endl;
    }

    if(test.assignmentOperator()){
        cout << "SUCCESS: assignmentOperator" << endl;
    }else{
        cout << "FAIL: assignmentOperator" << endl;
    }

    if(test.assignmentOperatorEdge()){
        cout << "SUCCESS: assignmentOperatorEdge" << endl;
    }else{
        cout << "FAIL: assignmentOperatorEdge" << endl;
    }

    if(test.copyConstructor()){
        cout << "SUCCESS: copyConstructor" << endl;
    }else{
        cout << "FAIL: copyConstructor" << endl;
    }

    if(test.copyConstructorEdge()){
        cout << "SUCCESS: copyConstructorEdge" << endl;
    }else{
        cout << "FAIL: copyConstructorEdge" << endl;
    }
    // Railroad aNetwork;
    // for (int i=1;i<10;i++)
    //     aNetwork.extendAtTail(i,i*2);
    // aNetwork.dump();
    // cout << "Create a route [(2,NORTH),(5,SOUTH),(8,NONE)]\n\n";
    // list<pair<int,DIRECTION>> aRoute;
    // aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    // aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
    // aRoute.push_back(pair<int,DIRECTION>(8,NONE));
    // aNetwork.makeRoute(aRoute);
    // cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    // cout << "\nDump of the list:\n\n";
    // aNetwork.dump();
    // cout << "\n\nRemove node 5.\n\n";
    // aNetwork.removeStation(5);
    // cout << "Removing node 5 invalidates the route passing through 5.\n\n";
    // cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    // cout << "\nDump of the list:\n\n";
    // aNetwork.dump();
    // return 0;
}


bool Tester::extendAtHeadNormal(){
    Railroad net;
    for(int i = 1; i < 301; i++){
        if(!net.extendAtHead(i, i*2)){
            return false;
        }
    }
    return true;
}

bool Tester::extendAtHeadError(){
    Railroad net;
    if(!net.extendAtHead(-5, 5)){
        return true;
    }
    return false;
}

bool Tester::extendAtTailNormal(){
    Railroad net;
    for(int i = 1; i < 301; i++){
        if(!net.extendAtTail(i, i*2)){
            return false;
        }
    }
    return true;
}

bool Tester::extendAtTailError(){
    Railroad net;
    if(!net.extendAtTail(-5, 5)){
        return true;
    }
    return false;
}

bool Tester::removeStationNormal(){
    Railroad net;
    for(int i = 1; i < 99; i++){
        net.extendAtTail(i, i*2);
    }
    for(int i = 1; i < 99; i++){
        if(!net.removeStation(i)){
            return false;
        }
    }
    return true;
}

bool Tester::removeStationError(){
    Railroad net;
    for(int i = 1; i < 3; i++){
        net.extendAtTail(i, i*2);
    }

    if(!net.removeStation(20)){
        return true;
    }
    return false;
}

bool Tester::assignmentOperator(){
    Railroad net;
    for(int i = 1; i < 50; i++){
        net.extendAtTail(i, i*2);
    }

    Railroad net2;
    for(int i = 50; i < 100; i++){
        net2.extendAtTail(i, i*2);
    }

    net2 = net;
    
    if(net.m_numStations != net2.m_numStations){
        return false;
    }

    Station* temp = net.m_head;
    Station* temp2 = net2.m_head;

    while(temp != nullptr){
        if(temp -> getStationCode() != temp2 -> getStationCode()){
            return false;
        }
        if(temp -> getNumPassegers() != temp2 -> getNumPassegers()){
            return false;
        }
        if(!(temp -> getNext() == nullptr) && (temp2 -> getNext() == nullptr)){
            if(temp -> getNext() -> getStationCode() != temp2 -> getNext() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getPrevious() == nullptr) && (temp2 -> getPrevious() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getNorth() == nullptr) && (temp2 -> getNorth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getSouth() == nullptr) && (temp2 -> getSouth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getEast() == nullptr) && (temp2 -> getEast() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getWest() == nullptr) && (temp2 -> getWest() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        temp = temp -> getNext();
        temp2 = temp2 -> getNext();
    }

    return true;
}

bool Tester::assignmentOperatorEdge(){
        Railroad net;
    for(int i = 1; i < 2; i++){
        net.extendAtTail(i, i*2);
    }

    Railroad net2;
    for(int i = 2; i < 4; i++){
        net2.extendAtTail(i, i*2);
    }

    net2 = net;
    
    if(net.m_numStations != net2.m_numStations){
        return false;
    }

    Station* temp = net.m_head;
    Station* temp2 = net2.m_head;

    while(temp != nullptr){
        if(temp -> getStationCode() != temp2 -> getStationCode()){
            return false;
        }
        if(temp -> getNumPassegers() != temp2 -> getNumPassegers()){
            return false;
        }
        if(!(temp -> getNext() == nullptr) && (temp2 -> getNext() == nullptr)){
            if(temp -> getNext() -> getStationCode() != temp2 -> getNext() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getPrevious() == nullptr) && (temp2 -> getPrevious() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getNorth() == nullptr) && (temp2 -> getNorth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getSouth() == nullptr) && (temp2 -> getSouth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getEast() == nullptr) && (temp2 -> getEast() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getWest() == nullptr) && (temp2 -> getWest() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        temp = temp -> getNext();
        temp2 = temp2 -> getNext();
    }

    return true;
}

bool Tester::copyConstructor(){
    Railroad net;
    for(int i = 1; i < 50; i++){
        net.extendAtTail(i, i*2);
    }

    Railroad net2 = Railroad(net);
    
    if(net.m_numStations != net2.m_numStations){
        return false;
    }

    Station* temp = net.m_head;
    Station* temp2 = net2.m_head;

    while(temp != nullptr){
        if(temp -> getStationCode() != temp2 -> getStationCode()){
            return false;
        }
        if(temp -> getNumPassegers() != temp2 -> getNumPassegers()){
            return false;
        }
        if(!(temp -> getNext() == nullptr) && (temp2 -> getNext() == nullptr)){
            if(temp -> getNext() -> getStationCode() != temp2 -> getNext() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getPrevious() == nullptr) && (temp2 -> getPrevious() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getNorth() == nullptr) && (temp2 -> getNorth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getSouth() == nullptr) && (temp2 -> getSouth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getEast() == nullptr) && (temp2 -> getEast() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getWest() == nullptr) && (temp2 -> getWest() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        temp = temp -> getNext();
        temp2 = temp2 -> getNext();
    }

    return true;
}

bool Tester::copyConstructorEdge(){
    Railroad net;
    for(int i = 1; i < 2; i++){
        net.extendAtTail(i, i*2);
    }

    Railroad net2 = Railroad(net);
    
    if(net.m_numStations != net2.m_numStations){
        return false;
    }

    Station* temp = net.m_head;
    Station* temp2 = net2.m_head;

    while(temp != nullptr){
        if(temp -> getStationCode() != temp2 -> getStationCode()){
            return false;
        }
        if(temp -> getNumPassegers() != temp2 -> getNumPassegers()){
            return false;
        }
        if(!(temp -> getNext() == nullptr) && (temp2 -> getNext() == nullptr)){
            if(temp -> getNext() -> getStationCode() != temp2 -> getNext() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getPrevious() == nullptr) && (temp2 -> getPrevious() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getNorth() == nullptr) && (temp2 -> getNorth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getSouth() == nullptr) && (temp2 -> getSouth() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getEast() == nullptr) && (temp2 -> getEast() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        if(!(temp -> getWest() == nullptr) && (temp2 -> getWest() == nullptr)){
            if(temp -> getPrevious() -> getStationCode() != temp2 -> getPrevious() -> getStationCode()){
                return false;
            }
        }
        temp = temp -> getNext();
        temp2 = temp2 -> getNext();
    }

    return true;
}
