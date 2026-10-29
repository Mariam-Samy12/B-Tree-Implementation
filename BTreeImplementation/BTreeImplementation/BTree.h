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

	// insert

	bool insert(Type value)
    {
        // Prevent duplicate keys
        int index = -1;

        if (search(value, index) != nullptr)
        {
            return false;
        }

        // Case 1: The tree is empty
        if (root == nullptr)
        {
            LeafNode<Type, ord>* newRoot =
                new LeafNode<Type, ord>{};

            newRoot->is_leaf = true;
            newRoot->num_keys = 1;
            newRoot->key[0] = value;

            root = newRoot;

            return true;
        }

        // Variables used to handle a possible split
        bool split = false;
        Type promoted{};
        Node<Type, ord>* rightNode = nullptr;

        // Insert recursively
        insertRecursive(root, value, split, promoted, rightNode);

        // Case 2: The old root was split
        if (split)
        {
            InternalNode<Type, ord>* newRoot =
                new InternalNode<Type, ord>{};

            newRoot->is_leaf = false;
            newRoot->num_keys = 1;

            newRoot->key[0] = promoted;

            newRoot->child[0] = root;
            newRoot->child[1] = rightNode;

            root = newRoot;
        }

        return true;
    }

    // ==================== Recursive Insert ====================
    void insertRecursive(
        Node<Type, ord>* current,
        Type value,
        bool& split,
        Type& promoted,
        Node<Type, ord>*& rightNode)
    {
        split = false;
        rightNode = nullptr;

        // Find the correct position for the value
        int i = 0;

        while (i < current->num_keys &&
               current->key[i] < value)
        {
            i++;
        }

        // ==================================================
        // Case 1: Current node is a LEAF
        // ==================================================
        if (current->is_leaf)
        {
            // Case 1A: Leaf has space
            if (current->num_keys < ord)
            {
                // Shift keys to the right
                for (int j = current->num_keys; j > i; j--)
                {
                    current->key[j] = current->key[j - 1];
                }

                // Insert the new value
                current->key[i] = value;
                current->num_keys++;

                return;
            }

            // Case 1B: Leaf is full, so split it

            // Temporary array can hold ord + 1 keys
            Type tempKeys[ord + 1];

            int j = 0;

            for (int k = 0; k < ord + 1; k++)
            {
                if (k == i)
                {
                    tempKeys[k] = value;
                }
                else
                {
                    tempKeys[k] = current->key[j];
                    j++;
                }
            }

            int totalKeys = ord + 1;
            int mid = totalKeys / 2;

            // Promote the middle key to the parent
            promoted = tempKeys[mid];

            // Create the new right leaf
            LeafNode<Type, ord>* newLeaf =
                new LeafNode<Type, ord>{};

            newLeaf->is_leaf = true;

            // Keep keys before the middle key in the old leaf
            current->num_keys = mid;

            for (int k = 0; k < mid; k++)
            {
                current->key[k] = tempKeys[k];
            }

            // Put keys after the middle key in the new leaf
            newLeaf->num_keys = totalKeys - mid - 1;

            for (int k = 0; k < newLeaf->num_keys; k++)
            {
                newLeaf->key[k] = tempKeys[mid + 1 + k];
            }

            // Report the split to the parent
            split = true;
            rightNode = newLeaf;

            return;
        }

        // ==================================================
        // Case 2: Current node is an INTERNAL NODE
        // ==================================================

        InternalNode<Type, ord>* internal =
            static_cast<InternalNode<Type, ord>*>(current);

        bool childSplit = false;
        Type childPromoted{};
        Node<Type, ord>* childRight = nullptr;

        // Insert into the appropriate child
        insertRecursive(
            internal->child[i],
            value,
            childSplit,
            childPromoted,
            childRight
        );

        // No split occurred in the child
        if (!childSplit)
        {
            return;
        }

        // ==================================================
        // Case 2A: Internal node has space
        // ==================================================
        if (internal->num_keys < ord)
        {
            // Shift keys to the right
            for (int j = internal->num_keys; j > i; j--)
            {
                internal->key[j] = internal->key[j - 1];
            }

            // Shift child pointers to the right
            for (int j = internal->num_keys + 1; j > i + 1; j--)
            {
                internal->child[j] = internal->child[j - 1];
            }

            // Insert the promoted key
            internal->key[i] = childPromoted;

            // Attach the new right child
            internal->child[i + 1] = childRight;

            internal->num_keys++;

            return;
        }

        // ==================================================
        // Case 2B: Internal node is full, so split it
        // ==================================================

        // Temporary arrays for keys and child pointers
        Type tempKeys[ord + 1];
        Node<Type, ord>* tempChildren[ord + 2];

        // Build the temporary key array
        for (int k = 0; k < ord + 1; k++)
        {
            if (k < i)
            {
                tempKeys[k] = internal->key[k];
            }
            else if (k == i)
            {
                tempKeys[k] = childPromoted;
            }
            else
            {
                tempKeys[k] = internal->key[k - 1];
            }
        }

        // Build the temporary child-pointer array
        for (int k = 0; k < ord + 2; k++)
        {
            if (k <= i)
            {
                tempChildren[k] = internal->child[k];
            }
            else if (k == i + 1)
            {
                tempChildren[k] = childRight;
            }
            else
            {
                tempChildren[k] = internal->child[k - 1];
            }
        }

        int totalKeys = ord + 1;
        int mid = totalKeys / 2;

        // Promote the middle key to the parent
        promoted = tempKeys[mid];

        // Create the new right internal node
        InternalNode<Type, ord>* newInternal =
            new InternalNode<Type, ord>{};

        newInternal->is_leaf = false;

        // Keep keys before the middle key in the old node
        internal->num_keys = mid;

        for (int k = 0; k < mid; k++)
        {
            internal->key[k] = tempKeys[k];
        }

        // Assign child pointers to the old node
        for (int k = 0; k <= mid; k++)
        {
            internal->child[k] = tempChildren[k];
        }

        // Put keys after the middle key in the new node
        newInternal->num_keys = totalKeys - mid - 1;

        for (int k = 0; k < newInternal->num_keys; k++)
        {
            newInternal->key[k] = tempKeys[mid + 1 + k];
        }

        // Assign child pointers to the new node
        for (int k = 0; k <= newInternal->num_keys; k++)
        {
            newInternal->child[k] = tempChildren[mid + 1 + k];
        }

        // Report the split to the parent
        split = true;
        rightNode = newInternal;
    }
	
};