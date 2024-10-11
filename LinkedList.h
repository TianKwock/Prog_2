
//
//@author: Tian Kwock
//@version: 1.0
//

#pragma once
#include <iostream>
#include <vector>

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data)
        {
            this->data = data;
            next = nullptr;
            prev = nullptr;
        }
    };
    Node* head;
    Node* tail;
    int nodeCount;

    //CONSTRUCTION / DESTRUCTION

    //Default Constructor
    LinkedList()
    {
        nodeCount = 0;
        head = nullptr;
        tail = nullptr;
    }
    //Copy Constructor
    LinkedList(const LinkedList<T>& list)
    {
        head = nullptr;
        tail = nullptr;
        nodeCount = 0;
        //check if empty
        if (list.head == nullptr)
        {
            return;
        }
        Node* current = list.head;
        while (current != nullptr)
        {
            Node* newNode = new Node(current->data);
            //check if empty
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
            current = current->next;
            nodeCount++;
        }
    }
    //Destructor
    ~LinkedList()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    //BEHAVIORS

    //Iterator through all the nodes and print out their values, one at a time
    void PrintForward() const
    {
        Node* current = head;
        while (current != nullptr)
        {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
    //Opposite of PrintForward
    void PrintReverse() const
    {
        //traverse backwards
        Node* current = tail;
        while (current != nullptr)
        {
            std::cout << current->data << std::endl;
            current = current->prev;
        }
    }
    //Takes in a pointer to a starting node. From the node, recursively visit each node that follows, in forward order, printing their values.
    void PrintForwardRecursive(const Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }
        std::cout << node->data << std::endl;
        PrintForwardRecursive(node->next);
    }
    //Same as above but in reverse.
    void PrintReverseRecursive(const Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }
        std::cout << node->data << std::endl;
        PrintReverseRecursive(node->prev);
    }

    //ACCESSORS

    //Returns the head pointer; non-const version
    Node* Head()
    {
        return head;
    }
    //Returns the head pointer; const version
    const Node* Head() const
    {
        return head;
    }
    //Return the tail pointer ; non-const version
    Node* Tail()
    {
        return tail;
    }
    //Return the tail pointer ; const version
    const Node* Tail() const
    {
        return tail;
    }
    //How many nodes?
    unsigned int NodeCount() const
    {
        return nodeCount;
    }
    //Given an index, return a pointer to the node at that index. Throw out_of_range exception if index is out of range ; non-const version
    Node* GetNode(unsigned int index)
    {
        //throw out of range
        if (index >= nodeCount)
        {
            throw std::out_of_range("out of range");
        }
        //search for the node
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current;
    }
    //Given an index, return a pointer to the node at that index. Throw out_of_range exception if index is out of range ; const version
    const Node* GetNode(unsigned int index) const
    {
        //throw out of range
        if (index >= nodeCount)
        {
            throw std::out_of_range("out of range");
        }
        //search for the node
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current;
    }
    //Find the first node with a data value matching the passed in parameter, returning a pointer to that node. Returns nullptr if no matching node found ; non-const version
    Node* Find(const T& data)
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->data == data)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    //Find the first node with a data value matching the passed in parameter, returning a pointer to that node. Returns nullptr if no matching node found ; const version
    const Node* Find(const T& data) const
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->data == data)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    //Find all nodes that match the passed in value, and store a pointer to that node in the passed-in vector.
    void FindAll(std::vector<Node*>& outData, const T& value) const
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                outData.push_back(current);
            }
            current = current->next;
        }
    }

    //INSERTION OPERATIONS

    //Create a new node at the front of the list to store the passed in parameter
    //Possible edge case of this being called on an empty list
    void AddHead(const T& data)
    {
        //create a new node, point it to current head, make it new head
        Node* newNode = new Node(data);
        //if empty
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        nodeCount++;
    }
    //Create a new node at the end of the list to store the passed in parameter
    //Possible edge case of this being called on an empty list
    void AddTail(const T& data)
    {
        //create a new node, point the previous tail at it, point it at nullptr
        Node* newNode = new Node(data);
        //if empty
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        nodeCount++;
    }
    //Given an array of values, insert a node for each of those at the beginning of the list, maintaining the original order
    void AddNodesHead(const T* data, unsigned int count)
    {
        //to maintain order, go backwards in the array
        for (unsigned int i = count; i > 0; i--)
        {
            Node* newNode = new Node(data[i-1]);
            newNode->next = head;
            head = newNode;
            nodeCount++;
        }
    }
    //Same as AddNodesHead, but at the end of the list instead
    void AddNodesTail(const T* data, unsigned int count)
    {
        //going forward in the array maintains the proper order
        for (unsigned int i = 0; i < count; i++)
        {
            Node* newNode = new Node(data[i]);
            tail->next = newNode;
            tail = newNode;
            nodeCount++;
        }
    }
    //Given a pointer to a node, create a new node to store the passed in value, after the indicated node
    void InsertAfter(Node* node, const T& data)
    {
        Node* newNode = new Node(data);
        newNode->next = node->next;
        newNode->prev = node;
        node->next = newNode;
        //could be a problem line if next is nullptr?
        newNode->next->prev = newNode;
    }
    //Given a pointer to a node, create a new node to store the passed in value, before the indicated node
    void InsertBefore(Node* node, const T& data)
    {
        Node* newNode = new Node(data);
        newNode->next = node;
        newNode->prev = node->prev;
        node->prev = newNode;
        //again, could be a problem line
        newNode->prev->next = newNode;
    }
    //Inserts a new node to store the first parameter at the index-th location. Throw an out of range exception if given a bad index
    void InsertAt(const T& data, unsigned int index)
    {
        //out of range
        if (index > nodeCount)
        {
            throw std::out_of_range("out of range");
        }
        if (index == 0)
        {
            AddHead(data);
        }
        else
        {
            Node* current = head;
            for (unsigned int i = 0; i < index - 1; i++)
            {
                current = current->next;
            }
            Node* newNode = new Node(data);
            newNode->next = current->next;
            newNode->prev = current;
            current->next = newNode;
            if (newNode->next != nullptr)
            {
                newNode->next->prev = newNode;
            }
            nodeCount++;
        }
    }

    //REMOVALS

    //Deletes the first node in the list; returns whether the node was removed
    bool RemoveHead()
    {
        //list is empty
        if (head == nullptr)
        {
            return false;
        }
        Node* tbr = head;
        head = head->next;
        //if list still has elements post-removal
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        //if it doesn't
        else
        {
            tail = nullptr;
        }
        //delete and return true
        delete tbr;
        nodeCount--;
        return true;
    }
    //Deletes the last node, returning whether the operation was successful
    bool RemoveTail()
    {
        if (tail == nullptr)
        {
            return false;
        }
        Node* tbr = tail;
        tail = tail->prev;
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete tbr;
        nodeCount--;
        return true;
    }
    //Delete the index-th node from the list, returning whether the operation was successful
    bool RemoveAt(unsigned int index)
    {
        if (index > nodeCount)
        {
            return false;
        }
        //if list is empty
        if (head == nullptr)
        {
            return false;
        }
        if (index == 0)
        {
            return RemoveHead();
        }
        if (index == nodeCount - 1)
        {
            return RemoveTail();
        }
        Node* node = GetNode(index);
        Node* node1 = node->prev;
        Node* node2 = node->next;
        node1->next = node2;
        node2->prev = node1;
        delete node;
        nodeCount--;
        return true;
    }
    //Remove all nodes containing values matching the passed-in value. Returns how many instances were removed. 
    unsigned int Remove(const T& data)
    {
        Node* current = head;
        unsigned int counter = 0;
        while (current != nullptr)
        {
            if (current->data == data)
            {
                Node* tbr = current;
                //if it is head
                if (current == head)
                {
                    //if list still has elements
                    head = head->next;
                    if (head != nullptr)
                    {
                        head->prev = nullptr;
                    }
                }
                if (current == tail)
                {
                    tail = current->prev;
                    //if list still has elements
                    if (tail != nullptr)
                    {
                        tail->next = nullptr;
                    }
                }
                //remove it, add to counter, subtract from nodeCount
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current = current->next;
                delete tbr;
                counter++;
                nodeCount--;
            }
            else
            {
                current = current->next;
            }
        }
        return counter;
    }
    //Deletes all nodes, updates node count accordingly
    void Clear()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        nodeCount = 0;
    }

    //OPERATORS

    //Overloaded subscript operator that takes an index, and returns data from the nth node. Throws an out of range exception for an invalid index. non-const version
    T& operator[](unsigned int index)
    {
        if (index > nodeCount)
        {
            throw std::out_of_range("out of range");
        }
        Node* current = head;
        for (unsigned int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }
    //Overloaded subscript operator that takes an index, and returns data from the nth node. Throws an out of range exception for an invalid index. const version
    const T& operator[](unsigned int index) const
    {
        if (index > nodeCount)
        {
            throw std::out_of_range("out of range");
        }
        Node* current = head;
        for (unsigned int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }
    //Assignment operator
    LinkedList<T>& operator=(const LinkedList<T>& rhs)
    {
        //check if same
        if (this == &rhs)
        {
            return *this;
        }
        Node* current = head;
        //copied and pasted from destructor 
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        current = rhs.head;
        head = nullptr;
        tail = nullptr;
        nodeCount = 0;
        while (current != nullptr)
        {
            Node* newNode = new Node(current->data);
            //check if empty
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
            nodeCount++;
            current = current->next;
        }
        return *this;
    }
    //Overloaded equality operator
    bool operator==(const LinkedList<T>& rhs) const
    {
        //if same, must be equal
        if (this == &rhs)
        {
            return true;
        }
        //check node count
        if (this->nodeCount != rhs.nodeCount)
        {
            return false;
        }
        //check equal
        for (unsigned int i = 0; i < nodeCount; i++)
        {
            if (GetNode(i)->data != rhs.GetNode(i)->data)
            {
                return false;
            }
        }
        return true;
    }
};