#pragma once
#include "LIST.H"
#include <iostream>
#include "vector.h"

using namespace std;

class Node_Trie{
public:
char key;
string Meaning;
Node_Trie** Array_of_pointers;
bool Flag_indicates;
Vector<string> synonyms;

	Node_Trie() {
		Node_Trie::Array_of_pointers = new Node_Trie*[26];// = new Node_Trie[26];//new Node_Trie[26];
		for (int i = 0; i < 26; ++i)
			this->Array_of_pointers[i] = NULL;

		Node_Trie::key = '\0';
		Node_Trie::Flag_indicates = false;
	 }




};