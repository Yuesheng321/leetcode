#include "./utils/tree.cpp"

/**
 * 二叉树层次遍历
 * [3, 9, 20, null, null, 15, 7]
 * [[3], [9, 20], [15, 7]]]
 */
class Solution
{
public:

    /*
        每次遍历currentLevelNum个元素，currentLevelNum为第currentLevelNum层元素个数（即队列中元素个数）
    */
    vector<vector<int>> levelOrder2(TreeNode* root) {
        // 中序遍历结果
        vector<vector<int>> nums;
         // 存储节点
        queue<TreeNode *> queue_node;
        // 首先放入根节点
        queue_node.push(root);
        while (!queue_node.empty()) {
            vector<int> num;
            // 队列中元素个数，即本次需要遍历数
            int currentLevelNum = queue_node.size();
            for (int i = 0; i < currentLevelNum; i++)
            {
                auto node = queue_node.front();
                // 访问节点
                num.push_back(node->val);
                queue_node.pop();
                if (node->left)
                {
                    queue_node.push(node->left);
                }
                if (node->right)
                {
                    queue_node.push(node->right);
                }

            }
            nums.push_back(num);
        }
        return nums;
    }

    /*
        每次遍历一个元素，记录元素所在层
    */
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        // 中序遍历结果
        vector<vector<int>> nums;
        // 存储节点当前层，以及节点
        queue<pair<int, TreeNode *>> queue_node;
        // 首先放入根节点
        queue_node.push(make_pair(0, root));
        pair<int, TreeNode *> pair_node;
        /*
            1. 队列中存储 待访问节点，及其层次
            2. 每次遍历非空队列
            3. 访问队头元素，并将左右节点及其层次放入队列
        */
        while (!queue_node.empty())
        {
            
            pair_node = queue_node.front();
            queue_node.pop();
            // 元素第一层数量小于节点层次，新增一层
            if(nums.size() <= pair_node.first) {
                nums.push_back(vector<int>());
            }
            
            // 添加访问节点至本层
            nums[pair_node.first].push_back(pair_node.second->val);

            // 左右子树添加至队列
            if (pair_node.second->left != nullptr)
            {
                queue_node.push({pair_node.first + 1, pair_node.second->left});
            }

            if (pair_node.second->right != nullptr)
            {
                queue_node.push({pair_node.first + 1, pair_node.second->right});
            }
        }
        return nums;
    }
};


void printRow(vector<int> row) {
    for_each(row.begin(), row.end(), printVal);
    cout << endl;
}

int main()
{
    TreeNode* root = createTreeNodeFromLevelOrder({3, 9, 20, INT_MAX, INT_MAX, 15, 7});
    vector<vector<int>> nums = Solution().levelOrder(root);
    for_each(nums.begin(), nums.end(), printRow);
    cout << endl;

    nums = Solution().levelOrder2(root);
    for_each(nums.begin(), nums.end(), printRow);
}