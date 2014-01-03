// main.cpp - testing of the map implementation
// written by Brett Esworthy

#include <iostream>
#include <string>
#include <map>
#include "Huffman.h"
#include "BinaryTree.h"

using namespace std;

map<char, string> HuffmanMap;
HuffTree hufftree;

void buildcode()
{
	HuffmanMap.clear();
}

void HuffTree buildcode(const BinaryTree<SymbolPriority>& tree, const string& code)
{
	if(tree.IsLeaf())
	{
		SymbolPriority data = tree.getData();
		HuffmanMap[data.Symbol] = code;
	}
	else
	{
		string left(code);
		left.append(false);
		buildcode(tree.getLeftSub(), left);
		string right(code);
		right.append(true);
		buildcode(tree.getRightSub(), right);
	}
}

void HuffTree encode(istream& in, ostream& out)
{
	string result;
	char next;
	while (in.get(next))
	{
		result += HuffmanMap[next];
	}
	result.write(out);
}




void main()
{
	
	string test;
	PriorityQueue<SymbolPriority> objects;
	SymbolPriority character;
	BinaryTree<HuffTree> testree;

	cout << "Enter: ";
	getline(cin, test);

	for( int i = 0; i < test.length(); i++)
	{
		character.Symbol = test[i];
		character.Priority ++;
		if(character.Symbol == test[i - 1])
		{
			character.Priority ++;
		}
		objects.Push(character);
	}

	testree.MakeTree(objects);



	




	system("pause");
}
