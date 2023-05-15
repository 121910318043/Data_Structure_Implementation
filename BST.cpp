#include<iostream>
#include<queue>
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
    node* RecurInsert(node*,int);
    node* Del(node*,int);
    void LevelOR(queue<node*>&);
    int HOBST(queue<node*>&);
    void LevelOTT(node*,int);
    int TreeH(node*);
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
    void LevelOrderTraversal();
    void LevelOrderTraversalTraditional();
    void Delete(int);
    int Height();
    int TreeHeight();
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
void BST::Insert(int item)
{
    root = RecurInsert(root,item);
}
node* BST::RecurInsert(node *root,int item)
{
    if(root)
    {
        if(root->item > item)
        {
            root->left = RecurInsert(root->left,item);
        }
        else
        {
            root->right = RecurInsert(root->right,item);
        }
    }
    else
    {
        node *n = new node();
        n->right=NULL;
        n->left=NULL;
        n->item = item;
        return n;
    }
    return root;
}
void BST::LevelOrderTraversalTraditional()
{
    cout<<"Level Order Traversal = ";
    for(int i=0;i<=Height();i++)
    {
        LevelOTT(root,i);
    }
}
void BST::LevelOTT(node *root,int level)
{
    if(root==NULL)
        return;
    if(level==1)
    {
        cout<<root->item<<" ";
    }
    if(level>0)
    {
        LevelOTT(root->left,level-1);
        LevelOTT(root->right,level-1);
    }
}
/*void BST::Insert(int item) // Without recursion
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
*/
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
void BST::LevelOR(queue<node*> &q)
{
    if(q.empty())
    {
        return;
    }
    else
    {
        cout<<q.front()->item<<" ";
        if(q.front()->left)
        {q.push(q.front()->left);}
        if(q.front()->right)
        {q.push(q.front()->right);}
        q.pop();
        LevelOR(q);
    }
}
void BST::LevelOrderTraversal()
{
    queue<node*> Q;
    Q.push(root);
    LevelOR(Q);
}

/*void BST::LevelOrderTraversal()
{
    queue<node*> Q;
    Q.push(root);
    while(!Q.empty())
    {
        cout<<Q.front()->item<<" ";
        if(Q.front()->left)
        {Q.push(Q.front()->left);}
        if(Q.front()->right)
        {Q.push(Q.front()->right);}
        Q.pop();
    }
}*/
/*void BST::Delete(int item)
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
}*/
int BST::TreeHeight()
{
    return TreeH(root);
}
int BST::TreeH(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int leftHeight = TreeH(root->left);
    int rightHeight = TreeH(root->right);
    if(leftHeight > rightHeight)
        return leftHeight+1;
    else
        return rightHeight+1;
}
int BST::Height()
{
    queue<node*> q;
    if(root==NULL)
        return 0;
    q.push(root);
    q.push(NULL);
    return HOBST(q);
}
int BST::HOBST(queue<node*> &q)//Height of Binary Search Tree
{
    if(q.front() == NULL && q.back() == NULL)
        return 1;
    else
    {
        if(q.front()==NULL)
            {
                q.push(NULL);
                q.pop();
                return HOBST(q)+1;
            }
        if(q.front()->left)
        {
            q.push(q.front()->left);
        }
        if(q.front()->right)
        {
            q.push(q.front()->right);
        }
        q.pop();
        return HOBST(q);
    }
}
void BST::Delete(int item)
{
    root = Del(root,item);
}
node* BST::Del(node* root,int item)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->item = item)
    {
        if(!root->left && !root->right)
        {
            delete root;
            return NULL;
        }
        else if(root->left && root->right) 
        {
            node *t = root->right;
            while(t->left)
            {
                t=t->left;
            }
            root->item = t->item;
            root->right = Del(root->right,t->item);
        }
        else if(root->left)
        {
            node* t = root;
            root = root->left;
            delete t;
        }
        else
        {
            node* t = root;
            root = root->right;
            delete t;
        }
    }
    else
    {
        if(root->item > item)
        {
            root->left = Del(root->left,item);
        }else 
        {
            root->right = Del(root->right,item);
        }
    }
    return root;
}
int main()
{
    BST B;
    B.Insert(5);
    B.Insert(4);
    B.Insert(3);
    B.Insert(2);
    B.Insert(1);
    B.InorderTraversal();
    cout<<endl;
    B.PostorderTraversal();
    cout<<endl;
    B.PreorderTraversal();
    //cout<<endl;
    //B.Delete(10);
    //B.InorderTraversal();
    cout<<endl;
    B.LevelOrderTraversalTraditional();
    cout<<endl;
    cout<<"Height Of the tree = "<<B.Height();
    
    return 0;
}
