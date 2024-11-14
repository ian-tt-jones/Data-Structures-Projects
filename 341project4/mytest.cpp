// CMSC 341 - Fall 2022 - Project 4
#include "cache.h"
#include <random>
#include <vector>
const int MINSEARCH = 0;
const int MAXSEARCH = 7;
// the following array defines sample search strings for testing
string searchStr[MAXSEARCH+1]={"c++","python","java","scheme","prolog","c#","c","js"};
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
public:
    bool insertion();
    bool findError();
    bool findColliding();
    bool findNoRehash();
    bool remove();
    bool removeColliding();
    bool rehashTest();
    bool rehashLoadFactor();
    bool rehashRemoval();
    bool rehashDeleteRatio();
};

unsigned int hashCode(const string str);

int main(){
    Tester test;
    if(test.insertion()){
        cout << "SUCCESS: insertion" << endl;
    }else{
        cout << "FAIL: insertion" << endl;
    }

    if(test.findError()){
        cout << "SUCCESS: findError" << endl;
    }else{
        cout << "FAIL: findError" << endl;
    }

    if(test.findColliding()){
        cout << "SUCCESS: findColliding" << endl;
    }else{
        cout << "FAIL: findColliding" << endl;
    }

    if(test.findNoRehash()){
        cout << "SUCCESS: findNoRehash" << endl;
    }else{
        cout << "FAIL: findNoRehash" << endl;
    }

    if(test.remove()){
        cout << "SUCCESS: remove" << endl;
    }else{
        cout << "FAIL: remove" << endl;
    }

    if(test.removeColliding()){
        cout << "SUCCESS: removeColliding" << endl;
    }else{
        cout << "FAIL: removeColliding" << endl;
    }
    return 0;
}

unsigned int hashCode(const string str) {
   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook
   for ( unsigned int i = 0 ; i < str.length(); i++)
      val = val * thirtyThree + str[i] ;
   return val ;
}


bool Tester::insertion(){
    // confirmed with dump

    vector<Person> dataList;
    Cache cache(MINPRIME, hashCode);
    for (int i=0;i<49;i++){
        // generating random data
        Person dataObj = Person(to_string(i), i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }
    return true;
}


bool Tester::findError(){
    vector<Person> dataList;
    Cache cache(MINPRIME, hashCode);
    for (int i=0;i<49;i++){
        // generating random data
        Person dataObj = Person(to_string(i), i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }

    Person p = cache.getPerson("monkey", 1000);
    if(p.getKey() != ""){
        return false;
    }else{
        return true;
    }
}


bool Tester::findColliding(){
    vector<Person> dataList;
    Cache cache(MINPRIME, hashCode);
    for (int i=0;i<49;i++){
        // generating random data
        Person dataObj = Person(to_string(i), i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }

    Person p = cache.getPerson("3", 3);
    Person p1 = cache.getPerson("6", 6);
    Person p2 = cache.getPerson("9", 9);
    Person p3 = cache.getPerson("12", 12);

    if(p.getKey() == "3" and p1.getKey() == "6"
        and p2.getKey() == "9" and p3.getKey() == "12"){
        return true;
    }else{
        return false;
    }
}


bool Tester::findNoRehash(){
    vector<Person> dataList;
    Cache cache(MINPRIME, hashCode);
    for (int i=0;i<49;i++){
        Person dataObj;
        // generating random data
        if(i % 2 == 0){
            dataObj = Person(to_string(i), i);
        }else{
            dataObj = Person("c++", i);
            // saving data for later use
            dataList.push_back(dataObj);
        }
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }
    Person p;
    for (vector<Person>::iterator it = dataList.begin(); it != dataList.end(); it++){
        p = cache.getPerson((*it).getKey(), (*it).getID());
        if(p.getID() != (*it).getID()){
            return false;
        }
    }

    return true;
}


bool Tester::remove(){
    // confirmed with dump

    vector<Person> dataList;
    Cache cache(MINPRIME, hashCode);
    for (int i=0;i<49;i++){
        // generating random data
        Person dataObj = Person(to_string(i), i);
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }
    Person p = cache.getPerson("3", 3);
    Person p1 = cache.getPerson("6", 6);
    Person p2 = cache.getPerson("9", 9);
    Person p3 = cache.getPerson("12", 12);
    
    cache.remove(p);
    cache.remove(p1);
    cache.remove(p2);
    cache.remove(p3);
    return true;
}


bool Tester::removeColliding(){
    // confirmed with dump
    
    vector<Person> dataList;
    Cache cache(MINPRIME, hashCode);
    for (int i=0;i<49;i++){
        Person dataObj;
        // generating random data
        if(i % 2 == 0){
            dataObj = Person(to_string(i), i);
        }else{
            dataObj = Person("c++", i);
            // saving data for later use
            dataList.push_back(dataObj);
        }
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }
    
    for (vector<Person>::iterator it = dataList.begin(); it != dataList.end(); it++){
        cache.remove(*it);
    }
    return true;
}


bool Tester::rehashTest(){
    vector<Person> dataList;
    Random RndID(MINID,MAXID);
    Random RndStr(MINSEARCH,MAXSEARCH);
    Cache cache(MINPRIME, hashCode);
    for (int i=0;i<88;i++){
        // generating random data
        Person dataObj = Person(searchStr[RndStr.getRandNum()], RndID.getRandNum());
        // saving data for later use
        dataList.push_back(dataObj);
        // inserting data in to the Cache object
        cache.insert(dataObj);
    }

    return true;
}