#pragma once


template <class T>
class Node {
public:
	T data;
	Node* next;


};
template <class T>

class Linked_list {
public:
	Node<T>* head;

	Linked_list() {
		head = NULL;
	}

	void insert_at_end(T a) {
		Node<T>* newnode = new Node<T>;
		newnode->data = a;
		newnode->next = NULL;

		if (head == NULL) {
			head = newnode;
			///	std::cout << "\n head is null\n";
		}

		else {
			Node<T>* temp = head;
			while (temp->next)
			{

				temp = temp->next;

			}

			temp->next = newnode;

		}

	}
	void display() {
		Node<T>* temp = head;

		while (temp)
		{
			std::cout << temp->data << '-';
			temp = temp->next;
		}


	}

	void reverse_list() {

		Node<T>* temp = head;

		Node<T>* ptrofnext = NULL;// = temp->next;
		Node<T>* currpttr = NULL;


		while (temp)
		{

			ptrofnext = temp->next;


			temp->next = currpttr;



			currpttr = temp;


			//	std::cout << "\n" << temp->data << "\n";


			temp = ptrofnext;

		}
		head = currpttr;


	}
	int getindex(T t, Node<T>* head, T yoyo = 0) {

		if (t == head->data) {
			return yoyo;
		}
		if (head->next)
			getindex(t, head->next, yoyo + 1);
		else
		{
			return -1;
		}
	}
	void function(int x, int y) {

		Node<T>* temp = head;

		int keeper = 1;
		while (temp)
		{
			Node* tot = temp->next;
			if (keeper >= x) {
				int inner = 0;
				while (inner < y) {
					if (tot != NULL)
						tot = tot->next;

					inner++;
				}

				keeper = 0;
				temp->next = tot;
			}
			keeper++;

			//	std::cout << temp->data;
			temp = tot;

		}

	}
	void explode_head() {

		Node<T>* temp = head;
		head = head->next;
		delete (temp);
	}


};
