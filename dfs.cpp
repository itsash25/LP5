#include <iostream>
#include <stack>
#include <omp.h>
#include<chrono>
#include<vector>
#include<iomanip>

using namespace std::chrono;
using namespace std;


class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) {
        data=val;
        left=NULL;
        right=NULL;
    }
};

// Depth-First Search traversal function (parallel version)
void parallel_dfs(TreeNode* root) {
    auto start = high_resolution_clock::now();
    if (root == nullptr)
        return;

    stack<TreeNode*> s;
    s.push(root);

    while (!s.empty()) {
        #pragma omp parallel
        {
            // Each thread has its own private stack
            stack<TreeNode*> privateStack;

            #pragma omp single nowait
            {
                privateStack.push(s.top());
                s.pop();
            }

            while (!privateStack.empty()) {
                TreeNode* currNode = privateStack.top();
                privateStack.pop();

                cout << currNode->data << " "; // Process current node

                // Push right child first, then left child (to maintain DFS order)
                if (currNode->right != nullptr) {
                    privateStack.push(currNode->right);
                }
                if (currNode->left != nullptr) {
                    privateStack.push(currNode->left);
                }
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
    cout << "\nParallel DFS Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}

int main() {
    // Creating a binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    // Perform parallel DFS traversal
    parallel_dfs(root);

    // Clean up memory
    delete root->left->left;    
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
