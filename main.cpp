//Binary Search Tree

/*
 * Created By Devashish Katoriya on 03-01-2017
 */

#include<iostream>

using namespace std;

#define LIMIT 200

class node															//Node Class
{
public :
    int data;
    node *LChild,*RChild;
};

template<typename T>
class stack															//Stack Class
{
    T arr[LIMIT];
    int top;
public :
    stack()
    {
        top = 0;
    }
    void push(T s)
    {
        if(!isFull())
        {
            arr[top] = s;
            top++;
        }
        else
        {
            cout<<"\nStack Overflow!";
        }
    }
    T pop()
    {
        if(!isEmpty())
        {
            return arr[--top];
        }
        else
        {
            cout<<"\nStack Underflow!";
        }
        return nullptr;
    }
    bool isEmpty()
    {
        return top == 0;
    }
    bool isFull()
    {
        return top == LIMIT;
    }
};

class binary_search_tree													//Tree Class
{
    node *root;
    node *create();
    int count,lCount;
public :
    binary_search_tree()
    {
        root = NULL;
        count = 0;
    }
    node *retRoot()
    {
        return root;
    }
    int retSize()
    {
        return count;
    }
    int retLeaves()
    {
        lCount = 0;
        leaves(root);
        return lCount;
    }
    void clr()
    {
        root = NULL;
        count = 0;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    void construct();
    void inOrder(node *);
    void preOrder(node *);
    void postOrder(node *);
    void in_itr(node *);
    void pre_itr(node *);
    void post_itr(node *);
    bool search(int);
    void remove(int);
    int height(node *);
    void leaves(node *);
    void swap(node *);
    void DFS();
};

node *binary_search_tree::create()											//create()
{
    node *s;
    s = new node;
    if(s==NULL)
    {
        cout<<"\nMemory Not Allocated!";
        return NULL;
    }
    cout<<"\nEnter value of Node : ";
    cin>>s->data;
    s->LChild = NULL;
    s->RChild = NULL;
    count++;

    return s;
}

void binary_search_tree::construct()                                        //construct()
{
    node *temp,*p;
    temp = create();
    if(isEmpty())
    {
        root = temp;
        cout<<"\nRoot Inserted!";
    }
    else
    {
        p = root;
        while(p!=NULL)
        {
            if(temp->data<p->data)
            {
                if(p->LChild==NULL)
                {
                    p->LChild = temp;
                    cout<<"\nElement Inserted!";
                    break;
                }
                else
                {
                    p = p->LChild;
                }
            }
            else if (temp->data>p->data)
            {
                if(p->RChild==NULL)
                {
                    p->RChild = temp;
                    cout<<"\nElement Inserted!";
                    break;
                }
                else
                {
                    p = p->RChild;
                }
            }
            else
            {
                cout<<"\nEntry already Exist";
                count--;
                break;
            }
        }
    }
}

void binary_search_tree::remove(int d)
{
    //Locate the element
    bool found = false;
    if(isEmpty())
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    node *curr;
    node *parent=NULL;
    curr = root;
    while(curr != NULL)
    {
        if(curr->data == d)
        {
            found = true;
            break;
        }
        else
        {
            parent = curr;
            if(d>curr->data) curr = curr->RChild;
            else curr = curr->LChild;
        }
    }
    if(!found)
    {
        cout<<" Data not found! "<<endl;
        return;
    }
    
    
    // 3 cases :
    // 1. We're removing a leaf node
    // 2. We're removing a node with a single child
    // 3. we're removing a node with 2 children
    
    // Node with single child
    if((curr->LChild == NULL && curr->RChild != NULL)|| (curr->LChild != NULL && curr->RChild == NULL))
    {
        if(curr->LChild == NULL && curr->RChild != NULL)
        {
            if(parent->LChild == curr)
            {
                parent->LChild = curr->RChild;
                delete curr;
            }
            else
            {
                parent->RChild = curr->RChild;
                delete curr;
            }
        }
        else // left child present, no right child
        {
            if(parent->LChild == curr)
            {
                parent->LChild = curr->LChild;
                delete curr;
            }
            else
            {
                parent->RChild = curr->LChild;
                delete curr;
            }
        }
        return;
    }
    
    //We're looking at a leaf node
    if( curr->LChild == NULL && curr->RChild == NULL)
    {
        if(parent->LChild == curr) parent->LChild = NULL;
        else parent->RChild = NULL;
        delete curr;
        return;
    }
    
    
    //Node with 2 children
    // replace node with smallest value in right subtree
    if (curr->LChild != NULL && curr->RChild != NULL)
    {
        node *chkr;
        chkr = curr->RChild;
        if((chkr->LChild == NULL) && (chkr->RChild == NULL))
        {
            curr = chkr;
            delete chkr;
            curr->RChild = NULL;
        }
        else // right child has children
        {
            //if the node's right child has a left child
            // Move all the way down left to locate smallest element
            
            if((curr->RChild)->LChild != NULL)
            {
                node *lcurr;
                node *lcurrp;
                lcurrp = curr->RChild;
                lcurr = (curr->RChild)->LChild;
                while(lcurr->LChild != NULL)
                {
                    lcurrp = lcurr;
                    lcurr = lcurr->LChild;
                }
                curr->data = lcurr->data;
                delete lcurr;
                lcurrp->LChild = NULL;
            }
            else
            {
                node *tmp;
                tmp = curr->RChild;
                curr->data = tmp->data;
                curr->RChild = tmp->RChild;
                delete tmp;
            }
            
        }
        return;
    }
    
}

void binary_search_tree::in_itr(node *s1)								//In order Iterative
{
    node *temp;
    temp = s1;
    stack <node *>s;
    while(1)
    {
        while(temp!=NULL)
        {
            s.push(temp);
            temp = temp->LChild;
        }
        if(s.isEmpty())
            return;
        temp = s.pop();
        cout<<temp->data;
        temp = temp->RChild;
    }
}

void binary_search_tree::inOrder(node *s1)								//in order()
{
    if(s1!=NULL)
    {
        inOrder(s1->LChild);
        cout<<s1->data<<",";
        inOrder(s1->RChild);
    }

}

void binary_search_tree::preOrder(node *s1)							//pre order()
{
    if(s1!=NULL)
    {
        preOrder(s1->LChild);
        preOrder(s1->RChild);
        cout<<s1->data<<",";
    }

}

void binary_search_tree::pre_itr(node *R)								//Pre order Iterative
{
    node *temp;
    temp = R;
    stack <node *>s;
    while(1)
    {
        while(temp!=NULL)
        {
            cout<<temp->data<<",";
            s.push(temp);
            temp = temp->LChild;
        }
        if(s.isEmpty())
            return;
        temp = s.pop();
        temp = temp->RChild;
    }
}

void binary_search_tree::postOrder(node *s)							//post order()
{
    if(s!=NULL)
    {
        cout<<s->data<<",";
        postOrder(s->LChild);
        postOrder(s->RChild);
    }
}

void binary_search_tree::post_itr(node *r)								//Post order Iterative
{
    node *temp;
    temp = r;
    stack <node *>s;
    stack <char>s2;
    char flag;

    while(1)
    {
        while(temp!=NULL)
        {
            s.push(temp);
            s2.push('L');
            temp = temp->LChild;
        }
        if(s.isEmpty())
            return;
        temp = s.pop();
        flag = s2.pop();
        if(flag=='R')
        {
            cout<<temp->data<<",";
            temp = NULL;
        }
        else
        {
            s.push(temp);
            s2.push('R');
            temp = temp->RChild;
        }
    }
}

bool binary_search_tree::search(int key)                                        //search()
{
    node *p;
    if(isEmpty())
    {
        cout<<"\nEmpty tree!";
        return false;
    }
    else
    {
        p = root;
        while(p!=NULL)
        {
            if(key<p->data)
            {
                if(p->LChild==NULL)
                {
                    return false;
                }
                else
                {
                    p = p->LChild;
                }
            }
            else if (key>p->data)
            {
                if(p->RChild==NULL)
                {
                    return false;
                }
                else
                {
                    p = p->RChild;
                }
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

int binary_search_tree::height(node *r)
{
    if(r==NULL)
        return 0;
    if(r->LChild==NULL && r->RChild==NULL)
        return 0;
    int hl,hr;
    hl = height(r->LChild);
    hr = height(r->RChild);
    if(hl>hr)
        return hl+1;
    else
        return hr+1;
}

void binary_search_tree::leaves(node *r)
{
    if(root==NULL) {
        cout << "\nEmpty Tree!";
        return;
    }
    if(r!=NULL)
    {
        if (r->LChild == NULL && r->RChild == NULL)
            lCount++;
        else
        {
            leaves(r->LChild);
            leaves(r->RChild);
        }
    }
}

void binary_search_tree::swap(node *r)
{
    node *temp;
    if(r==NULL)
    {
        swap(r->LChild);
        swap(r->RChild);
        
        temp = r->LChild;
        r->LChild = r->RChild;
        r->RChild = temp;
    }
}

void binary_search_tree::DFS()
{
    node *temp;
    temp = root;
    stack <node *>s;
    while(1)
    {
        while(temp!=NULL)
        {
            cout<<temp->data<<",";
            s.push(temp);
            temp = temp->LChild;
        }
        if(s.isEmpty())
            return;
        temp = s.pop();
        temp = temp->RChild;
    }
}

int main()
{
    binary_search_tree obj;
    int ch,key;
    char choice;
    cout<<"\nProgram to perform Various operation on Binary Search Tree.";
    do
    {
        ch = key = 0;
        choice = 'n';
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n 1 for Construction and Insertion";
        cout<<"\n 2 for In order Traversal";
        cout<<"\n 3 for Pre order Traversal";
        cout<<"\n 4 for Post order Traversal";
        cout<<"\n 5 to  Display Root Node";
        cout<<"\n 6 to  Display No. of Nodes in Tree";
        cout<<"\n 7 for In order Interative";
        cout<<"\n 8 for Pre oder Interative";
        cout<<"\n 9 for Post order Interative";
        cout<<"\n 10 to Search an Element";
        cout<<"\n 11 to Remove an Element";
        cout<<"\n 14 to Find Height/Depth of Tree";
        cout<<"\n 15 to Find No. of Leaves";
        cout<<"\n 16 to Swap Nodes";
        cout<<"\n 17 to DFS Traversal";
        cout<<"\n 19 to Clear whole Tree";
        cout<<"\n 0 to  Quit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch)
        {
            case 1 : obj.construct();
                break;
            case 2 : cout<<"\nIn order Traversal is ";
                obj.inOrder(obj.retRoot());
                break;
            case 3 : cout<<"\nPre order Traversal is ";
                obj.postOrder(obj.retRoot());
                break;
            case 4 : cout<<"\nPost order Traversal is ";
                obj.preOrder(obj.retRoot());
                break;
            case 5 : if(!obj.isEmpty())
                    cout<<"\nRoot Node is "<<obj.retRoot()->data;
                else
                    cout<<"\nEmpty Tree!";
                break;
            case 6 : cout<<"\nNo. of Nodes in Tree are "<<obj.retSize();
                break;
            case 7 : cout<<"\nIn order Interative is ";
                obj.in_itr(obj.retRoot());
                break;
            case 8 : cout<<"\nPre order Interative is ";
                obj.pre_itr(obj.retRoot());
                break;
            case 9 : cout<<"\nPost order Interative is ";
                obj.post_itr(obj.retRoot());
                break;
            case 10 : cout<<"\nEnter the search term : ";
                cin>>key;
                if(obj.search(key))
                    cout<<"\nKey Found!";
                else
                    cout<<"\nKey NOT found.";
                break;
            case 11 : cout<<"\nEnter the term to delete : ";
                cin>>key;
                obj.remove(key);
                break;
            case 14 : cout<<"\nThe height of tree is "<<obj.height(obj.retRoot());
                break;
            case 15 : cout<<"\nTotal No. of Leaves are "<<obj.retLeaves();
                break;
            case 16 : obj.swap(obj.retRoot());
                cout<<"\nNodes Swapped Successfully!";
                break;
            case 17 : cout<<"\nDFS Traversal is ";
                obj.DFS();
                break;
            case 19: cout<<"\nAre you sure you want to clear tree (y/n) ? ";
                cin>>choice;
                if(choice=='y'||choice=='Y')
                {
                    obj.clr();
                    cout<<"\nTree Cleared Successfully!";
                }
                else
                    cout<<"\nCancelled!";
            case 0 : break;
            default : cout<<"\nInvalid Option!";
        }

        /*
        if(ch!=0)
        {
            cout<<"\n\n\n\n\n\n\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }
        */
    }while(ch!=0);

    cout<<"\nThank you for using this program :) \n\n";
    return 0;
}

/* OUTPUT
C:\Users\A\CLionProjects\BST\cmake-build-debug\BST.exe

Program to perform Various operation on Binary Search Tree.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter value of Node :100
 100

Root Inserted!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter value of Node :50
 50

Element Inserted!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter value of Node :200
 200

Element Inserted!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter value of Node :25
 25

Element Inserted!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter value of Node :75
 75

Element Inserted!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :2
 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order Traversal is 25,50,75,100,200,

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :10
 10
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter the search term :200
 200

Key Found!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 for Construction and Insertion
 2 for In order Traversal
 3 for Pre order Traversal
 4 for Post order Traversal
 5 to  Display Root Node
 6 to  Display No. of Nodes in Tree
 7 for In order Interative
 8 for Pre oder Interative
 9 for Post order Interative
 10 to Search an Element
 11 to Remove an Element
 19 to Clear whole Tree
 0 to  Quit
Enter your choice :0
 0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thank you for using this program :)

*/