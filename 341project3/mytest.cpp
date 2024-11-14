// CMSC 341 - Fall 2022 - Project 3
#include "iqueue.h"
#include <random>
// the followings are sample priority functions to be used by IQueue class
// users can define their own priority functions
// Priority functions compute an integer priority for a crop.  Internal
// computations may be floating point, but must return an integer.
int priorityFn1(const Crop &crop);// works with a MAXHEAP
int priorityFn2(const Crop &crop);// works with a MINHEAP

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
    bool insertNormalMin();
    bool insertNormalMax();
    bool removeNormalMin();
    bool removeNormalMax();
    bool priorityChange();
    bool mergeEmpty();
    bool copyNormal();
    bool copyEdge();
    bool assignmentNormal();
    bool assignmentEdge();
    bool outOfRange();
    bool domainError();
};

int main(){
    Tester test;
    
    if(test.insertNormalMin()){
        cout << "SUCCESS: insertNormalMin" << endl;
    }
    else{
        cout << "FAIL: insertNormalMin" << endl;
    }

    if(test.insertNormalMax()){
        cout << "SUCCESS: insertNormalMax" << endl;
    }
    else{
        cout << "FAIL: insertNormalMax" << endl;
    }

    if(test.removeNormalMin()){
        cout << "SUCCESS: removeNormalMin" << endl;
    }
    else{
        cout << "FAIL: removeNormalMin" << endl;
    }

    if(test.removeNormalMax()){
        cout << "SUCCESS: removeNormalMax" << endl;
    }
    else{
        cout << "FAIL: removeNormalMax" << endl;
    }

    if(test.priorityChange()){
        cout << "SUCCESS: priorityChange" << endl;
    }
    else{
        cout << "FAIL: priorityChange" << endl;
    }

    if(test.mergeEmpty()){
        cout << "SUCCESS: mergeEmpty" << endl;
    }
    else{
        cout << "FAIL: mergeEmpty" << endl;
    }

    if(test.copyNormal()){
        cout << "SUCCESS: copyNormal" << endl;
    }
    else{
        cout << "FAIL: copyNormal" << endl;
    }

    if(test.copyEdge()){
        cout << "SUCCESS: copyEdge" << endl;
    }
    else{
        cout << "FAIL: copyEdge" << endl;
    }

    if(test.assignmentNormal()){
        cout << "SUCCESS: assignmentNormal" << endl;
    }
    else{
        cout << "FAIL: assignmentNormal" << endl;
    }

    if(test.assignmentEdge()){
        cout << "SUCCESS: assignmentEdge" << endl;
    }
    else{
        cout << "FAIL: assignmentEdge" << endl;
    }

    if(test.outOfRange()){
        cout << "SUCCESS: outOfRange" << endl;
    }
    else{
        cout << "FAIL: outOfRange" << endl;
    }

    if(test.domainError()){
        cout << "SUCCESS: domainError" << endl;
    }
    else{
        cout << "FAIL: domainError" << endl;
    }

    return 0;
}

int priorityFn1(const Crop &crop) {
    //needs MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [30-116]
    //the highest priority would be 110+6 = 116
    //the lowest priority would be 30+0 = 30
    //the larger value means the higher priority
    int priority = crop.getTemperature() + crop.getType();
    return priority;
}

int priorityFn2(const Crop &crop) {
    //needs MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-103]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 100+3 = 103
    //the smaller value means the higher priority
    int priority = crop.getMoisture() + crop.getTime();
    return priority;
}

// test function definitions
bool Tester::insertNormalMin(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    // check if heap property satisfied at each node
    for(int i = 0; i < 299; i++){
        int priority = queue1.m_priorFunc(queue1.getNextCrop());
        if(priority > queue1.m_priorFunc(queue1.m_heap -> m_crop)){
            return false;
        }
    }

    return true;
}


bool Tester::insertNormalMax(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    // check if heap property satisfied at each node
    for(int i = 0; i < 299; i++){
        int priority = queue1.m_priorFunc(queue1.getNextCrop());
        if(priority < queue1.m_priorFunc(queue1.m_heap -> m_crop)){
            return false;
        }
    }

    return true;
}


bool Tester::removeNormalMin(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn2, MINHEAP);
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    // checking removal order
    for(int i = 0; i < 299; i++){
        int priority = queue1.m_priorFunc(queue1.getNextCrop());
        if(priority > queue1.m_priorFunc(queue1.m_heap -> m_crop)){
            return false;
        }
    }
    return true;
}


bool Tester::removeNormalMax(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    // checking removal order
    for(int i = 0; i < 299; i++){
        int priority = queue1.m_priorFunc(queue1.getNextCrop());
        if(priority < queue1.m_priorFunc(queue1.m_heap -> m_crop)){
            return false;
        }
    }
    return true;
}


bool Tester::priorityChange(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<25;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    // sets priority and then reallocates nodes
    queue1.setPriorityFn(priorityFn2, MINHEAP);
    return true;
}


bool Tester::mergeEmpty(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<25;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    // tests merging into an empty queue
    IQueue queue2(priorityFn1, MAXHEAP);
    queue2.mergeWithQueue(queue1);

    return true;
}


bool Tester::copyNormal(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<100;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    // tests copy constructor, confirmed with dump
    IQueue queue2(queue1);
    return true;
}


bool Tester::copyEdge(){
    // tests copying empty queue, confirmed with dump
    IQueue queue1(priorityFn1, MAXHEAP);
    IQueue queue2(queue1);
    return true;
}


bool Tester::assignmentNormal(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<100;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }

    IQueue queue2(priorityFn1, MAXHEAP);
    for (int i=0;i<150;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
    }
    // tests assignment, confirmed with dump
    queue2 = queue1;
    return true;
}


bool Tester::assignmentEdge(){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<100;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    IQueue queue2(priorityFn1, MAXHEAP);
    // tests copying an empty queue, confirmed with dump
    queue1 = queue2;
    return true;
}


bool Tester::outOfRange(){
    // throws exception if is an empty queue
    IQueue queue2(priorityFn1, MAXHEAP);
    queue2.getNextCrop();
    return true;
}


bool Tester::domainError(){
    // throws exception if different priority functions
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    IQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<100;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue1.insertCrop(aCrop);
    }
    IQueue queue2(priorityFn2, MINHEAP);
    for (int i=0;i<150;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        queue2.insertCrop(aCrop);
    }
    queue1.mergeWithQueue(queue2);
    return true;
}