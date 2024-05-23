#include "./head.h"

/*
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 二叉树层次遍历
 */
vector<int> levelOrder(TreeNode *root)
{
    vector<int> nums;
    // 根节点为空直接返回
    if (root == nullptr)
    {
        return nums;
    }
    queue<TreeNode *> node_queue;
    node_queue.push(root);
    while (!node_queue.empty())
    {
        // 获取队头节点，并出队
        root = node_queue.front();
        node_queue.pop();

        // 访问队头节点
        nums.push_back(root->val);
        // 左右字数入队
        if (root->left != nullptr)
        {
            node_queue.push(root->left);
        }
        if (root->right != nullptr)
        {
            node_queue.push(root->right);
        }
    }
    return nums;
}

/**
 * 层序遍历创建二叉树
 * 1. 将根节点放入队列
 * 2. 遍历队列非空 且 未达到最大序列
 * 3. 遍历根节点，当根节点的左右子节非空，创建左右节点，并放入队列
 * 4. 返回第二步
 */
TreeNode *createTreeNodeFromLevelOrder(vector<int> nums)
{
    // 根节点元素不存在
    if (nums[0] == INT_MAX || nums.empty())
    {
        return nullptr;
    }
    int n = nums.size();

    // 创建根节点
    TreeNode *root;
    root = new TreeNode(nums[0]);
    // 节点的左右子数入队
    queue<TreeNode *> child_queue;
    child_queue.push(root);

    // 记录nums中当前遍历的位置
    int index = 1;

    // !child_queue.empty():保证了队列非空，避免了最后一层都为空时，重复计算
    // index < n ：保证了没有超过序列长度，避免了序列中多余的INT_MAX时，queue中不存在元素而出队失败。
    while (!child_queue.empty() && index < n)
    {

        TreeNode *node = child_queue.front();
        child_queue.pop();

        // 非空创建左节点
        if (nums[index] != INT_MAX)
        {
            node->left = new TreeNode(nums[index]);
            child_queue.push(node->left);
        }
        ++index;

        // index < n 避免了超出容量，非空创建右节点
        if (index < n && nums[index] != INT_MAX)
        {
            node->right = new TreeNode(nums[index]);
            child_queue.push(node->right);
        }
        ++index;
    }
    return root;
}

void inOrderDfs(vector<int> &nums, TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    nums.push_back(root->val);
    inOrderDfs(nums, root->left);
    inOrderDfs(nums, root->right);
}

void preOrderDfs(vector<int> &nums, TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    preOrderDfs(nums, root->left);
    nums.push_back(root->val);
    preOrderDfs(nums, root->right);
}

vector<int> preOrderDfs(TreeNode *root)
{
    vector<int> nums;
    preOrderDfs(nums, root);
    return nums;
}

vector<int> inOrderDfs(TreeNode *root)
{
    vector<int> nums;
    inOrderDfs(nums, root);
    return nums;
}

void printVal(int val)
{
    cout << val << " ";
}

/**
 * 先序遍历
 * 1. 栈非空 或者 根节点非空时，遍历
 * 2. 访问节点，并遍历左节点，直到左节点为空
 * 3. 访问栈顶元素右节点，并出栈
 */
vector<int> preorderDfs(TreeNode *root)
{
    vector<int> nums;
    stack<TreeNode *> stack_node;
    while (!stack_node.empty() || root)
    {
        while (root)
        {
            nums.push_back(root->val);
            stack_node.push(root);
            root = root->left;
        }
        root = stack_node.top();
        stack_node.pop();
        root = root->right;
    }
    return nums;
}

/**
     二叉树中序遍历: 左子树，根节点，右子树
    1. 堆非空 或者 当前遍历节点非空，继续遍历
    2. 当前访问节点非空时，将遍历访问入队，并继续遍历左节点
    3. 没有左子树时，访问节点
    2. 遍历右节点
*/
vector<int> inorderDfs(TreeNode *root)
{
    stack<TreeNode *> stack_node;
    vector<int> nums;
    // 1. 堆非空时，存在可访问节点
    // 2. root非空保证了初始，和访问根节点
    while (!stack_node.empty() || root)
    {
        // 将所有根节点入队，并遍历左节点 （判断root节点，避免了将null节点入队）
        while (root)
        {
            stack_node.push(root);
            root = root->left;
        }
        // 访问并弹出栈顶节点（此时栈顶的左节点为空，可以访问）
        root = stack_node.top();
        stack_node.pop();
        nums.push_back(root->val);
        // 遍历右节点，非空时会继续将该节点入队，并访问其左节点，为空时，不会入队，会弹出root的父节点。
        root = root->right;
    }
}

/*
后序遍历：根节点最后访问，即需要左右子树都访问完成
*/
vector<int> postorderDfs(TreeNode *root)
{
    stack<TreeNode *> stack_node;
    vector<int> nums;
    // 记录上一轮访问的节点
    TreeNode* prev = nullptr;
    // 入队根节点，并遍历左节点
    while (!stack_node.empty() || root)
    {
        while (root)
        {
            stack_node.push(root);
            root = root->left;
        }
        root = stack_node.top();
        stack_node.pop();
        // 左右子节点都遍历完成, 怎么判断右节点已访问完成(记录上一个已访问的节点:根节点一定是最后一个访问的，所以右节点已被访问，一定是上一个刚被访问的节点)
        if (!root->right || root->right == prev)
        {
            // 访问根节点
            nums.push_back(root->val);
            // 记录上一个已访问的节点
            prev = root;
            // root 应该指向那: 指向空，避免左节点在下一次入队，同时可以在下一轮访问堆顶元素
            root = nullptr;
        }
        // 否则继续遍历右子节点
        else
        {
            // 根节点需重新入队，最后访问
            stack_node.push(root);
            // 继续遍历右节点
            root = root->right;
        }
    }
    return nums;
}

int main()
{
    TreeNode *root = createTreeNodeFromLevelOrder({1, 2, 3});
    /*
    vector<int> nums = preOrderDfs(root);
    for_each(nums.begin(), nums.end(), printVal);
    cout << endl;
    nums = levelOrder(root);*/
    vector<int> nums = postorderDfs(root);
    for_each(nums.begin(), nums.end(), printVal);
    return 0;
}
