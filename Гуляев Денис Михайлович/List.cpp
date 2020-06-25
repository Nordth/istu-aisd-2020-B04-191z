#include "stdio.h"
#include <cstdlib>

struct Data {			
	int value;			
	Data* next = NULL;	
};

struct List{				
							
							
	Data* first = NULL;		

	bool addAtEnd(Data* data) {								
		if (find(data->value)) return false;

		if (!first) {
			first = data;
			return true;
		}

		Data* next;
		next = first;

		while (next->next) {
			next = next->next;
		}

		next->next = data;
		return true;
	}

	Data* find(int value) {									
		if (!first) return NULL;

		Data* next = first;
		if (next->value == value) return next;
		while (next->next) {
			next = next->next;
			if (next->value == value) return next;
		}
		return NULL;
	}

	bool addAfter(Data* after, Data* data) {				
		if (!after) return false;
		if (find(data->value)) return false;

		if (!after->next) {
			after->next = data;
			return true;
		}
		else {
			Data* temp = after->next;
			after->next = data;
			data->next = temp;
			return true;
		}
	}

	bool remove(int value) {								
		Data* removeValue = find(value);
		if (!removeValue) return false;

		Data* parent = first;

		if (parent == removeValue) {
			first = removeValue->next;
			delete removeValue;
			return true;
		}

		while (parent->next) {
			if (parent->next == removeValue) break;
			parent = parent->next;
		}

		parent->next = removeValue->next;
		delete removeValue;
		return true;
	}

	void printAll() {										
		printf("------- PRINT LIST --------\n");
		Data* next = first;
		while (next) {
			printf("%d ", next->value);
			next = next->next;
		}
		printf("\n------- END OF PRINT -------\n");
	}

	void removeListFromMemory() {							
		Data* temp;
		while (first) {
			temp = first;
			first = first->next;
			delete temp;
		}
	}
};

struct Queue {												
	int* arr = NULL;
	int size = 0;
	int start = 0;
	int end = 0;

	bool init(int bufferSize) {								
		if (arr) return false;
		if (bufferSize < 1) return false;

		arr = new int[(unsigned int) bufferSize+1];
		size = bufferSize+1;
		return true;
	}

	bool enqueue(int val) {									
		if (((end + 1) % size) == start) return false;
		arr[end] = val;
		end++;
		end = end % size;
		return true;
	}

	bool dequeue(int* arg) {								
		if (!arg) arg = new int;
		if (start == end) {
			*arg = -999;
			return false;
		}
		*arg = arr[start];
		start++;
		start = start % size;
		return true;
	}

	Queue* clone() {										
		Queue* queue = new Queue();
		queue->arr = new int[size];
		queue->size = size;
		queue->start = start;
		queue->end = end;
		for (int i = 0; i < size; i++) {
			queue->arr[i] = arr[i];
		}
		return queue;
	}

	void removeQueueFromMemory() {							
		size = 0;
		end = 0;
		start = 0;
		delete[] arr;
		arr = NULL;
	}
};

Data* newData(int value) {
	Data* data = new Data();
	data->value = value;
	return data;
}

int main() {
	printf("################ CHECK LIST #############\n");
	List list;
	for (int i = 0; i < 10; i++) {
		list.addAtEnd(newData(i));
	}
	list.printAll();
	printf("Remove 7 = %s\n", list.remove(7) ? "true" : "false");
	printf("Remove 6 = %s\n", list.remove(6) ? "true" : "false");
	printf("Remove 99 = %s\n", list.remove(99) ? "true" : "false");
	printf("Remove 0 = %s\n", list.remove(0) ? "true" : "false");
	list.printAll();
	printf("Add value=22 after value=4.\n");
	list.addAfter(list.find(4), newData(22));
	list.printAll();
	printf("Find item with value=4.\n");
	printf("---%d address of value=4\n", (unsigned int) list.find(4));
	printf("Find item with value=99.\n");
	printf("---%d address of value=99.\n", list.find(99));
	printf("Remove list from memory.\n");
	list.removeListFromMemory();
	list.printAll();
	printf("########### END OF CHECK LIST ############\n");
	printf("Press ENTER to continue.");
	getchar();


	printf("########### CHECK QUEUE ###########\n");
	Queue queue;
	int* arg = new int;
	*arg = -999;
	bool isTrue = false;

	printf("Init queue with buffer size = 4 : %s\n", queue.init(4) ? "true" : "false");
	printf("Dequque from empty queue: %s val = %d\n", queue.dequeue(arg) ? "true" : "false", *arg);

	printf("Add 5 elements to queue:\n");
	for (int i = 0; i < 5; i++) {
		printf("Add value = %d : %s\n", i, queue.enqueue(i) ? "true" : "false");
	}

	printf("Press enter to continue.");
	getchar();

	printf("Make clone of queue...\n");
	Queue* queue2 = queue.clone();

	printf("Dequeue 15 elements from queue:\n");
	for (int i = 0; i < 15; i++) {
		isTrue = queue.dequeue(arg);
		printf("Deq. value = %d : %s\n", *arg, isTrue ? "true" : "false");
	}

	printf("Press enter to continue.");
	getchar();

	printf("Remove first queue...\n");
	queue.removeQueueFromMemory();
	printf("Dequeue 2 elements from queue:\n");
	for (int i = 0; i < 2; i++) {
		isTrue = queue.dequeue(arg);
		printf("Deq. value = %d : %s\n", *arg, isTrue ? "true" : "false");
	}

	printf("Press enter to continue.");
	getchar();

	printf("Dequeue 6 elements from clone:\n");
	for (int i = 0; i < 6; i++) {
		isTrue = queue2->dequeue(arg);
		printf("Deq. value = %d : %s\n", *arg, isTrue ? "true" : "false");
	}
}