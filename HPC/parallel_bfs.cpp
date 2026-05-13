#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

// Node Structure
class node
{
public:
    int data;
    node *left, *right;
};

// Insert Node Level Wise
node* insert(node *root, int data)
{
    if(root == NULL)
    {
        root = new node();
        root->data = data;
        root->left = root->right = NULL;

        return root;
    }

    queue<node*> q;
    q.push(root);

    while(!q.empty())
    {
        node *temp = q.front();
        q.pop();

        // Left Child
        if(temp->left == NULL)
        {
            temp->left = new node();
            temp->left->data = data;
            temp->left->left = temp->left->right = NULL;

            return root;
        }
        else
        {
            q.push(temp->left);
        }

        // Right Child
        if(temp->right == NULL)
        {
            temp->right = new node();
            temp->right->data = data;
            temp->right->left = temp->right->right = NULL;

            return root;
        }
        else
        {
            q.push(temp->right);
        }
    }

    return root;
}

// Parallel BFS
void bfs(node *root)
{
    queue<node*> q;

    q.push(root);

    while(!q.empty())
    {
        int qSize = q.size();

        #pragma omp parallel for
        for(int i = 0; i < qSize; i++)
        {
            node *curr;

            #pragma omp critical
            {
                curr = q.front();
                q.pop();

                cout << curr->data << " ";
            }

            #pragma omp critical
            {
                if(curr->left)
                    q.push(curr->left);

                if(curr->right)
                    q.push(curr->right);
            }
        }
    }
}

int main()
{
    node *root = NULL;

    int data;
    char ans;

    do
    {
        cout << "Enter data: ";
        cin >> data;

        root = insert(root, data);

        cout << "Insert more nodes? (y/n): ";
        cin >> ans;

    } while(ans == 'y' || ans == 'Y');

    cout << "\nBFS Traversal:\n";

    bfs(root);

    return 0;
}