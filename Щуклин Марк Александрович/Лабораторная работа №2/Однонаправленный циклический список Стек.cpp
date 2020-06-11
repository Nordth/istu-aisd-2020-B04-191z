#include <iostream>


struct Stack
{
	size_t size_of_stack;
	size_t buf;
	int* array;

	// Инициализация
	Stack() : size_of_stack(0), buf(1)
	{
		array = new int[buf];
	}

	// Освобождение памяти от структуры данных
	~Stack()
	{
		delete[] array;
	}

	// Конструктор копирования
	Stack(const Stack& A)
	{
		size_of_stack = A.size_of_stack;
		buf = A.buf;
		array = new int[buf];
		for (size_t i = 0; i < size_of_stack; ++i)
		{
			array[i] = A.array[i];
		}
	}

	// Вставка элемента
	void push(int n)
	{
		if (size_of_stack + 1 > buf)
		{
			int* copy_array = new int[buf];
			for (size_t i = 0; i < size_of_stack; ++i)
			{
				copy_array[i] = array[i];
			}
			delete[] array;
			buf *= 2;
			array = new int[buf];
			for (size_t i = 0; i < size_of_stack; ++i)
			{
				array[i] = copy_array[i];
			}
			delete[] copy_array;
			array[size_of_stack] = n;
			size_of_stack++;
		}
		else
		{
			array[size_of_stack] = n;
			size_of_stack++;
		}
	}

	// Извлечение элемента
	void pop()
	{
		if (size_of_stack == 0)
		{
			std::cout << "false" << std::endl;
		}
		else
		{
			std::cout << array[size_of_stack - 1] << std::endl;
			size_of_stack--;
		}
	}
};


int main()
{
	Stack A;
	A.push(5);
	A.push(4);
	Stack B = A;
	B.pop();
	B.pop();
	B.pop();
	system("PAUSE");
	return 0;
}