#ifndef TREESTRINGSET_HPP_INCLUDED

#define TREESTRINGSET_HPP_INCLUDED


#include <cstddef>
#include <queue>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

class TreeStringSet {
 private:
        // Forward declaration of private class.
        class Iterator;

 public:
        TreeStringSet();
        ~TreeStringSet();
        TreeStringSet(const TreeStringSet& orig);
        TreeStringSet& operator=(const TreeStringSet& rhs);

        // member functions
        /**
        * \brief Calculate size of tree
        * \param None
        * \returns size of tree
        **/
        size_t size() const;

        /**
        * \brief Insert element into current tree
        * \param string to insert
        * \returns void
        **/
        void insert(const string &s);

        /**
        * \brief Check whether string exists in tree
        * \param string to check
        * \returns boolean whether element exists or not
        **/
        bool exists(const string &s) const;

        /**
        * \brief Calculate height of tree
        * \param None
        * \returns height of tree
        **/
        int height() const;

        /**
        * \brief Calculate average depth of tree
        * \param None
        * \returns Average depth of tree
        **/
        double averageDepth() const;

        /**
        * \brief Print tree using CS70 rules
        * \param os stream to print into
        * \returns ostream&
        **/
        ostream& print(ostream& os) const;

        /**
        * \brief Calculate and print out statistics for a tree
        * \param os stream to print to
        * \returns ostream with printed statistics
        **/
        ostream& showStatistics(ostream& os) const;

        // allow users to iterate through tree
        using iterator = Iterator;
        iterator begin() const;  // An iterator that refers to the first node
        iterator end() const;  // iterator that refers to 1 past the last node

        // operators
        bool operator==(const TreeStringSet& rhs) const;
        bool operator!=(const TreeStringSet& rhs) const;

        friend std::ostream& operator<<(std::ostream& os,
                                        const TreeStringSet& c);

 private:
        struct Node {
            string value_;      // string value at node
            Node* leftChild_;   // left tree of node
            Node* rightChild_;  // right tree of node

            Node(string s);
            Node() = delete;
            Node(const Node&) = delete;
            Node& operator=(const Node&) = delete;
            ~Node() = default;
        };

        size_t size_;  // number of elements in tree
        Node* root_;  // root node of tree

        /**
        * \brief Insert element at leaf of given tree
        * \param tree to push into, string to add
        * \returns void
        **/
        void insertAtLeaf(Node*& tree, const string &s);

        /**
        * \brief Check whether value exists in current tree
        * \param tree and string to check
        * \returns whether string is in tree
        **/
        bool existsHelper(const Node* tree, const string& str) const;

        /**
        * \brief Delete tree
        * \param tree to delete
        * \returns void
        **/
        void deleteHelper(Node*& tree);

        /**
        * \brief Print tree using CS70 rules
        * \param tree to print, os stream to print into
        * \returns ostream&
        **/
        ostream& printerHelper(const Node* tree, ostream& os) const;

        /**
        * \brief Calculate average depth of tree
        * \param Node position, current height
        * \returns Average depth of tree
        **/
        double depthHelper(const Node* cur, double& h) const;

        /**
        * \brief Calculate height of tree
        * \param current node
        * \returns height of tree
        **/
        int heightHelper(const Node* current) const;

        bool consistent() const;

        class Iterator {
         public:
                using value_type = std::string;
                using reference = value_type&;
                using pointer = value_type*;
                using iterator_category = std::forward_iterator_tag;

                Iterator() = default;
                Iterator(const Iterator&) = default;
                Iterator& operator=(const Iterator&) = default;
                ~Iterator() = default;

                Iterator& operator++();
                reference operator*() const;
                bool operator==(const Iterator& rhs) const;
                bool operator!=(const Iterator& rhs) const;
                pointer operator->() const;

         private:
                friend class TreeStringSet;
                explicit Iterator(Node* current);
                // Friends create non-default iterators
                Node* current_;  // The current list node
                std::queue<Node*> pending_;
        };
};

std::ostream& operator<<(std::ostream& os, const TreeStringSet& c);

#endif  // TREESTRINGSET_HPP_INCLUDED
