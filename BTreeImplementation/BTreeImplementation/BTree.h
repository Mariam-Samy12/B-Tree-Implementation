#pragma once

//base node
template <typename Type,int ord>
struct Node
{
	bool is_leaf;
	int num_keys;
	Type key[ord];
};

//Internal node
template <typename Type, int ord>
struct InternalNode : public Node <Type, ord>
{
	Node<Type, ord>* child[ord + 1];
};

//Leaf Node
template <typename Type, int ord>
struct LeafNode :public Node < Type, ord>
{

};

//struct Btree
template <typename Type, int ord>
struct Btree
{
	Node<Type, ord>* root;
};