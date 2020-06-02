
#include <iostream>
using namespace std;
const int SIZE = 4;

class Queue {
private:

    int firstElementIndex = -1;
    int lastElementIndex = -1;
    
    int *buffer = new int[SIZE];
    int *temporaryBuffer = new int[SIZE];
    
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
    Queue(const Queue &queue) :
        firstElementIndex(queue.firstElementIndex), lastElementIndex(queue.lastElementIndex), dynSize(queue.dynSize), buffer(queue.buffer), temporaryBuffer(queue.temporaryBuffer)
    {
        cout << "Object copyring success"<<endl;
    }
    int push(int param){
        int i;int j;
        if (this->firstElementIndex != 0){
            this->firstElementIndex = 0;
        }
        
        this->lastElementIndex++;
        
        if (this->lastElementIndex == this->dynSize){
            
            delete [] this->temporaryBuffer;
            this->temporaryBuffer = new int[this->dynSize];
            for (i=0;i<dynSize;i++){
                this->temporaryBuffer[i] = this->buffer[i];
            }
            
            delete [] this->buffer;
            
            this->dynSize = this->dynSize * 2;
            
            this->buffer = new int[this->dynSize];
            for (j=0;j<i;j++){
                this->buffer[j] = this->temporaryBuffer[j];
            }

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
            delete [] this->temporaryBuffer;
            this->temporaryBuffer = new int[this->lastElementIndex+1];  
            for (i=1;i<=this->lastElementIndex;i++){
                this->temporaryBuffer[i-1] = this->buffer[i];
            }
            
            delete [] this->buffer;
            this->buffer = new int[this->dynSize];
            for (i=0;i<lastElementIndex;i++){
                this->buffer[i] = this->temporaryBuffer[i];
            }            
        }        
    }
};


int main()
{
    Queue queue1;Queue queue2;
    queue1.push(7);queue2.push(8);
    queue1.push(9);queue2.push(10);
    queue1.push(11);queue2.push(12);
    queue1.push(13);queue2.push(14);
    queue1.push(15);queue2.push(16);

	Queue queue3(queue1);
	
    cout << queue1.front();
    
    queue1.pop();
    
    cout << queue1.front();

    return 0;
}
