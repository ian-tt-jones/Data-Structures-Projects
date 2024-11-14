//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
#include "railroad.h"
Railroad::Railroad(){
    m_numStations = 0;
    m_head = nullptr;
    m_tail =  nullptr;
}

Railroad::~Railroad(){
    clearNetwork();
}

void Railroad::clearNetwork(){
    // delete everything
    clearAllRoutes();
    Station* temp;
    while(m_head != nullptr){
        temp = m_head;
        m_head = m_head -> m_next;
        delete temp;
    }
    m_numStations = 0;
    m_head = nullptr;
    m_tail =  nullptr;
}

bool Railroad::extendAtHead(int newCode, int passengers){
    if(newCode < 1){
        return false;
    }
    if (m_numStations == 0){
        Station* s = new Station(newCode, passengers);
        m_head = s;
        m_tail = s;
        m_numStations++;
    }else{
        Station* temp = m_head;
        while (temp != nullptr){
            if(temp->getStationCode() == newCode){
                return false;
            }
            temp = temp -> m_next;
        }
        temp = m_head;
        Station* s = new Station(newCode, passengers);
        s->setNext(temp);
        temp->setPrevious(s);
        m_head = s;
        m_numStations++;
    }
    return true;
}

bool Railroad::extendAtTail(int newCode, int passengers){
    if(newCode < 1){
        return false;
    }
    if (m_numStations == 0){
        Station* s = new Station(newCode, passengers);
        m_head = s;
        m_tail = s;
        m_numStations++;
    }
    if(m_numStations == 1){
        
    }else{
        Station* temp = m_head;
        while (temp != nullptr){
            cout << temp -> getStationCode();
            if(temp->getStationCode() == newCode){
                return false;
            }
            temp = temp -> m_next;
        }
        temp = m_tail;
        Station* s = new Station(newCode, passengers);
        s->setPrevious(temp);
        temp->setNext(s);
        m_tail = s;
        m_numStations++;
    }
    return true;
}

void Railroad::dump(){
    if (m_head != nullptr){
        int northCode, southCode, eastCode, westCode;
        Station *temp = m_head;
        while(temp != nullptr){
            if (temp->m_north != nullptr) northCode = temp->m_north->m_code;
            else northCode = -1;
            if (temp->m_south != nullptr) southCode = temp->m_south->m_code;
            else southCode = -1;
            if (temp->m_east != nullptr) eastCode = temp->m_east->m_code;
            else eastCode = -1;
            if (temp->m_west != nullptr) westCode = temp->m_west->m_code;
            else westCode = -1;
            cout << temp->m_code << 
                    " (" << 
                    "P: " << temp->m_passengers << 
                    ", N: " << northCode <<
                    ", S: " << southCode <<
                    ", E: " << eastCode <<
                    ", W: " << westCode <<
                    ")" << endl;
            temp = temp->m_next;
        }
    }
}

bool Railroad::makeRoute(list< pair<int,DIRECTION> > route){
    // first checks if the starting station exists
    list< pair<int,DIRECTION> >::iterator it;
    it = route.begin();
    if(it -> first <= m_numStations){
        Station* temp = m_head;
        Station* temp2 = m_head->m_next;
        list< pair<int,DIRECTION> >::iterator it;
        it = route.begin();
        for(int i = 0; i < it -> first; i++){
            temp = temp->getNext();
        }
        for(it = route.begin(); it != route.end(); it++){
            temp = getStation(it -> first);
            it++;
            temp2 = getStation(it -> first);
            if(it -> second == NORTH){
                temp -> m_north = temp2;
            }if(it -> second == SOUTH){
                temp -> m_south = temp2;
            }if(it -> second == EAST){
                temp -> m_east = temp2;
            }if(it -> second == WEST){
                temp -> m_west = temp2;
            }
            it--;
        }
        return true;
    }
    return false;
}

int Railroad::travel(list< pair<int,DIRECTION> > route){
    // traverse route and count passengers
    int passengers = 0;
    list< pair<int,DIRECTION> >::iterator it;
    for(it = route.begin(); it != route.end(); it++){
        Station* temp = getStation(it -> first);
        passengers += temp -> getNumPassegers();
    }    
    return passengers;
}

bool Railroad::setNumPassengers(int code, int passengers){
    Station* temp = m_head;
    while(temp -> getStationCode() != code){
        temp = temp -> m_next;
    }
    temp -> setNumPassengers(passengers);
    return true;
}

bool Railroad::removeStation(int aCode){
    Station* temp = m_head;
    if(temp == nullptr){
        return false;
    }
    if(aCode == temp -> getStationCode()){
        m_head = temp -> m_next;
        delete temp;
        return true;
    }
    while((temp -> getStationCode() != aCode)){
        temp = temp -> m_next;
        if(temp == nullptr){
            return false;
        }
    }
    if(temp == nullptr){
        return false;
    }
    repairRoute(aCode);
    Station* prev = temp -> m_previous;
    Station* next = temp -> m_next;
    if(next != nullptr){
        next -> setPrevious(prev);
    }
    if(prev != nullptr){
        prev -> setNext(next);
    }
    delete temp;
    return true;
}

void Railroad::clearAllRoutes(){
    Station* temp = m_head;
    while(temp != nullptr){
        if(temp -> getNorth() != nullptr){
            temp -> setNorth(nullptr);
        }
        if(temp -> getSouth() != nullptr){
            temp -> setSouth(nullptr);
        }
        if(temp -> getEast() != nullptr){
            temp -> setEast(nullptr);
        }
        if(temp -> getWest() != nullptr){
            temp -> setWest(nullptr);
        }
        temp = temp -> m_next;
    }
}

const Railroad & Railroad::operator=(const Railroad & rhs){
    clearNetwork();
    Station* temp = rhs.m_head;
    Station* temp2;
    while(temp != nullptr){
        extendAtTail(temp -> getStationCode(), temp -> getNumPassegers());
        temp = temp -> m_next;
    }
    temp = rhs.m_head;
    temp2 = m_head;
    while(temp2 != nullptr){
        temp2 -> setNorth(temp -> getNorth());
        temp2 -> setSouth(temp -> getSouth());
        temp2 -> setEast(temp -> getEast());
        temp2 -> setWest(temp -> getWest());
        temp = temp -> m_next;
        temp2 = temp2 -> m_next;
    }
    return *this;
}

Railroad::Railroad(const Railroad & rhs){
    clearNetwork();
    Station* temp = rhs.m_head;
    Station* temp2;
    while(temp != nullptr){
        extendAtTail(temp -> getStationCode(), temp -> getNumPassegers());
        temp = temp -> m_next;
    }
    temp = rhs.m_head;
    temp2 = m_head;
    while(temp2 != nullptr){
        if(temp -> getNorth() != nullptr){
            temp2 -> setNorth(temp -> getNorth());
        }
        if(temp -> getSouth() != nullptr){
            temp2 -> setSouth(temp -> getSouth());
        }
        if(temp -> getEast() != nullptr){
            temp2 -> setEast(temp -> getEast());
        }
        if(temp -> getWest() != nullptr){
            temp2 -> setWest(temp -> getWest());
        }
        temp = temp -> m_next;
        temp2 = temp2 -> m_next;
    }
}