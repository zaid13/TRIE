#include<iostream>
#include <fstream>
#include <algorithm>
#include "trie_node.h"
#include "LIST.H"
#include "vector.h"
using namespace std;


class TRIE {
	Node_Trie* root;
	Vector<string> WORDS;

	void sort_str(string& str) {

		for (int i = 0; i < str.length(); i++) {

			for (int j = i; j < str.length(); j++) {
				if (str[i] > str[j] && i != j) {
					std::swap(str[i], str[j]);

				}

			}
		}
	}

	bool replace(string str2, string str1) {
		int ctr = 0;

			if (str1[0] != str2[0])return false;
		for (int i = 0; i < str1.length(); i++)
		{

			for (int j = 0; j < str2.length(); j++)
			{
				if (str1[i]==str2[j]) {
					ctr++;
					break;
				
				}
			}
		}

		
		if (ctr == str1.length()-1)return true;

			return false;
	}


	bool add(string str2, string str1) {
		int noeq = 0;
		int ctr = 0;
		for (int i = 0; i < str1.length(); i++)
		{
			if (str1[i] == str2[ctr]) {
				ctr++;
				noeq++;
			}
			else {


				if (  str1[i] == str2[ctr+1]) {
					ctr++;
					noeq++;
					
				}
			}

		}
		//cout << noeq << "    ^^^^^^^^^^^^^^         " << str2<<"------\n";
		if (noeq == str1.length())return true;

		return false;
	}

	bool completeo(string str2, string str1) {
	
		for (int i = 0; i < str1.length(); i++)
		{

			for (int j = 0; j < str2.length(); j++)
			{
				if (str1[i] == str2[j]) {
					int t = j;
		
					for (int k = i; k < str1.length(); k++) {
						int ctr = 0;
						if (str1[k] == str2[t]) {
							t++;
							ctr++;
							if (ctr > str1.length()) {
								return true;
							}
							//else break;
						}
					}

				}
			}
		}
		return false;
	}
	

