#include "DataStructures.h"

ReservationQueue::ReservationQueue(){
    capacity=15;
    size=0;
    arr=new Reservation[capacity];
}
ReservationQueue::~ReservationQueue(){
    delete[] arr;
}
void ReservationQueue::resize(){
    capacity*=2;
    Reservation* newArr=new Reservation[capacity];
    for(int i=0 ; i<size ; i++){
        newArr[i]=arr[i];
    }
    delete[] arr;
    arr=newArr;
}
void ReservationQueue::upHeap(int index){
    if(index==0) return;
    int parent=(index-1)/2;
    if(arr[parent]>arr[index]){
        swap(arr[parent],arr[index]);
        upHeap(parent);
    }
}
void ReservationQueue::downHeap(int index){
    int lft=(index*2)+1;
    int rght=(index*2)+2;
    int temp=index;
    if(lft<size && arr[temp]>arr[lft]){
        temp=lft;
    }
    if(rght<size && arr[temp]>arr[rght]){
        temp=rght;
    }
    if(temp!=index){
        swap(arr[temp],arr[index]);
        downHeap(temp);
    }
    
}
void ReservationQueue::push(Reservation r){
    if(size==capacity) resize();
    arr[size]=r;
    upHeap(size);
    size++;
}
bool ReservationQueue::isEmpty(){
    return size == 0; 
}
Reservation ReservationQueue::pop(){
    if(size==0) return Reservation({{0,0,0},"",0});
    Reservation prior=arr[0];
    arr[0]=arr[size-1];
    size--;
    downHeap(0);
    return prior;
}
Reservation ReservationQueue::prior() {
    if (size==0) return Reservation({{0,0,0},"",0});
    return arr[0];
}