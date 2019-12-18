#include "pch.h"
#include "TRIE.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "vector"
#include "gtest/gtest.h"
using namespace std;


TEST(testTRIE, Inputfileopen)
{
	ifstream is("..\\trie\\dictionary.txt", std::ifstream::in);

	if (!is.is_open()) {
		ASSERT_TRUE(false);
	}
	else {
		ASSERT_TRUE(true);
	}
	is.close();
}

TEST(testTRIE, OutputAscendingDescending)
{
	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	string data;

	string dict_words[] = { "piper", "picked", "peck", "pecked", "pickled", "peppers", "silent", "listen", "zooid", "zoetrope",
						"hapten", "theatrical", "ownership", "tension", "poetic", "preventable", "hopeless" };

	int num_words = sizeof(dict_words) / sizeof(string);
	sort(dict_words, dict_words + num_words);

	Vector<string> ListOfWords = test.OutputAscending();

	ASSERT_TRUE(ListOfWords.Size() == num_words);

	for (int i = 0; i < num_words; ++i) {
		ASSERT_TRUE(ListOfWords[i] == dict_words[i]);
	}

	reverse(dict_words, dict_words + num_words);

	ListOfWords = test.OutputDescending();
	ASSERT_TRUE(ListOfWords.Size() == num_words);

	for (int i = 0; i < num_words; ++i) {
		ASSERT_TRUE(ListOfWords[i] == dict_words[i]);
	}
}


TEST(testTRIE, FindWord)
{
	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	EXPECT_EQ(1, test.FindWord("peck"));
	EXPECT_EQ(1, test.FindWord("piper"));
	EXPECT_EQ(0, test.FindWord("apple"));
	EXPECT_EQ(0, test.FindWord("pip"));
}

TEST(testTRIE, FindSynonyms)
{
	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	Vector<string> ListOfSynonyms = test.FindSynonyms("peck");

	string expected[] = { "strike", "beak", "pick" };

	for (string& ex : expected) {
		EXPECT_TRUE(ListOfSynonyms.find(ex) != -1);
	}
}


TEST(testTRIE, FindMeaning)
{
	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	string data = test.FindMeaning("peck");
	EXPECT_EQ(0, data.compare("a stroke or bite by a bird with its beak."));
	data = test.FindMeaning("piper");
	EXPECT_EQ(0, data.compare("a person who plays a pipe, especially an itinerant musician."));

}


TEST(testTRIE, FindPrefix)
{
	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	Vector<string> ListOfWords = test.OutputPrefix("pick");

	string expected[] = { "picked", "pickled" };

	ASSERT_TRUE(ListOfWords.Size() == 2);
	for (string& ex : expected) {
		EXPECT_TRUE(ListOfWords.find(ex) != -1);
	}

}


TEST(testTRIE, FindSmallerGreaterEqual)
{
	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	{
		Vector<string> ListOfWords = test.OutputSmaller(6);

		string expected[] = { "piper", "peck",  "zooid" };

		ASSERT_TRUE(ListOfWords.Size() == 3);
		for (string& ex : expected) {
			EXPECT_TRUE(ListOfWords.find(ex) != -1);
		}
	}

	{
		Vector<string> ListOfWords = test.OutputSE(5);

		string expected[] = { "piper", "peck",  "zooid" };

		ASSERT_TRUE(ListOfWords.Size() == 3);
		for (string& ex : expected) {
			EXPECT_TRUE(ListOfWords.find(ex) != -1);
		}
	}

	{
		Vector<string> ListOfWords = test.OutputGreater(6);

		string expected[] = { "pickled", "peppers",  "zoetrope", "theatrical", "ownership", "tension", "preventable", "hopeless" };

		ASSERT_TRUE(ListOfWords.Size() == 8);

		for (string& ex : expected) {
			EXPECT_TRUE(ListOfWords.find(ex) != -1);
		}
	}

}

TEST(testTRIE, FindAnagrams)
{
	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	Vector<string> ListOfWords = test.OutputAnagrams("listen");

	ASSERT_TRUE(ListOfWords.Size() == 1);
	string data;
	data = ListOfWords[0];
	EXPECT_EQ(0, data.compare("silent"));
}


TEST(testTRIE, FindSuffix)
{

	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");
	Vector<string> ListOfWords = test.OutputSuffix("cked");

	string expected[] = { "pecked", "picked" };

	ASSERT_TRUE(ListOfWords.Size() == 2);

	for (string& ex : expected) {
		EXPECT_TRUE(ListOfWords.find(ex) != -1);
	}
}


TEST(testTRIE, CompleteString)
{

	string dict_words[] = { "piper", "picked", "peck", "pecked", "pickled", "peppers", "silent", "listen", "zooid", "zoetrope",
					"hapten", "theatrical", "ownership", "tension", "poetic", "preventable", "hopeless" };

	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	{
		Vector<string> ListOfWords = test.CompleteString("pip");
		string expected[] = { "piper" };

		ASSERT_TRUE(ListOfWords.Size() == 1);

		for (string& ex : expected) {
			EXPECT_TRUE(ListOfWords.find(ex) != -1);
		}
	}

	{
		Vector<string> ListOfWords = test.CompleteString("eck");
		string expected[] = { "pecked", "peck" };

		ASSERT_TRUE(ListOfWords.Size() == 2);

		for (string& ex : expected) {
			EXPECT_TRUE(ListOfWords.find(ex) != -1);
		}
	}

}

// SpellChecker
TEST(testTRIE, SpellChecker) {

	TRIE test;
	test.CreateDictionary("..\\trie\\dictionary.txt");

	{
		string expected[] = { "pecked", "picked", "pickled" };

		Vector<string> ListOfWords = test.SpellChecker("packed");
		ASSERT_TRUE(ListOfWords.Size() == 3);

		for (string& ex : expected) {
			EXPECT_TRUE(ListOfWords.find(ex) != -1);
		}
	}

	{
		string expected[] = { "silent" };

		Vector<string> ListOfWords = test.SpellChecker("silnt");
		ASSERT_TRUE(ListOfWords.Size() == 1);

		for (string& ex : expected) {
			EXPECT_TRUE(ListOfWords.find(ex) != -1);
		}
	}
}
// SpellChecker