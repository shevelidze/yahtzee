#include "Fibanachi.hpp"

unsigned int Fibanachi::getNext()
{
    unsigned int next = this->left + this->right;
    this->left = this->right;
    this->right = next;
    return next;
}
