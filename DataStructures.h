#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include "Entity.h"
#include <iostream>

using namespace std;

struct Car;
struct User;
struct Reservation;

//heap//
class ReservationQueue{
private:
    Reservation* arr;
    int size;
    int capacity;
    void resize();
    void upHeap(int index);
    void downHeap(int index);
public:
    ReservationQueue();
    ~ReservationQueue();
    void push(Reservation r);
    Reservation pop();
    bool isEmpty();
    Reservation prior();

};


//DoublyLinkedlist//
template<typename T>
struct Node{
    T* data;
    Node* next;
    Node* prev;
    Node(T* x) : data(x),next(nullptr),prev(nullptr){}
};
template<typename T>
class DoublyLinkedList{
public:
    Node<T>* head;
    Node<T>* tail;

    DoublyLinkedList() : head(nullptr),tail(nullptr){}
    void append(T* data){
        Node<T>* newNode=new Node<T>(data);
        if(head==nullptr){
            head=tail=newNode;
        }
        else{
            newNode->prev=tail;
            tail->next=newNode;
            tail=newNode;
        }
    }
};


//AVL//
struct AVLNode{
    string key;
    AVLNode* left;
    AVLNode* right;
    int height;
    Car* carPtr;
    AVLNode(string k, Car* c);
};
class AVLTree{
private:
    AVLNode* root;
    int height(AVLNode* node);
    AVLNode* rightRotate(AVLNode* n);
    AVLNode* leftRotate(AVLNode* n);
    int getBalance(AVLNode* x);
    AVLNode* insert(AVLNode* node, string key, Car* car);
    Car* search(AVLNode* root, string key);
    int max(int a, int b);
public:
    AVLTree();
    void insert(string key,Car* car);
    Car* search(string key);
};



//hash table//
struct hashNode{
    string key;//username
    hashNode* next;
    User* userPtr;
    hashNode(string k, User* ptr);
};
class hashTable{
private:
    static const int TableSize=103;
    hashNode* table[TableSize];

    int hashIndex(string key);
public:
    hashTable();
    //~hashTable();
    void insert(string key , User* user);
    User* search(string key);
};




#endif