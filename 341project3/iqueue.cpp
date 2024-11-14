// CMSC 341 - Fall 2022 - Project 3
#include "iqueue.h"
IQueue::IQueue(prifn_t priFn, HEAPTYPE heapType)
{
  m_heap = nullptr;
  m_size = 0;
  m_priorFunc = priFn;
  m_heapType = heapType;
}

IQueue::~IQueue(){
  clear();
}

IQueue::IQueue(const IQueue& rhs){
  m_heap = copyRecur(rhs.m_heap);
}

IQueue& IQueue::operator=(const IQueue& rhs){
  // check for self assign first
  clear();
  m_heap = copyRecur(rhs.m_heap);
  return *this;
}

void IQueue::insertCrop(const Crop& crop) {
    Node* n = new Node(crop);
    m_heap = mergeRecur(m_heap, n);
    m_size++;
}

Crop IQueue::getNextCrop() {
  // throw exception if empty
  try{
    // remove root and return it
    if(m_size == 0){
      throw out_of_range("out_of_range exception");
    }
    Crop temp = m_heap -> m_crop;
    Node* left = m_heap -> m_left;
    Node* right = m_heap -> m_right;
    m_heap -> m_right = nullptr;
    m_heap -> m_left = nullptr;
    delete m_heap;
    m_heap = mergeRecur(left, right);
    m_size--;
    return temp;
  }
  catch(out_of_range const&){
    cout << "out_of_range exception" << endl;
  }
}

void IQueue::mergeWithQueue(IQueue& rhs) {
  try{
    if(rhs.m_priorFunc != m_priorFunc){
      throw domain_error("domain_error exception");
    }
    if(m_size > 0){
      m_heap = mergeRecur(m_heap, rhs.m_heap);
    }
  }
  catch(domain_error const&){
    cout << "domain_error exception" << endl;
  }
}

void IQueue::clear() {
  clearRecur(m_heap);
  m_heap = nullptr;
  m_size = 0;
}

int IQueue::numCrops() const{
  return m_size;
}

void IQueue::printCropsQueue() const {
  printCropsQueueRecur(m_heap);
}

prifn_t IQueue::getPriorityFn() const {
  return m_priorFunc;
}

void IQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
  m_priorFunc = priFn;
  m_heapType = heapType;
  IQueue temp(priFn, heapType);
  priorityShift(temp, m_heap);
  *this = temp;
}

void IQueue::dump() const{
  if (m_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(m_heap);
    cout << endl;
  }
}

void IQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    cout << m_priorFunc(pos->m_crop) << ":" << pos->m_crop.getCropID();
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Crop& crop) {
  sout << "Crop ID: " << crop.getCropID() 
        << ", current temperature: " << crop.getTemperature()
        << ", current soil moisture: " << crop.getMoisture() << "%"
        << ", current time: " << crop.getTimeString()
        << ", plant type: " << crop.getTypeString();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getCrop();
  return sout;
}
