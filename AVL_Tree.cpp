#include<iostream>
#include<queue>
using namespace std;
struct node
{
    int height;
    int item;
    node *left;
    node *right;
};
class AVL_Tree
{
private:
    node *root;
    int BalanceFactor(node*);
    int Height(node*);
    node* Insert(node*,int);
    node* RightRotation(node*);
    node* LeftRotation(node*);
    node* Rotation(node*);
    void Inorder(node*);
    void Postorder(node*);
    void Preorder(node*);
    node* Delete(node*,int);
    int max(int,int);
    node* DeepCopy(node*,node*);
    node *MinimumValueNode(node* root);
public:
    AVL_Tree();
    AVL_Tree(AVL_Tree&);
    AVL_Tree& operator=(AVL_Tree&);
    void Insert(int item);
    void Delete(int item);
    void Inorder();
    void Postorder();
    void Preorder();
    void LevelOrderTraversal();
    node* Search(int item);
    bool IsEmpty();
    ~AVL_Tree//destructor
};
AVL_Tree::AVL_Tree()
{
    root = NULL;
}


AVL_Tree::~AVL_Tree()
{
    while(root)
    {
        Delete(root->item);
    }
}

AVL_Tree::AVL_Tree(AVL_Tree &T)
{
    root=NULL;
    root = DeepCopy(root,T.root);
}

AVL_Tree& AVL_Tree::operator=(AVL_Tree &T)
{

    while(root!=NULL)
    {
        Delete(root->item);
    }
    root = DeepCopy(root,T.root);
    return *this;
}

node* AVL_Tree::MinimumValueNode(node* root)
{
    node *t = root;
    while(t->left)
    {
        t=t->left;
    }
    return t;
}

void AVL_Tree::Delete(int item)
{
    root = Delete(root,item);
}

node* AVL_Tree::Delete(node* r,int item)
{
    if(r==NULL)
    {
        return NULL;
    }
    if(r->item == item)
    {
        if(r->right && r->left)
        {
            r->item = MinimumValueNode(r->right)->item;
            r->right = Delete(r->right,r->item);
            return r;
        }
        else if(r->left)
        {
            node *t = r->left;
            delete r;
            return t;
        }
        else if(r->right)
        {
            node *t = r->right;
            delete r;
            return t;
        }
        else
        {
            delete r;
            return NULL;
        }
    }
    else if(r->item > item)
    {
        r->left = Delete(r->left,item);
    }
    else
    {
        r->right = Delete(r->right,item);
    }

        r->height = 1 + max(Height(r->left),Height(r->right));
        if(BalanceFactor(r)>1)
        {
        if(BalanceFactor(r->left)>-1)
        {
            return RightRotation(r);
        }
        else
        {
            r->left = LeftRotation(r->left);
            return RightRotation(r);
        }
        }
        else if(BalanceFactor(r)<-1)
        {
        if(BalanceFactor(r->right)<1)
        {
            return LeftRotation(r);
        }
        else
        {
            r->right = RightRotation(r->right);
            return LeftRotation(r);
        }

        }
    return r;
}
void AVL_Tree::LevelOrderTraversal()
{
    queue<node*> q;
    q.push(root);
    while(!q.empty())
    {
        cout<<q.front()->item<<" ";
        if(q.front()->left && q.front()->right)
        {
            q.push(q.front()->left);
            q.push(q.front()->right);
        }
        else if(q.front()->left)
        {
            q.push(q.front()->left);
        }
        else if(q.front()->right)
        {
            q.push(q.front()->right);
        }
        q.pop();
    }

}



node* AVL_Tree::Search(int item)
{
    node *temp = root;
    while(temp)
    {
        if(temp->item == item)
            return temp;
        if(temp->item > item)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return NULL;
}


node* AVL_Tree::DeepCopy(node* root1,node* root2)
{
    if(root2==NULL)
    {
        return NULL;
    }
    else
    {
        root1 = new node();
        root1->left = NULL;
        root1->right = NULL;
        root1->item = root2->item;
        root1->height = root2->height;
        root1->left = DeepCopy(root1->left,root2->left);
        root1->right = DeepCopy(root1->right,root2->right);
    }
    return root1;
}




void AVL_Tree::Preorder()
{
    Preorder(root);
}
void AVL_Tree::Preorder(node *root)
{
    if(root)
    {
        cout<<root->item<<" ";
        Preorder(root->left);
        Preorder(root->right);
    }
}

void AVL_Tree::Postorder()
{
    Postorder(root);
}
void AVL_Tree::Postorder(node *root)
{
    if(root)
    {
        Postorder(root->left);
        Postorder(root->right);
        cout<<root->item<<" ";
    }
}



void AVL_Tree::Inorder()
{
    Inorder(root);
}

void AVL_Tree::Inorder(node *root)
{
    if(root)
    {
        Inorder(root->left);
        cout<<root->item<<" ";
        Inorder(root->right);
    }
}

int AVL_Tree::BalanceFactor(node* root)
{
    return Height(root->left) - Height(root->right);
}

int AVL_Tree::Height(node *ptr)
{
    if(ptr==NULL)
        return 0;
    return ptr->height;
}

void AVL_Tree::Insert(int item)
{
    root = Insert(root,item);
}

int AVL_Tree::max(int a,int b)
{
    return (a>b)?a:b;
}

node* AVL_Tree::Insert(node* ptr,int item)
{
    if(ptr==NULL)
    {
        node* n = new node();
        n->height = 1;
        n->item = item;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    else
    {
        if(item>ptr->item)
        {
            ptr->right = Insert(ptr->right,item);
        }
        else
        {
            ptr->left = Insert(ptr->left,item);
        }


        ptr->height = 1 + max(Height(ptr->left),Height(ptr->right));
        if(BalanceFactor(ptr)>1)
        {
        if(BalanceFactor(ptr->left)>-1)
        {
            return RightRotation(ptr);
        }
        else
        {
            ptr->left = LeftRotation(ptr->left);
            return RightRotation(ptr);
        }
        }
        else if(BalanceFactor(ptr)<-1)
        {
        if(BalanceFactor(ptr->right)<1)
        {
            return LeftRotation(ptr);
        }
        else
        {
            ptr->right = RightRotation(ptr->right);
            return LeftRotation(ptr);
        }
    }
    }
    return ptr;
}

node* AVL_Tree::RightRotation(node *y)
{
    node *x = y->left;
    node *T2= x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(Height(y->left),Height(y->right));
    x->height = 1 + max(Height(x->left),Height(x->right));
    return x;
}
node* AVL_Tree::LeftRotation(node *x)
{
    node *y = x->right;
    node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(Height(x->left),Height(x->right));
    y->height = 1 + max(Height(y->left),Height(y->right));
    return y;
}


int main()
{
    AVL_Tree T1;
    T1.Insert(40);
    T1.Insert(30);
    T1.Insert(20);
    T1.Insert(10);
    T1.Insert(50);
    T1.Insert(55);
    T1.Insert(60);
    AVL_Tree T2 = T1;
    T1.Inorder();
    cout<<endl;
    T2.Delete(40);
    T2.Inorder();
    cout<<endl;
    T1.LevelOrderTraversal();
    return 0;
}
