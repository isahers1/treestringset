#include <utility>
// Include the testing-logger library from
// the CS70 system directory in Docker.
#include <cs70/testinglogger.hpp>
#include "treestringset.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;


TreeStringSet::TreeStringSet() : size_(0), root_(nullptr) {
    affirm(consistent());
}

TreeStringSet::~TreeStringSet() {
    // only delete if tree actually exists
    if (root_ != nullptr) {
        deleteHelper(root_);
    }
}

bool TreeStringSet::consistent() const {
    return (((root_ == nullptr) && (size_ == 0)) ||
            ((root_ != nullptr) && (size_ > 0)));
}

void TreeStringSet::deleteHelper(Node*& tree) {
    // if we are past a leaf
    if (tree != nullptr) {
        // recursively delete left child if it exists
        deleteHelper(tree->leftChild_);
        // recursively delete right child if it exists
        deleteHelper(tree->rightChild_);
        // only after right and left child have been deleted
        // can we remove current node from the heap
        delete tree;
    }
}

size_t TreeStringSet::size() const { return size_; }

void TreeStringSet::insertAtLeaf(Node*& tree, const string& str) {
    // if we are inserting into empty tree, tree become node containing string
    if (tree == nullptr) {
        tree = new Node{str};  // Assumes a constructor for Node
        ++size_;
    } else if (str < tree->value_) {  // insert in left tree if it's less
        insertAtLeaf(tree->leftChild_, str);
    } else {  // insert in right tree if string is greater than current value
        insertAtLeaf(tree->rightChild_, str);
    }
}

void TreeStringSet::insert(const string &str) {
    // only insert if it does not exist in tree already
    if (!exists(str)) {
        insertAtLeaf(root_, str);
    }
}

bool TreeStringSet::existsHelper(const Node* tree, const string& str) const {
    // if tree is empty no elements can exist
    if (tree == nullptr) {
        return false;
    } else if (str == tree->value_) {  // return true if we find the value
        return true;
    } else if (str < tree->value_) {  // check left child if str is less
        return existsHelper(tree->leftChild_, str);
    } else {  // check right child if str is greater than current value
        return existsHelper(tree->rightChild_, str);
    }
}

bool TreeStringSet::exists(const string& str) const {
    return existsHelper(root_, str);
}


bool TreeStringSet::operator==(const TreeStringSet& rhs) const {
    // check that sizes are equal
    if (size() != rhs.size()) {
        return false;
    }
    // if sizes are equal, iterate through one tree to check that all values
    // present are present in the other tree as well
    for (TreeStringSet::iterator iter = begin(); iter != end(); ++iter) {
        if (!(rhs.exists(*iter))) {
            return false;
        }
    }
    return true;
}

bool TreeStringSet::operator!=(const TreeStringSet& rhs) const {
    return !operator==(rhs);
}

ostream& operator<<(ostream& os, const TreeStringSet& t) {
    return t.print(os);
}

ostream& TreeStringSet::printerHelper(const Node* tree, ostream& os) const {
    // print nothing if tree is empty
    if (tree == nullptr) {
        os << "-";
    } else {  // print using CS70 conventions otherwise
        os << "(";
        printerHelper(tree->leftChild_, os);
        os << ", " << tree->value_ << ", ";
        printerHelper(tree->rightChild_, os);
        os << ")";
    }
    return os;
}

ostream& TreeStringSet::print(ostream& os) const {
    return printerHelper(root_, os);
}

TreeStringSet::iterator TreeStringSet::begin() const {
    return TreeStringSet::Iterator(root_);
}

TreeStringSet::iterator TreeStringSet::end() const {
    return TreeStringSet::Iterator(nullptr);
}

TreeStringSet::Iterator::Iterator(Node* current) : current_(current) {
    // Nothing else to do.
}

TreeStringSet::Iterator& TreeStringSet::Iterator::operator++() {
    if (current_->leftChild_ != nullptr) {  // add left child to node queue
        pending_.push(current_->leftChild_);
    }
    if (current_->rightChild_ != nullptr) {  // add right child to node queue
        pending_.push(current_->rightChild_);
    }
    if (!pending_.empty()) {  // visit next node
        current_ = pending_.front();
        pending_.pop();
    } else {  // if at end, set current to null pointer
        current_ = nullptr;
    }
    return *this;
}

TreeStringSet::Iterator::reference TreeStringSet::Iterator::operator*() const {
    return current_ -> value_;
}

TreeStringSet::Iterator::pointer TreeStringSet::Iterator::operator->() const {
  return &(**this);
}

bool TreeStringSet::Iterator::operator==(const Iterator& rhs) const {
    return (current_ == rhs.current_) & (pending_ == rhs.pending_);
}

bool TreeStringSet::Iterator::operator!=(const Iterator& rhs) const {
    // Idiomatic code: leverage == to implement !=
    return !(*this == rhs);
}

TreeStringSet::Node::Node(string str)
    : value_(str), leftChild_(nullptr), rightChild_(nullptr) {
        // nothing else to do
}

double TreeStringSet::depthHelper(const Node* cur, double& h) const {
    // if doesn't exist, it has no depth
    if (cur == nullptr) {
        return 0;
        // if neither child exists, we are at leaf so return height
    } else if (cur->leftChild_ == nullptr && cur->rightChild_ == nullptr) {
        return h;
    }
    // add one to height and recursively find total depth
    double newHeight = h + 1;
    return h + depthHelper(cur->leftChild_, newHeight)
                    + depthHelper(cur->rightChild_, newHeight);
}

double TreeStringSet::averageDepth() const {
    if (size_ == 0) {
        return 0;
    } else {
        double total = 0;
        return depthHelper(root_, total)/size_;
    }
}

int TreeStringSet::heightHelper(const Node* current) const {
    // if we are at null it has no height
    if (current == nullptr) {
        return -1;
    } else {  // else return 1 plus max of height of right tree, left tree
        return 1 + max(heightHelper(current->leftChild_),
                        heightHelper(current->rightChild_));
    }
}

int TreeStringSet::height() const {
    return heightHelper(root_);
}

ostream& TreeStringSet::showStatistics(ostream& os) const {
    os << size() << " nodes, height " << height() << ", average depth "
        << averageDepth() << endl;
    return os;
}
