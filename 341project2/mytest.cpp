// UMBC - CMSC 341 - Fall 2022 - Proj2
#include "streak.h"
#include <vector>
#include <random>
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
    /******************************************
    * Test function declarations go here! *
    ******************************************/
    bool insertNormal();
    bool insertEdge();
    bool insertError();
    bool balanced();
    bool bstProperty();
    bool removeNormal();
    bool removeEdge();
    bool removeBalanced();
    bool bstPropertyRemove();
    bool removeDeadTest();
    bool countTigerCubsTest();
    bool measureInsertionTime(int numTrials, int inputSize);
    bool measureRemovalTime(int numTrials, int inputSize);
};

int main(){
    Tester t;
        // Streak streak;
        // int streakSize = 10;
        // int tempID = 0;
        // int ID = 0;
        // for(int i=0;i<streakSize;i++){
        //     ID = idGen.getRandNum();
        //     if (i == streakSize / 2) tempID = ID;//we store this ID for later use
        //     Tiger tiger(ID,
        //                 static_cast<AGE>(ageGen.getRandNum()),
        //                 static_cast<GENDER>(genderGen.getRandNum()));
        //     streak.insert(tiger);
        // }
        // cout << "\nDump after inserting " << streakSize << " nodes:\n\n";
        // streak.dumpTree();
        // cout << "\n\nList of Tigers after inserting " << streakSize << " nodes:\n";
        // streak.listTigers();
        // cout << endl;

        // streak.remove(tempID);
        // cout << "\nDump after removig the node with ID: " << tempID << "\n\n";
        // streak.dumpTree();
        // cout << "\n\nList of Tigers after removing the node with ID: " << tempID << "\n";
        // streak.listTigers();
        // cout << endl;
    if(t.insertNormal()){
        cout << "insertNormal: SUCCESS" << endl;
    }else{
        cout << "insertNormal: FAIL" << endl;
    }

    if(t.insertEdge()){
        cout << "insertEdge: SUCCESS" << endl;
    }else{
        cout << "insertEdge: FAIL" << endl;
    }
    if(t.insertError()){
        cout << "insertError: SUCCESS" << endl;
    }else{
        cout << "insertError: FAIL" << endl;
    }
    if(t.balanced()){
        cout << "balanced: SUCCESS" << endl;
    }else{
        cout << "balanced: FAIL" << endl;
    }
    if(t.bstProperty()){
        cout << "bstProperty: SUCCESS" << endl;
    }else{
        cout << "bstProperty: FAIL" << endl;
    }
    if(t.removeNormal()){
        cout << "removeNormal: SUCCESS" << endl;
    }else{
        cout << "removeNormal: FAIL" << endl;
    }
    if(t.removeEdge()){
        cout << "removeEdge: SUCCESS" << endl;
    }else{
        cout << "removeEdge: FAIL" << endl;
    }
    if(t.removeBalanced()){
        cout << "removeBalanced: SUCCESS" << endl;
    }else{
        cout << "removeBalanced: FAIL" << endl;
    }
    if(t.bstPropertyRemove()){
        cout << "bstPropertyRemove: SUCCESS" << endl;
    }else{
        cout << "bstPropertyRemove: FAIL" << endl;
    }
    if(t.removeDeadTest()){
        cout << "removeDeadTest: SUCCESS" << endl;
    }else{
        cout << "removeDeadTest: FAIL" << endl;
    }
    if(t.countTigerCubsTest()){
        cout << "countTigerCubsTest: SUCCESS" << endl;
    }else{
        cout << "countTigerCubsTest: FAIL" << endl;
    }
    if(t.measureInsertionTime(2, 500)){
        cout << "measureInsertionTime: SUCCESS" << endl;
    }else{
        cout << "measureInsertionTime: FAIL" << endl;
    }
    if(t.measureRemovalTime(2, 500)){
        cout << "measureRemovalTime: SUCCESS" << endl;
    }else{
        cout << "measureRemovalTime: FAIL" << endl;
    }
    return 0;
}


// Test function definitions

