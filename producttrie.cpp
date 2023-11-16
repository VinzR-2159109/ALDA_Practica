#include "producttrie.h"

ProductTrie::ProductTrie() : m_head{new Node}
{

}

void ProductTrie::insert(Product *product)
{
    insert(product->getAsin(), product);
}

void ProductTrie::insert(QString insertString, Product *product)
{
    Node *currentNode = m_head;

    for (QChar value : insertString) {
        if (currentNode->children.find(value) == currentNode->children.end()) {
            currentNode->children[value] = new Node;
        }

        currentNode = currentNode->children[value];
    }

    currentNode->products.push_back(product);
}
