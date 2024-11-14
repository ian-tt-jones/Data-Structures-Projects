// CMSC 341 - Fall 2022 - Project 3
#include "iqueue.h"
IQueue::IQueue(prifn_t priFn, HEAPTYPE heapType)
{
  
}

IQueue::~IQueue()
{
  
}

IQueue::IQueue(const IQueue& rhs)
{
  
}

IQueue& IQueue::operator=(const IQueue& rhs)
{
  
}

void IQueue::insertCrop(const Crop& crop) {
    
}

Crop IQueue::getNextCrop() {
    
}

void IQueue::mergeWithQueue(IQueue& rhs) {
  
}

void IQueue::clear() {
  
}

int IQueue::numCrops() const
{
  
}

void IQueue::printCropsQueue() const {
  
}

prifn_t IQueue::getPriorityFn() const {
  
}

void IQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
                   
}

void IQueue::dump() const
{
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
