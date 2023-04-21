#include<iostream>
using namespace std;
struct node
{
    node *left;
    int item;
    node *right;
};
class BST
{
private:
    node *root;
    void InorderTraversalRecursion(node*);
    void PreorderTraversalRecursion(node*);
    void PostorderTraversalRecursion(node*);
    void CopyTraversal(node*);
public:
    BST();
    BST(BST&);
    BST& operator=(BST&);
    node* GetRoot();
    bool IsEmpty();
    void Insert(int);
    void InorderTraversal();
    void PreorderTraversal();
    void PostorderTraversal();
    void Delete(int);
    ~BST();
};
BST::BST()
{
    root = NULL;
}
BST::BST(BST &B)
{
    root = NULL;
    CopyTraversal(B.root);
}
BST& BST::operator=(BST &B)
{
    if(root!=NULL)
    {
        while(root)
        {
            Delete(root->item);
        }
    }
    CopyTraversal(B.root);
    return *this;
}
void BST::CopyTraversal(node* root)//recursive inorder copy function
{
    if(root)
    {
        Insert(root->item);
        CopyTraversal(root->left);
        CopyTraversal(root->right);
    }
}
node* BST::GetRoot()
{
    return root;
}
BST::~BST()
{
    while(root)
    {
        Delete(root->item);
    }
}
bool BST::IsEmpty()
{
    if(root)
        return false;
    return true;
}
void BST::PreorderTraversal()
{
    cout<<"PreorderTraversal : ";
    if(root)
    {
        PreorderTraversalRecursion(root);
    }
    else
    {
        cout<<"Tree is Empty ";
    }
}
void BST::PreorderTraversalRecursion(node *root)
{
    if(root)
    {
        cout<<root->item<<" ";
        PreorderTraversalRecursion(root->left);
        PreorderTraversalRecursion(root->right);
    }
}
void BST::PostorderTraversal()
{
    cout<<"Post-Order Traversal : ";
    if(root)
    {
        PostorderTraversalRecursion(root);
    }
    else
    {
        cout<<"Tree Is Empty ";
    }
}
void BST::PostorderTraversalRecursion(node *root)
{
    if(root)
    {
        PostorderTraversalRecursion(root->left);
        PostorderTraversalRecursion(root->right);
        cout<<root->item<<" ";
    }
}
void BST::Insert(int item) // Without recursion
{
        node *n = new node;
        n->item = item;
        n->left = NULL;
        n->right = NULL;
    if(root==NULL)
    {
        root = n;
    }
    else
    {
        node *s=NULL,*t = root;
        while(t!=NULL)
        {
            s=t;
            if(t->item <= item)
                t=t->right;
            else
                t=t->left;
        }
        if(s->item <= item)
        {
            s->right = n;
        }
        else
        {
            s->left = n;
        }
    }
}

void BST::InorderTraversal()
{
    cout<<"Inorder Traversal : ";
    if(root)
    {
        InorderTraversalRecursion(root);
    }
    else
    {
        cout<<"Tree is Empty ";
    }
}
void BST::InorderTraversalRecursion(node *root)
{
    if(root)
    {
        InorderTraversalRecursion(root->left);
        cout<<root->item<<" ";
        InorderTraversalRecursion(root->right);
    }
}
void BST::Delete(int item)
{
    if(root)
    {
        if(item == root->item) //If Item is found in root node
        {
            node *t = root;
            if(root->right && root->left)
            {
                t = t->right;
                node *s = root;
                while(t->right || t->left)
                {
                    s=t;
                    if(t->left)
                    {
                        t=t->left;
                    }
                    else
                    {
                        t=t->right;
                    }
                }
                if(s->right == t)
                {
                    root->item = t->item;
                    delete s->right;
                    s->right = NULL;
                }
                else
                {
                    root->item = t->item;
                    delete s->left;
                    s->left = NULL;
                }
            }
            else if(!root->left && root->right)
            {
                root = root->right;
                delete t;
            }
            else if(!root->right && root->left)
            {
                root = root->left;
                delete t;
            }
            else
            {
                delete root;
                root = NULL;
            }
        }
        else
        {
            node *s = root;
            node *t = root;
            while(t->left || t->right)//searching node
            {
                s=t;
                if(item>t->item && t->right)
                {
                    t = t->right;
                }
                else if(t->left)
                {
                    t=t->left;
                }
                if(t->item == item)
                {
                    break;
                }
            }
            if(item == t->item)
            {
                if(t->right && t->left)//2 child
                {
                    node *f,*r=t;
                    while(r->right && r->left)
                    {
                        f=r;
                        if(r->left)
                        {
                            r=r->left;
                        }
                        else
                        {
                            r=r->right;
                        }
                    }
                    if(f->right == r)
                    {
                        t->item = f->item;
                        f->item = r->item;
                        delete f->right;
                        f->right = NULL;
                    }
                    else
                    {
                        t->item = r->item;
                        delete f->left;
                        f->left = NULL;
                    }
                }
                else if(t->right)
                {
                    if(s->right == t)
                    {
                        s->right = t->right;
                        delete t;
                    }
                    else
                    {
                        s->left = t->right;
                        delete t;
                    }
                }
                else
                {
                    if(s->right == t)
                    {
                        s->right = t->left;
                        delete t;
                    }
                    else
                    {
                        s->left = t->left;
                        delete t;
                    }
                }
            }
            else
            {
                cout<<"Node With "<<item<<" Not Found";
            }
        }
    }
    else
    {
        cout<<"Tree Is Empty ";
    }
}
int main()
{
    BST B;
    B.Insert(20);
    B.Insert(12);
    B.Insert(26);
    B.Insert(6);
    B.Insert(14);
    //B.Insert(7);
    B.Insert(22);
    B.Insert(30);
    //B.Delete(6);
    //B.Delete(14);
    B.InorderTraversal();
    cout<<endl;
    B.PostorderTraversal();
    cout<<endl;
    B.PreorderTraversal();
    B.Delete(14);
    cout<<endl;
    B.PreorderTraversal();
    cout<<endl;
    BST B2 = B;
    B2.PreorderTraversal();
    return 0;
}
