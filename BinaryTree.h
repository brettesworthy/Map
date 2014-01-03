//
//
#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <queue>
#include <sstream>
#include <ostream>

using namespace std;

template<typename T> struct TreeNode
{
   TreeNode(const T& value, TreeNode<T>* left = NULL, TreeNode<T>* right = NULL)
   {
      Value = value;
      Left = left;
      Right = right;
   }

   T Value;
   TreeNode<T>* Left;
   TreeNode<T>* Right;

   virtual ~TreeNode()
   {}

  
   virtual string tostring() const
   {
	   ostringstream os;
	   os << Value;
	   return os.str();
   }
};

template<typename T> ostream& operator << (ostream& out, const TreeNode<T>& node)
{
	return out << node.tostring();
}

template<typename T> class BinaryTree
{
public:
	BinaryTree() : root(NULL){}

	BinaryTree(const T& value, const BinaryTree<T>& leftchild = BinaryTree(),
		const BinaryTree<T>& rightchild = BinaryTree()) :
		root(new TreeNode<T>(value, leftchild.root, rightchild.root)){}

	virtual ~BinaryTree()
	{}

	BinaryTree<T> getLeftSub() const
	{
		return BinaryTree<T> (root->Left);
	}

	BinaryTree<T> getRightSub() const
	{
		return BinaryTree<T> (root->Right);
	}

	const T& getData() const
	{
		return root->Value;
	}

	bool IsNull() const
	{
		if( root == NULL )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsLeaf() const
	{
      if(root!=NULL)
	  {
		  return root->Left == NULL && root->Right == NULL;
	  }
	  else
		  return true;
	}

	virtual string tostring() const
	{
		ostringstream os;
		if (IsNull())
		{
			os << "NULL\n";
		}
		else
		{
			os << *root << '\n';
			os << getLeftSub().tostring();
			os << getRightSub().tostring();
		}
		return os.str();
	}

	static BinaryTree<T> Read (istream& in)
	{
		string next;
		getline(in, next);
		if(next == "NULL")
		{
			return BinaryTree<T>();
		}
		else
		{
			T Value;
			istringstream ins(next);
			ins >> Value;
			BinaryTree<T> left = Read(in);
			BinaryTree<T> right = Read(in);
			return BinaryTree<T>(Value, left, right);
		}
	}
protected:
	BinaryTree(TreeNode<T>* new_root) : root(new_root){}
	
	TreeNode<T>* root;
};

template<typename T> ostream& operator << (ostream& out,
	const BinaryTree<T>& thetree)
{
	return << thetree.tostring();
}
template<typename T> istream& operator >> (istream& in,
	BinaryTree<T>& thetree)
{
	thetree = BinaryTree<T> Read(in);
	return in;
}
