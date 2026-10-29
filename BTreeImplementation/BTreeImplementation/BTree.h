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
	Node<Type, ord>* root = nullptr;

	//search
	Node<Type, ord>* search(Type& value,int&index) {

		Node<Type, ord>* current = root;
		index = -1;
		while (current!=nullptr) {
			int i = 0;
			while (i< current->num_keys &&  current->key[i] < value ) {
				i++;
			}
			if (i < current->num_keys && current->key[i] == value){

				index = i;
				return current;
			}

			if (current->is_leaf) {
				
				return nullptr;
			}
				

			current = static_cast<InternalNode<Type, ord>*>(current)->child[i];

		}
		return nullptr;
	
	}
	
};