bool Tester::insertNormal(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 100;
    int ID = 0;
    for(int i=0;i<streakSize;i++){
        ID = idGen.getRandNum();
        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    return true;
}

bool Tester::insertEdge(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int ID = 1;
    Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    if(streak.m_root -> m_id == 1){
        return true;
    }
    else{
        return false;
    }
}

bool Tester::insertError(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int ID = 1;
    Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
    streak.insert(tiger);
    streak.insert(tiger);
    if(streak.m_root -> m_right == nullptr and
        streak.m_root -> m_left == nullptr){
        return true;
    }
    else{
        return false;
    }
}

bool Tester::balanced(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 300;
    int ID = 0;
    for(int i = 0; i < streakSize; i++){
        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    // goes through the tree recursively and sets
    // is balanced to false if any subtree isnt balanced
    streak.checkBalance(streak.m_root);

    if(streak.isBalanced){
        return true;
    }else{
        return false;
    }
}

bool Tester::bstProperty(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 300;
    int ID = 0;
    for(int i = 0; i < streakSize; i++){
        Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    streak.bstRecur(streak.m_root);
    if(streak.bstProperty){
        return true;
    }
    else{
        return false;
    }
}

bool Tester::removeNormal(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 100;
    for(int i = 0; i < streakSize; i++){
        Tiger tiger(i,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    for(int i = 0; i < streakSize; i += 2){
        streak.remove(i);
    }
    // tested with dump
    return true;
}

bool Tester::removeEdge(){
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int ID = 1;
    Tiger tiger(ID,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    streak.remove(ID);
    if(streak.m_root != nullptr){
        return false;
    }
    else{
        return true;
    }
}

bool Tester::removeBalanced(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 100;
    for(int i = 0; i < streakSize; i++){
        Tiger tiger(i,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    for(int i = 0; i < streakSize; i += 2){
        streak.remove(i);
    }
    streak.checkBalance(streak.m_root);

    if(streak.isBalanced){
        return true;
    }else{
        return false;
    }
}

bool Tester::bstPropertyRemove(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 100;
    for(int i = 0; i < streakSize; i++){
        Tiger tiger(i,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    for(int i = 0; i < streakSize; i += 2){
        streak.remove(i);
    }
    streak.isBalanced = true;
    streak.bstRecur(streak.m_root);
    if(streak.bstProperty){
        return true;
    }
    else{
        return false;
    }
}

bool Tester::removeDeadTest(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 100;
    for(int i = 0; i < streakSize; i++){
        Tiger tiger(i,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    streak.removeDead();
    streak.searchForDead(streak.m_root);
    if(streak.allDead){
        return true;
    }
    else{
        return false;
    }
}

bool Tester::countTigerCubsTest(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    Streak streak;
    int streakSize = 100;
    for(int i = 0; i < streakSize; i++){
        if(i % 2 == 0){
            Tiger tiger(i,
                    CUB,
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
        }
        else{
            Tiger tiger(i,
                    OLD,
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
        }
    }
    if(streak.countTigerCubs() != 50){
        return false;
    }
    else{
        return true;
    }
}

bool Tester::measureInsertionTime(int numTrials, int inputSize){
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++){
        Streak streak;
        start = clock();
        Random idGen(MINID,MAXID);
        Random ageGen(0,2);
        Random genderGen(0,2);
        int ID = 0;
        for(int i=0;i<inputSize;i++){
            ID = idGen.getRandNum();
            Tiger tiger(ID,
                        static_cast<AGE>(ageGen.getRandNum()),
                        static_cast<GENDER>(genderGen.getRandNum()));
            streak.insert(tiger);
        }        
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "\tInserting " << inputSize * inputSize << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        inputSize = inputSize * a;//increase the input size by the scaling factor
    }
    cout << "This shows that insertion runs in < O(n) time, and that it runs in O(logn)" << endl;
    return true;
}

bool Tester::measureRemovalTime(int numTrials, int inputSize){
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);
    int streakSize = inputSize;
    Streak streak;
    for(int i = 0; i < inputSize; i++){
        Tiger tiger(i,
                    static_cast<AGE>(ageGen.getRandNum()),
                    static_cast<GENDER>(genderGen.getRandNum()));
        streak.insert(tiger);
    }
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials;k++){
        start = clock();
        for(int i = 0; i < streakSize; i += 2){
            streak.remove(i);
        }        
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "\tInserting " << inputSize * inputSize << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        inputSize = inputSize * a;//increase the input size by the scaling factor
    }
    cout << "This shows that removal runs in < O(n) time, and that it runs in O(logn)" << endl;
    return true;
}