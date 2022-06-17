#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.in");
class node
{
public:
    char * token;
    node *left, *right;
    node()
    {
        this->left = NULL;
        this->right = NULL;
    }
    node(char * t)
    {
        token = new char[strlen(t) + 1];
        strcpy(token, t);
        this->left = NULL;
        this->right = NULL;
    }
    char * where_child()
    {
        if (left == nullptr)
            return "left";
        if (right == nullptr)
            return "right";
        return "full";
    }
};
class Tree
{
public:
    node * root;
    int isNum(char * ch)
    {
        for(int i=0; i<strlen(ch); i++)
        {
            if(ch[i] < '0' || ch[i] > '9')
                return 0;
        }
        return 1;
    }
    int isSign(char * ch)
    {
        if (strlen(ch) > 1)
            return 0;
        int result = isNum(ch);
        if(result == 0)
            return 1;
        else
            return 0;
    }

    deque<char *>expr;
    void make_expr(char * prop)
    {
        char * p =strtok(prop, " ");
        while(p)
        {
            expr.push_back(p);
            p = strtok(NULL, " ");
        }
        make_root();
    }

    void make_root()
    {

        root = new node(expr[0]);
        expr.pop_front();
        make_tree(root);
    }

    void make_tree(node * father)
    {
        if (expr.empty())
        {
            return;
        }

        while(father->where_child() != "full" && !expr.empty())
        {
            node * nod = new node(expr[0]);
            char * dir = father->where_child();
            if(dir== "left")
                father->left = nod;
            else
            {
                father->right = nod;
            }
            expr.pop_front();

            if(isSign(nod->token))
            {
                make_tree(nod);
            }
            else
            {
                make_tree(father);
            }
        }
    }

    void inOrder(node *ptr)
    {
        if (ptr != NULL)
        {
            inOrder(ptr->left);
            cout<<ptr->token;
            inOrder(ptr->right);
        }
    }
    void preOrder(node *ptr)
    {
        if (ptr != NULL)
        {
            cout<<ptr->token<<" ";
            inOrder(ptr->left);
            inOrder(ptr->right);
        }
    }
    void postOrder(node *ptr)
    {
        if (ptr != NULL)
        {

            inOrder(ptr->left);
            inOrder(ptr->right);
            cout<<ptr->token<<" ";
        }
    }
    int evaluate(node * n)
    {
        char * semn = n->token;
        if(isNum(n->token))
        {
            return atoi(n->token);
        }
        if(strcmp(semn, "-") == 0)
        {
            return evaluate(n->left) - evaluate(n->right);
        }
        if(strcmp(semn, "+") == 0)
        {
            return evaluate(n->left) + evaluate(n->right);
        }
        if(strcmp(semn, "/") == 0)
        {
            return evaluate(n->left) / evaluate(n->right);
        }
        if(strcmp(semn, "*") == 0)
        {
            return evaluate(n->left) * evaluate(n->right);
        }
    }
};
int evaluateStack(char * expr)
{
    stack<int> Stack;

    for (int i = strlen(expr) - 1; i >= 0; i--) {
        if (expr[i] == ' '||expr[i]==')'||expr[i]=='(')
            continue;
        if (isdigit(expr[i])) {
            int num = 0, j = i;
            while (i < strlen(expr) && isdigit(expr[i]))
                i--;
            i++;
            for (int k = i; k <= j; k++)
                num = num * 10 + int(expr[k] - '0');
            Stack.push(num);
        }
        else {
            int t1 = Stack.top();
            Stack.pop();
            int t2 = Stack.top();
            Stack.pop();
            if(expr[i]=='+')
                Stack.push(t1+t2);
            else if(expr[i]=='-')
                Stack.push(t1-t2);
            else if(expr[i]=='*')
                Stack.push(t1*t2);
            else if(expr[i]=='/')
                Stack.push(t1/t2);
            else if(expr[i]=='^')
                Stack.push(pow(t1,t2));
        }
    }

    return Stack.top();
}
void removePar(char *str)
{
    int k=0;
    char *pt=new char[strlen(str)+1];
    for(int i=0;i<strlen(str);i++)
        if(str[i]!='('&&str[i]!=')')
        {
            pt[k]=str[i];
            k++;
        }
    pt[k]='\0';
    strcpy(str,pt);
}


int main()
{
    char * exp = new char[1000];
    char * cp = new char[1000];

    Tree exptree;
    cout<<"Enter expression in Prefix form: ";
    fin.getline(exp, 1000);
    removePar(exp);
    cout<<endl;
    cout<<"Your expression without paranthesis is: ";
    cout<<exp;
    strcpy(cp, exp);
    exptree.make_expr(exp);
    cout<<endl;
    cout<<"In-order of the tree : ";
    exptree.inOrder(exptree.root);
    cout<<endl;
    cout<<"The value of the expression using the tree is : ";
    cout<<exptree.evaluate(exptree.root)<<"\n";
    cout<<"The value of the expression using the stack is : ";
    cout << evaluateStack(cp) << endl;
    return 0;
};
