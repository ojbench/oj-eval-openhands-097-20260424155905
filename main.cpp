
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return NULL;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    vector<TreeNode*> q;
    q.push_back(root);
    int i = 1;
    int head = 0;
    while (head < q.size() && i < nodes.size()) {
        TreeNode* curr = q[head++];
        if (i < nodes.size() && nodes[i] != "null") {
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push_back(curr->left);
        }
        i++;
        if (i < nodes.size() && nodes[i] != "null") {
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push_back(curr->right);
        }
        i++;
    }
    return root;
}

void reverseInorder(TreeNode* root, int& cnt, int& result) {
    if (!root || cnt <= 0) return;
    reverseInorder(root->right, cnt, result);
    if (--cnt == 0) {
        result = root->val;
        return;
    }
    reverseInorder(root->left, cnt, result);
}

int main() {
    string line;
    if (!getline(cin, line)) return 0;
    
    // Parse input: root = [12, 5, 18, 2, 9, 15, 20], cnt = 4
    size_t root_pos = line.find("root = [");
    size_t root_end = line.find("]", root_pos);
    string root_str = line.substr(root_pos + 8, root_end - (root_pos + 8));
    
    size_t cnt_pos = line.find("cnt = ");
    int cnt = stoi(line.substr(cnt_pos + 6));
    
    vector<string> nodes;
    stringstream ss(root_str);
    string item;
    while (getline(ss, item, ',')) {
        size_t first = item.find_first_not_of(" ");
        size_t last = item.find_last_not_of(" ");
        if (first != string::npos)
            nodes.push_back(item.substr(first, last - first + 1));
    }
    
    TreeNode* root = buildTree(nodes);
    int result = -1;
    reverseInorder(root, cnt, result);
    cout << result << endl;
    
    return 0;
}
