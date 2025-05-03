#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * nuevoMapa = (TreeMap *)malloc(sizeof(TreeMap));
    if (nuevoMapa == NULL) return NULL;
    nuevoMapa->root = NULL;
    nuevoMapa->current = NULL;

    nuevoMapa->lower_than = lower_than;
    return nuevoMapa;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    TreeNode * nuevoNodo = createTreeNode(key, value);
    if (tree->root == NULL) {
        tree->root = nuevoNodo;
        tree->current = nuevoNodo;
        return;
    }
    TreeNode * current = tree->root;

    while(1) {
        if (is_equal(tree, current->pair->key, key)) {
            free(nuevoNodo->pair);
            free(nuevoNodo);
            current->pair->value = value;
            return;
        }
        if (tree->lower_than(key, current->pair->key)) {
            if (current->left == NULL) 
            {
                current->left = nuevoNodo;
                nuevoNodo->parent = current;
                tree->current = nuevoNodo;
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) 
            {
                current->right = nuevoNodo;
                nuevoNodo->parent = current;
                tree->current = nuevoNodo;
                return;
            }
            current = current->right;
        }
    }
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if (node == NULL) return;
    if (node->left ==NULL && node->right == NULL) 
    {
        if (node != tree->root) {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        } else {
            tree->root = NULL;
        }
            
            free(node->pair);
            free(node);
            return;
        }
    else if( node->left == NULL || node->right == NULL) 
    {
        TreeNode * child;
        if (node->left != NULL) {
            child = node->left;
        } else {
            child = node->right;
        }
        if (node != tree->root) {
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        } else {
            tree->root = child;
        }
        free(node->pair);
        free(node);
        return;
    }
    else {
        TreeNode * Succ = minimum(node->right);

        TreeNode * child = Succ->right;
        TreeNode * parent = Succ->parent;
        node->pair->key = Succ->pair->key;
        node->pair->value = Succ->pair->value;
        // Se puedo haber usado removeNode, pero nose si se podía hacer así
        if (child != NULL) {
            child->parent = parent;
        }
        if (parent->left == Succ) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(Succ->pair);
        free(Succ);
                
    }
}

    

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * current = tree->root;
    while (current != NULL)
    {
        if (is_equal(tree, current->pair->key, key)) {
            tree->current = current;
            return current->pair;
        }
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }

    }
    return NULL;

}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
