// huffman.h - class declaration and implementation of huffman map
// written by Brett Esworthy

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <ostream>
#include <functional>
#include "BinaryTree.h"
using namespace std;

template<typename T, typename Container = vector<T>, 
	typename Compare = less<T> > 
class PriorityQueue
{
public:
   PriorityQueue()
   {
   }
   const T& Top() const
   {
	   return QueueData.front();

   }
   bool IsEmpty() const
   {
	   return QueueData.empty();
   }
   void Pop()
   {
	   if (QueueData.size() == 1)
	   {
		   QueueData.pop_back();
		   return;
	   }
	   swap(QueueData[0], QueueData[QueueData.size() - 1]);
	   QueueData.pop_back();
	   int parent = 0;
	   while (true)
	   {
		   int left_child = 2 * parent + 1;
		   if (left_child >= QueueData.size())
			   break;
		   int right_child = left_child + 1;
		   int max_child = left_child;
		   if (right_child < QueueData.size() && comp(QueueData[left_child],
			   QueueData[right_child]) )
			   max_child = right_child;
		   if (comp(QueueData[parent], QueueData[max_child]))
		   {
			   swap(QueueData[max_child], QueueData[parent]);
			   parent = max_child;
		   }
		   else
			   break;
	   }

   }
   void Push(const T& value)
   {
	   QueueData.push_back(value);
	   int child = QueueData.size() - 1;
	   int parent = (child - 1) / 2;
	   while ( parent >= 0 && comp(QueueData[parent], QueueData[child]) )
	   {
		   swap(QueueData[child], QueueData[parent]);
		   child = parent;
		   parent = (child - 1) / 2;
	   }

   }
private:
   Container QueueData;
   Compare comp;
};

struct SymbolPriority
{
   SymbolPriority(char symbol, int priority)
   {
	   Symbol = symbol;
	   Priority = priority;
   }

   SymbolPriority()
   {
   }

   char Symbol;
   int Priority;
};

ostream& operator << (ostream&, const SymbolPriority&);

struct Comparetree
{
	bool operator()(const BinaryTree<SymbolPriority>& left_tree,
		const BinaryTree<SymbolPriority>& right_tree)
	{
		int wl = left_tree.getData().Priority;
		int wr = right_tree.getData().Priority;
		return wl > wr;
	}

};


class HuffTree
{
public:
	void MakeTree(const vector<SymbolPriority>& symbol)
	{
		PriorityQueue<BinaryTree<SymbolPriority>,
		vector<BinaryTree<SymbolPriority> >, Comparetree> thequeue;

		for(int i = 0; i < symbol.size(); i++)
		{
			thequeue.Push(BinaryTree<SymbolPriority>(symbol[i]));
		}

		while(!thequeue.IsEmpty())
		{
			BinaryTree<SymbolPriority> left = thequeue.Top();
			thequeue.Pop();
			BinaryTree<SymbolPriority> right = thequeue.Top();
			thequeue.Pop();
			int wl = left.getData().Priority;
			int wr = right.getData().Priority;
			SymbolPriority sum(wl + wr, 0);
			BinaryTree<SymbolPriority> newtree(sum, left, right);
			thequeue.Push(newtree);
		}
		hufftree = thequeue.Top();
		thequeue.Pop();
	}

	void Encode(ostream& out, string code, const BinaryTree<SymbolPriority>& tree) const
	{
		SymbolPriority data = tree.getData();
		if(data.Symbol != 0)
		{
			if(data.Symbol == ' ')
			{
				out << code << '\n';
			}
			else
			{
				out << data.Symbol << ": " << code << '\n';
			}
		}
		else
		{
			Encode(out, code + "0", tree.getLeftSub());
			Encode(out, code + "1", tree.getRightSub());
		}
	}

	string Decode(string& coded) const
	{
		string result;
		BinaryTree<SymbolPriority> current = hufftree;
		for(int i = 0; i < coded.length(); i++)
		{
			if(coded[i] == '1')
			{
				current = current.getRightSub();
			}
			else
			{
				current = current.getRightSub();
			}
			if(current.IsLeaf())
			{
				SymbolPriority data = current.getData();
				result += data.Symbol;
				current = hufftree;
			}
		}
	}

private:
	void Encode();
	BinaryTree<SymbolPriority> hufftree;
};
