#pragma once

template <typename T>
class Vector {
	T* arr;
	int size;
	int index;

public:
	Vector() {

		size = 1;
		index = 0;
		arr = new T[size];

	}
	void delete_entry(int a) {
	
		if (a < index) {
			for (int i = a; i < index-1; i++) {
				arr[i] = arr[i+1];
			}
			index--;
		}
	}
	Vector(int s) {

		size = s;
		index = 0;
		arr = new T[size];

	}
	int get_index() { return index; }
	void put(T sample) {

		if (index >= size) {
			size *= 2;
		T *temp = new T[size];
		
			for (int i = 0; i < size/2; i++) {
				temp[i] = arr[i];

			}
			delete []arr;

			arr = new T[size];


			for (int i = 0; i < size / 2; i++) {
				arr[i] = temp[i];

			}

			arr[index] = sample;


		}
		else {
			arr[index] = sample;
		}
		index++;
	}
	int Size() {
		return index;
	}
	T operator [](int a) {
		

		return arr[a];

	}
	T* return_ptr() {
		return arr;
	}
	int find(T str ) {

		for (int i = 0; i < size; i++) {
		
			if (str== arr[i])
			{
				return i;
			}


		}

		return -1;
	}

};