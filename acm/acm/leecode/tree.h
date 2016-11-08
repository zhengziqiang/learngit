/*==============================================================================
    > File Name: tree.h
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月28日 星期三 18时08分59秒
 ==========================================================================*/


#include <stdio.h>  
#include <vector>  
  
struct TreeNode{  
    int value;  
    std::vector<TreeNode*> vec_children;  
};  
  
TreeNode* CreateTreeNode(int value){  
    TreeNode* pNode = new TreeNode();  
    pNode->value = value;  
  
    return pNode;  
}  
  
void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild){  
    if(pParent != NULL){  
        pParent->vec_children.push_back(pChild);  
    }  
}  
  
void PrintTreeNode(TreeNode* pNode){  
    if(pNode != NULL){  
        printf("value of this node is: %d\n", pNode->value);  
  
        printf("its children is as the following");  
        std::vector<TreeNode*>::iterator i = pNode->vec_children.begin();  
        while(i < pNode->vec_children.end()){  
            if(*i != NULL)  
                printf("%d\t", (*i)->value);  
        }  
        printf("\n");  
    }else{  
        printf("this node is null.\n");  
    }  
    printf("\n");  
}  
  
void PrintTree(TreeNode* pRoot){  
    PrintTreeNode(pRoot);  
  
    if(pRoot != NULL){  
        std::vector<TreeNode*>::iterator i = pRoot->vec_children.begin();  
        while(i < pRoot->vec_children.end()){  
            PrintTreeNode(*i);  
            ++i;  
        }  
    }  
}  
  
void DestroyTree(TreeNode* pRoot){  
    if(pRoot != NULL){  
        std::vector<TreeNode*>::iterator i = pRoot->vec_children.begin();  
        while(i < pRoot->vec_children.end()){  
            DestroyTree(*i);  
            ++i;  
        }  
        delete pRoot;  
    }  
}  

