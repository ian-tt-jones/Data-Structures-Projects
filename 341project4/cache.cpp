// CMSC 341 - Fall 2022 - Project 4
#include "cache.h"
Cache::Cache(int size, hash_fn hash){
    if(size >= MINPRIME and size <= MAXPRIME){
        if(isPrime(size)){
            m_currentCap = size;
        }
        else{
            m_currentCap = findNextPrime(size);
        }
    }
    else if(size < MINPRIME){
        m_currentCap = MINPRIME;
    }
    else if(size > MAXPRIME){
        m_currentCap = MAXPRIME;
    }

    m_hash = hash;
    m_currentSize = 0;
    m_currentTable = new Person[m_currentCap];
    m_currNumDeleted = 0;
    m_oldCap = 0;
    m_oldSize = 0;
    m_oldNumDeleted = 0;
    m_oldTable = nullptr;
}

Cache::~Cache(){
    delete[] m_currentTable;
    delete[] m_oldTable;
}

bool Cache::insert(Person person){
    bool inserted = false;
    int i = 0;
    int index = 0;
    while(not inserted){
        index = ((m_hash(person.getKey()) % m_currentCap) + (i * i)) % m_currentCap;
        if(m_currentTable[index].getKey() == ""){
            m_currentTable[index] = person;
            inserted = true;
            m_currentSize++;
        }else{
            i++;
        }
    }
    if(lambda() >= .5){
        rehash();
    }
    return true;
}

bool Cache::remove(Person person){
    bool removed = false;
    int i = 0;
    int index = 0;
    while(not removed){
        index = ((m_hash(person.getKey()) % m_currentCap) + (i * i)) % m_currentCap;
        if(m_currentTable[index].getKey() == person.getKey()){
            m_currentTable[index] = DELETED;
            removed = true;
            m_currNumDeleted++;
            if(m_oldSize > 0){
                transferData();
            }else{
                if(deletedRatio() >= .8){
                    rehash();
                }
            }   
            return true;
        }else{
            i++;
        }
    }
    return false;
}

Person Cache::getPerson(string key, int id) const{
    int elementsSearched = 0;
    int index = 0;
    int i = 0;
    bool personFound = false;
    while(not personFound){
        index = ((m_hash(key) % m_currentCap) + (i * i)) % m_currentCap;
        if(m_currentTable[index].getID() == id){
            return m_currentTable[index];
        }
        i++;
        elementsSearched++;
        if(elementsSearched > m_currentSize){
            personFound = true;
        }
    }
    if(m_oldSize > 0){
        for(int i = 0; i < m_oldSize; i++){
            index = ((m_hash(key) % m_oldCap) + (i * i)) % m_oldCap;
            if(m_oldTable[index].getID() == id){
                return m_oldTable[index];
            }
        }
    }
    Person p;
    return p;
}

float Cache::lambda() const {
    return float(m_currentSize) / float(m_currentCap);
}

float Cache::deletedRatio() const {
    return float(m_currNumDeleted) / float(m_currentSize);
}

void Cache::rehash(){
    m_oldCap = m_currentCap;
    m_oldSize = m_currentSize;
    m_oldNumDeleted = m_currNumDeleted;
    m_currentCap = findNextPrime(4 * (m_currentSize - m_currNumDeleted));
    m_currentSize = 0;
    m_currNumDeleted = 0;
    m_oldTable = m_currentTable;
    m_currentTable = nullptr;
    m_currentTable = new Person[m_currentCap];
    transferData();
}

void Cache::transferData(){
    int toTransfer = m_oldSize - m_oldNumDeleted;
    float ratio = toTransfer / m_oldCap;
    // transfers the rest if there is 25% or less remaining
    if(ratio <= .25){
        for(int i = 0; i < m_oldCap; i++){
            if(m_oldTable[i].getKey() != "" and m_oldTable[i].getKey() != "DELETED"){
                insert(m_oldTable[i]);
                m_oldTable[i] = DELETED;
                m_oldNumDeleted++;
            }
        }
        delete[] m_oldTable;
        m_oldSize = 0;
        m_oldNumDeleted = 0;
        m_oldCap = 0;
    }else{
        // transfers 25% if more than 25% remains
        toTransfer = m_oldCap / 4;
        int i = 0;
        while(toTransfer > 0){
            if(m_oldTable[i].getKey() != "" and m_oldTable[i].getKey() != "DELETED"){
                insert(m_oldTable[i]);
                m_oldTable[i] = DELETED;
                toTransfer--;
                m_oldNumDeleted++;
            }
        }
    }
}

void Cache::dump() const {
    cout << "Dump for the current table: " << endl;
    if (m_currentTable != nullptr)
        for (int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for the old table: " << endl;
    if (m_oldTable != nullptr)
        for (int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool Cache::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int Cache::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

ostream& operator<<(ostream& sout, const Person &person ) {
    if (!person.m_key.empty())
        sout << person.m_key << " (ID " << person.m_id << ")";
    else
        sout << "";
  return sout;
}

bool operator==(const Person& lhs, const Person& rhs){
    return ((lhs.m_key == rhs.m_key) && (lhs.m_id == rhs.m_id));
}
