
#include <iostream>
using namespace std;
const int SIZE = 4;

class Queue {
private:

    int firstElementIndex = -1;
    int lastElementIndex = -1;
    
    int *buffer = new int[SIZE];
    
    int dynSize = SIZE;
public:
    Queue()
    {
        int i;
        for(i=0;i<SIZE;i++){
            this->buffer[i] = 0;
        }
    }
    ~Queue() { 
        delete[] this->buffer;
    }
    Queue(const Queue & queue) :
        firstElementIndex(queue.firstElementIndex), lastElementIndex(queue.lastElementIndex), dynSize(queue.dynSize), buffer(queue.buffer)
    {
        int i;
        buffer = new int [queue.dynSize];
        firstElementIndex = queue.firstElementIndex;
        lastElementIndex = queue.lastElementIndex;
        for (i=0;i<queue.dynSize;i++){
            buffer[i] = queue.buffer[i];
        }
        dynSize = queue.dynSize;
        cout << "Object copyring success"<<endl;
    }
    int push(int param){
        int i;int j;
        
        if (this->firstElementIndex != 0){
            this->firstElementIndex = 0;
        }
        
        this->lastElementIndex++;
        
        if (this->lastElementIndex == this->dynSize){
            int *temporaryBuffer;
            temporaryBuffer = new int[this->dynSize];
            for (i=0;i<dynSize;i++){
                temporaryBuffer[i] = this->buffer[i];
            }
            
            delete [] this->buffer;
            
            this->dynSize = this->dynSize * 2;
            
            this->buffer = new int[this->dynSize];
            for (j=0;j<i;j++){
                this->buffer[j] = temporaryBuffer[j];
            }
            delete [] temporaryBuffer;
            cout << "Queue overflow: queue size doubled"<<endl;
            this->buffer[this->lastElementIndex] = param;
            
        } else {
            this->buffer[this->lastElementIndex] = param;
        }
    }
    int front(){
        if (this->firstElementIndex == 0){
            return this->buffer[this->firstElementIndex];
        } else {
            return false;
        }
    }
    int pop(){
        
        if (this->firstElementIndex == 0){
            int i;
            int *temporaryBuffer;
            temporaryBuffer = new int[this->lastElementIndex+1];  
            for (i=1;i<=this->lastElementIndex;i++){
                temporaryBuffer[i-1] = this->buffer[i];
            }
            
            delete [] this->buffer;
            this->buffer = new int[this->dynSize];
            for (i=0;i<lastElementIndex;i++){
                this->buffer[i] = temporaryBuffer[i];
            }
            delete [] temporaryBuffer;
        }
        
    }
};


int main()
{
    cout << "Adding elelments in two small queues:"<<endl;
    Queue queue1;Queue queue2;
    queue1.push(7);queue2.push(8);
    queue1.push(9);queue2.push(10);
    queue1.push(11);queue2.push(12);
    queue1.push(13);queue2.push(14);
    queue1.push(15);queue2.push(16);

    cout <<endl<< "Output first element from queue:"<<endl;
    cout << queue1.front();
    cout <<endl<< "Delete first element from queue:"<<endl;    
    queue1.pop();
    cout <<endl<< "Output first element from queue:"<<endl;
    cout << queue1.front();
    cout <<endl<< "Copyring queue to new queue:"<<endl;
    Queue queue3(queue1);
    

    cout <<endl<< "Output firsts element from first queue and queue copy:"<<endl;
    cout << queue1.front();
    cout << queue3.front();
    
    cout <<endl<< "Delete first element from first queue:"<<endl;
    queue1.pop();
    cout <<endl<< "Output firsts element from first queue and queue copy:"<<endl;
    cout << queue1.front(); 
    cout << queue3.front();
    
    return 0;
}

