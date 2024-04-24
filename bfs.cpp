#include<iostream>
#include<stdlib.h>
#include<queue>
#include<vector>
#include<chrono>
#include<iomanip>
#include<omp.h>

using namespace std::chrono;
using namespace std;

class Node{
public:
    Node *left,*right;
    int data;
    Node(int val)
    {
        data=val;
        left=NULL;
        right=NULL;
    }
};
void parallel_BFS(Node *root)
{
    auto start = high_resolution_clock::now();
    queue<Node *>q;
    q.push(root);
    int qSize;
    while(!q.empty())
    {
        qSize=q.size();
        #pragma omp parallel for
        for(int i=0;i<qSize;i++)
        {
            Node *currNode;
        #pragma omp critical
            {
                currNode=q.front();
                q.pop();
                cout<<"\t"<<currNode->data;
            }
        #pragma omp critical
            {
                if(currNode->left){
                    q.push(currNode->left);
                }            
                if(currNode->right){
                    q.push(currNode->right);
                }
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
    cout << "\nParallel BFS Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}
int main()
{
    Node *root=new Node(1);
    root->left=new Node(2);
    root->right=new Node(3);
    root->left->left=new Node(4);
    root->left->right=new Node(5);
    root->right->left=new Node(6);
    root->right->right=new Node(7);
    parallel_BFS(root);
}