	bool is_end(string str2, string str1 ) {
		int len = str2.length() - 1;
		for (int i = str1.length()-1; i>=0; i--) {
		
			if (str1[i] == str2[len]) {
				len--;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	
	bool is_sub(string str2, string str1) {

		for (int i = 0; i < str1.length(); i++)
		{

			for (int j = 0; j < str2.length(); j++)
			{
				if (str1[i] == str2[j]) {
					int t = j;
					int ctr = 0;
					for (int k = i; k < str1.length(); k++) {

						if (str1[k] == str2[t]) {
							t++;
							ctr++;
							if (ctr == str1.length() ) {
								return true;
							}
							//else break;
						}
					}
				
				}
			}
		}
		return false;
	}
	
	void revstr(string& str) {
		int y = str.length() - 1;

		for (int i = 0; i < str.length()/2; i++) {

			std::swap(str[i], str[y]);
			y--;
			
		
		}
	}
	void Outputgreater(Node_Trie* curr, Vector<string>& results, string curr_string, int number) {

		if (curr->key != '\0')
			curr_string += curr->key;

		if (curr->Flag_indicates && curr_string.length() > number) {
			cout << "putting this " << curr_string << "\n";
			results.put(curr_string);
		}

		for (int i = 0; i < 26; ++i) {

			if (curr->Array_of_pointers[i]) {
				Outputgreater(curr->Array_of_pointers[i], results, curr_string, number);
			}
		}
	}

	void Outputeq(Node_Trie* curr, Vector<string>& results, string curr_string, int number) {

		if (curr->key != '\0')
			curr_string += curr->key;

		if (curr->Flag_indicates && curr_string.length() == number) {
			results.put(curr_string);
		}

		for (int i = 0; i < 26; ++i) {

			if (curr->Array_of_pointers[i]) {
				OutputSmaller(curr->Array_of_pointers[i], results, curr_string, number);
			}
		}
	}


	void OutputSmaller(Node_Trie* curr, Vector<string>& results,string curr_string,int number) {
	
		if (curr->key != '\0')
			curr_string += curr->key;

		if (curr->Flag_indicates&& curr_string.length()<number) {
			results.put(curr_string);
		}

		for (int i = 0; i < 26; ++i) {

			if (curr->Array_of_pointers[i]) {
				OutputSmaller(curr->Array_of_pointers[i], results, curr_string, number);
			}
		}
	}
	Vector<string> pre_finder(string curr_string) {

		Node_Trie* curr = root;//->Array_of_pointers[str[0] - 97];  //making curr equal to the node of first charecter

		for (int i = 0; i < curr_string.length(); i++) {
			int index = curr_string[i] - 'a';
			if (curr->Array_of_pointers[index] == NULL) {
				return false;
			}
			else {
				if (curr->Array_of_pointers[index]->key == curr_string[i])
				{
					cout << curr_string << " " << i << " " << " " << curr_string.length() - 1 << " " << curr->Array_of_pointers[index]->Flag_indicates << "\n";
					if (i == curr_string.length() - 1 && curr->Array_of_pointers[index]->Flag_indicates == true) {
					
				
						return true;
					}


					curr = curr->Array_of_pointers[index];

				}
				else
				{
					return false;
				}



			}

		}
	}



	void amalgum(Node_Trie* curr, Vector<string>& results, string curr_string, string genuuine, string conststr) {
		if (curr->key != '\0') {
			curr_string += curr->key;
			conststr += curr->key;
			sort_str(curr_string);
		}

		if (curr->Flag_indicates && !curr_string.compare(genuuine)) {
			results.put(conststr);
		}

		for (int i = 0; i < 26; ++i) {

			if (curr->Array_of_pointers[i]) {
				amalgum(curr->Array_of_pointers[i], results, curr_string, genuuine, conststr);
			}
		}
	}
	void completion(Node_Trie* curr, Vector<string>& results, string curr_string, string perminent) {

		if (curr->key != '\0')
			curr_string += curr->key;

		if (curr->Flag_indicates) {
			cout << perminent[perminent.length() - 1] << "- " << curr_string[curr_string.length() - 1] << endl;


			if (is_sub(curr_string, perminent)) {
			//	cout << "putting this-------------------- " << curr_string << "\n";
				results.put(curr_string);

			}

		}

		for (int i = 0; i < 26; ++i) {

			if (curr->Array_of_pointers[i]) {
				completion(curr->Array_of_pointers[i], results, curr_string, perminent);
			}
		}
	}

	void SpellChecker(Node_Trie* curr, Vector<string>& results, string curr_string, string perminent) {

		if (curr->key != '\0')
			curr_string += curr->key;

		if (curr->Flag_indicates) {
			cout << perminent[perminent.length() - 1] << "- " << curr_string[curr_string.length() - 1] << endl;


			if (replace(curr_string, perminent) || add(curr_string, perminent)) {
				cout << "putting this-------------------- " << curr_string << "\n";
				results.put(curr_string);

			}

		}

		for (int i = 0; i < 26; ++i) {

			if (curr->Array_of_pointers[i]) {
				SpellChecker(curr->Array_of_pointers[i], results, curr_string, perminent);
			}
		}
	}

	void _suffix(Node_Trie* curr, Vector<string>& results, string curr_string, string perminent) {

		if (curr->key != '\0')
			curr_string += curr->key;

		if (curr->Flag_indicates ) {
		///	cout << perminent[perminent.length() - 1] << "- " << curr_string[curr_string.length() - 1]<<endl;
			

			if (is_end(curr_string, perminent)  ){ 
			//	cout << "putting this-------------------- " << curr_string << "\n";
				results.put(curr_string);

			}
			
		}

		for (int i = 0; i < 26; ++i) {

			if (curr->Array_of_pointers[i]) {
				_suffix(curr->Array_of_pointers[i], results, curr_string, perminent);
			}
		}
	}


	void OutputAscending(Node_Trie* curr, Vector<string>& results, string curr_string) {
		if(curr->key !='\0')
		curr_string += curr->key;

		if (curr->Flag_indicates ) {
			results.put(curr_string);
		}

		for (int i = 0; i < 26; ++i) {
			
			if (curr->Array_of_pointers[i]) {
				OutputAscending(curr->Array_of_pointers[i], results, curr_string);
			}
		}
	}
	bool checker(string curr_string) {

		Node_Trie* curr = root;//->Array_of_pointers[str[0] - 97];  //making curr equal to the node of first charecter

		for (int i = 0; i < curr_string.length(); i++) {
			int index = curr_string[i] - 'a';
			if (curr->Array_of_pointers[index] == NULL) {
	//			cout << "returning false \n\n\n";
				return false;
			}
		
				if (curr->Array_of_pointers[index]->key == curr_string[i])
				{
		//	cout<<	curr_string  <<" "<<i<<" "  <<" " <<curr_string.length() - 1  <<" "<< curr->Array_of_pointers[index]->Flag_indicates << "\n";
					if (i == curr_string.length()-1 && curr->Array_of_pointers[index]->Flag_indicates==true) {
						return true;
					}


					curr = curr->Array_of_pointers[index];

				}



			
	
		}

		return false;
	}


	Node_Trie* checker_ptr_pre(string curr_string) {

		Node_Trie* curr = root;//->Array_of_pointers[str[0] - 97];  //making curr equal to the node of first charecter

		for (int i = 0; i < curr_string.length(); i++) {
			int index = curr_string[i] - 'a';
			if (curr->Array_of_pointers[index] == NULL) {
				return	NULL;
			}
			else {
				if (curr->Array_of_pointers[index]->key == curr_string[i])
				{
				//	cout << curr_string << " " << i << " " << " " << curr_string.length() - 1 << " " << curr->Array_of_pointers[index]->Flag_indicates << "\n";
					if (i == curr_string.length() - 1 ) {
						
						

						return curr->Array_of_pointers[index];
					}


					curr = curr->Array_of_pointers[index];

				}
				else
				{
					return NULL;
				}



			}

		}
	}
	Node_Trie* checker_ptr(string curr_string) {

		Node_Trie* curr = root;//->Array_of_pointers[str[0] - 97];  //making curr equal to the node of first charecter

		for (int i = 0; i < curr_string.length(); i++) {
			int index = curr_string[i] - 'a';
			if (curr->Array_of_pointers[index] == NULL) {
				return false;
			}
			else {
				if (curr->Array_of_pointers[index]->key == curr_string[i])
				{
				//	cout << curr_string << " " << i << " " << " " << curr_string.length() - 1 << " " << curr->Array_of_pointers[index]->Flag_indicates << "\n";
					if (i == curr_string.length() - 1 && curr->Array_of_pointers[index]->Flag_indicates == true) {
						return curr->Array_of_pointers[index];
					}


					curr = curr->Array_of_pointers[index];

				}
				else
				{
					return NULL;
				}



			}

		}
	}
	void OutputDescending(Node_Trie* curr, Vector<string>& results, string curr_string) {
		
		if (curr->key != '\0')
			curr_string += curr->key;

	

		for (int i = 25; i >=0 ; --i) {

			if (curr->Array_of_pointers[i]) {
				OutputDescending(curr->Array_of_pointers[i], results, curr_string);
			}
		}

			if (curr->Flag_indicates) {
			results.put(curr_string);
		}
	}



public:


	TRIE() {
	//	cout << "&&&&&&&&&&&&&&&&&&&&&&&\n";
		//cout<<is_end("waqar", "aqha");

	//	cout << "&&&&&&&&&&&&&&&&&&&&&&&\n";
		root = new Node_Trie;
	}



	void  place(string str, Vector<string> synonymsst,string meaningst ) {

		Node_Trie* curr = root;//->Array_of_pointers[str[0] - 97];  //making curr equal to the node of first charecter
		
		for (int i = 0; i < str.length(); i++) {
			
			int index = str[i] - 'a';
			if (curr->Array_of_pointers[index] == NULL) {
				curr->Array_of_pointers[index] = new Node_Trie;
				curr->Array_of_pointers[index]->key = str[i];

			}
	
			curr = curr->Array_of_pointers[index];
		}
		curr->synonyms = synonymsst;
		curr->Flag_indicates = true;
		curr->Meaning = meaningst;
	}
	
	void CreateDictionary(string address) {

		string y = "zaid";
	
	//	cout << "\n\n"<< spello("packed", "pecked") <<"\n\n\n";

		Vector<string> Master_container;
		
ifstream is("..\\trie\\dictionary.txt", std::ifstream::in);
		int i = 0;
		string  temp = "iuyglh";
		while (!is.eof())
		{
			getline(is,temp);
				Master_container.put(temp);
			//	cout << Master_container[i]<<endl ;
				i++;
		}

		int No_of_words = 0;
		int No_of_meanings = 0;
		int No_of_synonyms = 0;
		for (int index = 0; index < i; index++) {
			if (is_word(Master_container[index]))
		 No_of_words++;
		}
		Vector<string> MEANIGS;
		Vector<string> *SYNONYMS = new Vector<string>[No_of_words];

	
		
	//	Vector<string> synovect;
		int wordcpunt = 0;
				for (int index = 1; index < i; index++) {
					if (is_synonyms(Master_container[index])) {
						SYNONYMS[wordcpunt].put(Master_container[index]);
						No_of_synonyms++;
				}
					if (is_word(Master_container[index])) {
						wordcpunt++;

					}
			}
				Vector<string> mean;
		for (int index = 0; index < i; index++) {

			if (is_meaning(Master_container[index])) {
				string str1 = Master_container[index];
				for (int k = 0; k < str1.length()-1; k++) {

					str1[k] = str1[k + 2];


				}
				str1.resize(str1.length() - 2);
				mean.put(str1);
	
				No_of_meanings++;
				
			}
		}
		
		int ctr = 0;

		for (int index = 0; index < i; index++) {

			if (is_word(Master_container[index])) {
				string str1 = Master_container[index];

				for (int k = 0; k < str1.length(); k++) {

					str1[k] = str1[k + 1];


				}

				str1.resize(str1.length() - 1);

					place(str1, SYNONYMS[ctr], mean.return_ptr()[ctr]);

				WORDS.put(str1);
				ctr++;
			}




		}



	//	cout << "-------------------------\n";
		for (int in = 0; in < No_of_words; in++)
		//	cout << WORDS[in]<<endl;

		//cout << "-------------------------\n";
		for (int in = 0; in < No_of_words; in++)
		//	cout << MEANIGS[in] << endl;

		//cout << "-------------------------\n";
		for (int in = 0; in < No_of_synonyms; in++) {}
		//	cout << SYNONYMS[in] << endl;

		for (int j = 0; j < No_of_words;j++) {
	//		cout << WORDS.return_ptr()[j]<<" ";

			for (int k = 0; k < SYNONYMS[j].get_index();k++  ) {
		//		cout << SYNONYMS[j].return_ptr()[k]<<"   ";
			
			}
		//	cout <<mean.return_ptr()[j] << " ";

		//	cout <<"\n";
		
		}
		
	}
	bool is_word(string& str) {
		if (str[0] =='-'  && str[1] != '-') {		  //first is dash second is NOT dash 
			return true;
		}
		return false;

	}

	bool is_meaning(string str) {
		if (str[0] == '-'  &&  str[1] == '-') {		  //first is dash second is dash 
			return true;
		}
		return false;
	}
	bool is_synonyms(string str) {

		if (str[0] != '-') {						  //first is  NOT dash
			return true;
		}
		return false;
	}




	bool FindWord(string str) {
	
		bool o = checker(str);
	

return  o;
	
	}
	Vector<string> OutputGreater(int a) {

		Vector<string> ab;
		Outputgreater(root, ab, "", a);

		return ab;
	
	}


	Vector<string> OutputAscending() {
		Vector<string> b;
		string str;
		OutputAscending(root,b,str);

	//	string *dict_words = WORDS.return_ptr();
		//int num_words = WORDS.get_index();
	//	sort(dict_words, dict_words + num_words);





		return b;
	}

	bool remove_(string &str1) {
	

		for (int i = 0; i < str1.length(); i++) {
			cout << str1;
			str1[i] = str1[i+1];

		
		}
		return true;
	}
	Vector<string>  OutputDescending() {
		Vector<string> b;
		string str;

		OutputDescending(root, b, str);

		
		return b;

	}
	Vector<string> FindSynonyms(string str) {

		Vector<string> a =checker_ptr(str)->synonyms;
		return a;
	}

	string FindMeaning(string str ) {
		
		string a = checker_ptr(str)->Meaning;
		return a;

	}


	Vector<string> OutputPrefix(string str) {
	Node_Trie* temp =checker_ptr_pre(str);
	Vector<string> b;
	str[str.length()-1] = str[str.length()];
		str.resize(str.length()-1);
		OutputAscending(temp, b, str);
		return b;
	}
	Vector<string> OutputSmaller(int b ) {
	
		Vector<string> ab;
		OutputSmaller(root, ab, "", b);
		
		return ab;
	}
	Vector<string> OutputSE(int bb) {
		Vector<string> ab;
		Outputeq(root, ab, "", bb+1);

		return ab;


		Vector<string> a;
		return a;
	}
	Vector<string> 	OutputAnagrams(string str ) {
		sort_str(str);
		Vector<string> a;
		amalgum(root,a,"",str,"" );
		for (int i = 0;i < a.Size(); i++) {
			cout << a.return_ptr()[i] << "--------------------\n\n";
			a.delete_entry(i);
		}
		return a;
	}


	Vector<string> 	OutputSuffix(string str) {
		Vector<string> a;
		
		string c = "";
		_suffix(root,a,"",str);

		return a;
	}
	
	
	Vector<string> 		CompleteString(string str) {
		Vector<string> a;

		string c = "";
		completion(root, a, "", str);

		return a;
	}


	Vector<string>  SpellChecker(string str) {
		Vector<string> a;

		string c = "";
		SpellChecker(root, a, "", str);

		return a;
	}
};