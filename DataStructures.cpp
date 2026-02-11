#include "DataStructures.h"

//heap//

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




//AVL//

AVLNode::AVLNode(string k, Car* c) : key(k), carPtr(c), left(nullptr), right(nullptr), height(1) {}
AVLTree::AVLTree() : root(nullptr) {}
int AVLTree::height(AVLNode* node){
    if(node==nullptr) return 0;
    return node->height;
}
int AVLTree::max(int a, int b){
    if(a<b) return b;
    else return a;
}
AVLNode* AVLTree::rightRotate(AVLNode* n){
    AVLNode* x=n->left;
    AVLNode* y=x->right;
    x->right=n;
    n->left=y;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
    return x;
}
AVLNode* AVLTree::leftRotate(AVLNode* n){
    AVLNode* y=n->right;
    AVLNode* x=y->left;
    y->left=n;
    n->right=x;
    n->height=max(height(n->left),height(n->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}
int AVLTree::getBalance(AVLNode* N){
    if (N==nullptr) return 0;
    return height(N->left)-height(N->right);
}
void AVLTree::insert(string key, Car* car) {
    root=insert(root, key, car); 
}
AVLNode* AVLTree::insert(AVLNode* node, string key, Car* car){
    if(node==nullptr) return new AVLNode(key,car);
    if(key<node->key){
        node->left=insert(node->left,key,car);
    }
    else if(key>node->key){
        node->right=insert(node->right, key, car);
    }
    else return node;    
    node->height = 1 + max(height(node->left),height(node->right));
    int balance=getBalance(node);
    if(balance>1){
        if(key>node->left->key){
            node->left=leftRotate(node->left);
            return rightRotate(node);
        }
        else{
            return rightRotate(node);
        }
    }
    if(balance<-1){
        if(key<node->right->key){
            node->right=rightRotate(node->right);
            return leftRotate(node);
        }
        else{
            return leftRotate(node);
        }
    }
    return node;
}

Car* AVLTree::search(string key){ 
    return search(root,key); 
}
Car* AVLTree::search(AVLNode* root,string key){
    if(root->key==key) return root->carPtr;
    if (root==nullptr) return nullptr;
    if(root->key<key) return search(root->right,key);
    if (key<root->key) return search(root->left, key);
}



//hash table//

hashNode::hashNode(string k, User* ptr) : key(k), userPtr(ptr), next(nullptr){}

hashTable::hashTable(){
    for(int i=0 ; i<TableSize ; i++){
        table[i]=nullptr;
    }
}
int hashTable::hashIndex(string key){
    return hashString(key) % TableSize;
}
void hashTable::insert(string key , User* user){
    hashNode* newNode=new hashNode(key, user);
    newNode->next=table[hashIndex(key)];
    table[hashIndex(key)]=newNode;
}
User* hashTable::search(string key){
    int index=hashIndex(key);
    hashNode* temp=table[index];
    while(!temp){
        if(temp->key == key){
            return temp->userPtr;
        }
        temp=temp->next;
    }
    return nullptr;
}
