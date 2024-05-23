#include "utils/tree.cpp"

/*
    二叉树中序遍历: 左子树，根节点，右子树
    1. 堆非空 或者 当前遍历节点非空，继续遍历
    2. 当前访问节点非空时，将遍历访问入队，并继续遍历左节点
    3. 没有左子树时，访问节点
    2. 遍历右节点
*/
class Solution {

    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stack_node;
        vector<int> nums;
        // 1. 堆非空时，存在可访问节点
        // 2. root非空保证了初始，和访问根节点
        while(!stack_node.empty() || root) {
            // 将所有根节点入队，并遍历左节点 （判断root节点，避免了将null节点入队）
            while (root)
            {
                stack_node.push(root);
                root = root->left;
            }
            // 访问并弹出栈顶节点（此时栈顶的左节点为空，可以访问）
            root = stack_node.top(); stack_node.pop();
            nums.push_back(root->val);
            // 遍历右节点，非空时会继续将该节点入队，并访问其左节点，为空时，不会入队，会弹出root的父节点。
            root = root->right;
        }
        return nums;
    }
};

int main() {
    auto root = createTreeNodeFromLevelOrder({1, INT_MAX, 2, 3});
    auto nums = Solution().inorderTraversal(root);
    for_each(nums.begin(), nums.end(), printVal);
}