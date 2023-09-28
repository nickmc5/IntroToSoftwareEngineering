#ifndef GATORAVL_AVLTREE_H
#define GATORAVL_AVLTREE_H
#include <string>
#include <sstream>
#include <vector>

struct Node {
    std::string name;
    std::string ufid;
    Node* left ;
    Node* right;
    int height;

    Node() : name(""), ufid(""), left(nullptr), right(nullptr), height(1) {}
    Node(std::string name, std::string ufid) : name(name), ufid(ufid), height(1), left(nullptr), right(nullptr) {}
};


class AVLTree {
private:
    Node* InsertHelper(Node* node, std::string name, std::string ufid, bool& success) {

        if (node == nullptr) {
            return new Node(name, ufid);
        }
        if (std::stoi(node->ufid) < std::stoi(ufid)) {
            node->right = InsertHelper(node->right, name, ufid, success);
            if (node->left != nullptr) {
                if (node->left->height < node->right->height) {
                    node->height = node->right->height + 1;
                }
            } else {
                node->height = node->right->height + 1;
            }
        } else if (std::stoi(node->ufid) > std::stoi(ufid)) {
            node->left = InsertHelper(node->left, name, ufid, success);

            if (node->right != nullptr) {
                if (node->right->height < node->left->height) {
                    node->height = node->left->height + 1;
                }
            } else {
                node->height = node->left->height + 1;
            }
        } else {
            std::cout << "unsuccessful" << "\n";
            success = false;
            return node;
        }

        // balance functions
        int balanceFactor = GetBalanceFactor(node);
        if (balanceFactor == 2) {
            if (GetBalanceFactor(node->left) == 1) {
                return RightRotate(node);
            }
            if (GetBalanceFactor(node->left) == -1) {
                // left right rotation
                node->left = LeftRotate(node->left);
                return RightRotate(node);
            }
        }
        if (balanceFactor == -2) {
            if (GetBalanceFactor(node->right) == -1) {
                return LeftRotate(node);
            }
            if (GetBalanceFactor(node->right) == 1) {
                // right left rotation
                node->right = RightRotate(node->right);
                return LeftRotate(node);
            }
        }
        return node;
    }
    void PrintInorderHelper(Node* node, std::vector<std::string>& vec) {
        if (this->root == nullptr) {
            std::cout << "unsuccessful" << "\n";
        } else {
            if (node->left != nullptr) {
                PrintInorderHelper(node->left, vec);
            }
            vec.push_back(node->name);
            if (node->right != nullptr) {
                PrintInorderHelper(node->right, vec);
            }
        }
    }
    void PrintPreorderHelper(Node* node, std::vector<std::string>& vec) {
        if (this->root == nullptr) {
            std::cout << "unsuccessful" << "\n";
        } else {
            vec.push_back(node->name);
            if (node->left != nullptr) {
                PrintPreorderHelper(node->left, vec);
            }
            if (node->right != nullptr) {
                PrintPreorderHelper(node->right, vec);
            }
        }
    }
    void PrintPostorderHelper(Node* node, std::vector<std::string>& vec) {
        if (this->root == nullptr) {
            std::cout << "unsuccessful" << "\n";
        } else {
            if (node->left != nullptr) {
                PrintPostorderHelper(node->left, vec);
            }
            if (node->right != nullptr) {
                PrintPostorderHelper(node->right, vec);
            }
            vec.push_back(node->name);
        }
    }
    Node* SearchIDHelper(Node* root, std::string ufid) {

        if (root->ufid == ufid) {
            return root;
        }
        Node* temp = root;
        while (temp != nullptr) {
            if (temp->right != nullptr) {
                if (temp->right->ufid == ufid) {
                    return temp;
                }
            }
            if (temp->left != nullptr) {
                if (temp->left->ufid == ufid) {
                    return temp;
                }
            }
            if (std::stoi(temp->ufid) < std::stoi(ufid)) {
                temp = temp->right;
            } else if (std::stoi(temp->ufid) > std::stoi(ufid)) {
                temp = temp->left;
            } else {
                std::cout << "unsuccessful" << "\n";
                temp = nullptr;

            }
        }
        return temp;
    }
    void SearchNameHelper(Node* node, std::string name, bool& found) {
        if (node->name == name) {
            std::cout << node->ufid << "\n";
            found = true;
        }
        if (node->left != nullptr) {
            SearchNameHelper(node->left, name, found);
        }
        if (node->right != nullptr) {
            SearchNameHelper(node->right, name, found);
        }
        if (node->ufid == root->ufid && found == false) {
            std::cout << "unsuccessful" << "\n";
        }
    }
    int GetBalanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            if (node->left != nullptr && node->right != nullptr) {
                return (node->left->height - node->right->height);
            } else if (node->left == nullptr && node->right != nullptr) {
                return (0 - node->right->height);
            } else if (node->right == nullptr && node->left != nullptr) {
                return (node->left->height);
            }
        }
    }
    Node* LeftRotate(Node* node) {
        // set temp pointers
        Node* temp1 = node->right;
        Node* temp2 = temp1->left;

        // rotate
        temp1->left = node;
        node->right = temp2;

        //fix heights
        if (node->left == nullptr && node->right == nullptr) {
            node->height = 1;
        } else if (node->right == nullptr) {
            node->height = node->left->height + 1;
        } else {
            node->height = node->right->height + 1;
        }
        temp1->height = node->height + 1;

        return temp1;
    }
    Node* RightRotate(Node* node) {
        // set temp pointers
        Node* temp1 = node->left;
        Node* temp2 = temp1->right;

        // rotate
        temp1->right = node;
        node->left = temp2;

        // fix heights
        if (node->right == nullptr && node->left == nullptr) {
            node->height = 1;
        } else if (node->left == nullptr) {
            node->height = node->right->height + 1;
        } else {
            node->height = node->left->height + 1;
        }
        temp1->height = node->height + 1;

        return temp1;
    }
    void RemoveIDHelper(Node* root, std::string ufid) {
        Node* temp = SearchIDHelper(root, ufid);
        if (temp != nullptr) {
            if (temp->ufid == ufid) {
                this->root = Remove(temp);
            } else if (temp->right->ufid == ufid) {
                temp->right = Remove(temp->right);
            } else if (temp->left->ufid == ufid) {
                temp->left = Remove(temp->left);
            }
        }
    }
    Node* RemoveInorderHelper(Node* node, int N, int& counter) {
        Node* temp = nullptr;
        if (node->left != nullptr) {
            temp = RemoveInorderHelper(node->left, N, counter);
            if (node->left == temp) {
                node->left = Remove(node->left); // added
                return temp;
            }
            counter++;
        }
        if (temp != nullptr) {
            return temp;
        }
        if (counter == N) {
            return node;
        }
        if (node->right != nullptr) {
            counter++;
            temp = RemoveInorderHelper(node->right, N, counter);
            if (node->right == temp) {
                node->right = Remove(node->right); // added
                return temp;
            }
        }
        if (temp != nullptr) {
            return temp;
        }
        if (N > counter && node == root) {
            return temp;
        }
        return temp;
    }
    Node* Remove(Node* node) {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            std::cout << "successful" << "\n";
            return nullptr;
        } else if (node->left == nullptr && node->right != nullptr) {
            node->name = node->right->name;
            node->ufid = node->right->ufid;
            delete node->right;
            node->right = nullptr;
            std::cout << "successful" << "\n";

            // fix heights
            if (node->right != nullptr) {
                node->height = node->right->height + 1;
            } else {
                node->height = 1;
            }
            return node;
        } else if (node->left != nullptr && node->right == nullptr) {
            node->name = node->left->name;
            node->ufid = node->left->ufid;
            delete node->left;
            node->left = nullptr;
            std::cout << "successful" << "\n";

            // fix heights
            if (node->left != nullptr) {
                node->height = node->left->height + 1;
            } else {
                node->height = 1;
            }
            return node;
        } else {
            Node* temp = node->right;
            Node* temp2 = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            if (temp2->left != nullptr) {
                while (temp2->left->left != nullptr) {
                    temp2 = temp2->left;
                }
            }
            node->name = temp->name;
            node->ufid = temp->ufid;
            if (temp->right != nullptr && temp != temp2) {
                temp2->left = temp->right;
            }else if (temp->right != nullptr && temp == temp2) {
                temp2->left = nullptr;
                if (temp2->right != nullptr) {
                    node->right = temp2->right;
                }
            }
            else {
                temp2->left = nullptr;
            }
            if (node->right->right == nullptr) {
                if (node->right->name == "") {
                    node->right = nullptr;
                }
            } else if (node->right == nullptr) {
                node->right = node->right->right;
            }
            delete temp;
            std::cout << "successful" << "\n";

            // fix heights
            if (node->left == nullptr && node->right == nullptr) {
                node->height = 1;
            } else if (node->left == nullptr) {
                node->height = node->right->height + 1;
            } else if (node->right == nullptr) {
                node->height = node->left->height + 1;
            } else {
                if (node->left->height > node->right->height) {
                    node->height = node->left->height + 1;
                } else {
                    node->height = node->right->height + 1;
                }
            }
            return node;
        }

    }
    Node* DestructorHelper(Node* node) {
        if (root != nullptr) {
            if (node->left != nullptr) {
                node->left = DestructorHelper(node->left);
            }
            if (node->right != nullptr) {
                node->right = DestructorHelper(node->right);
            }
            delete node;
            return nullptr;
        }
    }

public:
    Node* root;
    AVLTree() : root(nullptr) {}
    ~AVLTree() {
        DestructorHelper(root);
    }
    void insert(std::string name, std::string ufid) {
        bool success = true;
        this->root = InsertHelper(this->root, name, ufid, success);
        if (success == true) {
            std::cout << "successful" << "\n";
        }
    }
    void printInorder() {

        std::vector<std::string> vec;
        PrintInorderHelper(this->root, vec);
        if (vec.size() != 0) {
            for (int i = 0; i < vec.size() - 1; i++) {
                std::cout << vec[i] << ", ";
            }
            std::cout << vec[vec.size() - 1] << "\n";
        }
    }
    void printPreorder() {

        std::vector<std::string> vec;
        PrintPreorderHelper(this->root, vec);
        if (vec.size() != 0) {
            for (int i = 0; i < vec.size() - 1; i++) {
                std::cout << vec[i] << ", ";
            }
            std::cout << vec[vec.size() - 1] << "\n";
        }
    }
    void printPostorder()
    {

        std::vector<std::string> vec;
        PrintPostorderHelper( this->root, vec);
        if (vec.size() != 0) {
            for (int i = 0; i < vec.size() - 1; i++) {
                std::cout << vec[i] << ", ";
            }
            std::cout << vec[vec.size() - 1] << "\n";
        }
    }
    void searchID(std::string ufid) {
        if (root == nullptr) {
            std::cout << "unsuccessful" << "\n";
        } else {
            Node *temp = SearchIDHelper(this->root, ufid);
            if (temp != nullptr) {
                if (temp->ufid == ufid) {
                    std::cout << temp->name << "\n";
                }
                if (temp->right != nullptr) {
                    if (temp->right->ufid == ufid) {
                        std::cout << temp->right->name << "\n";
                    }
                }
                if (temp->left != nullptr) {
                    if (temp->left->ufid == ufid) {
                        std::cout << temp->left->name << "\n";
                    }
                }
            } else {
                std::cout << "unsuccessful" << "\n";
            }
        }
    }
    void searchName(std::string name) {
        if (root == nullptr) {
            std::cout << "unsuccessful" << "\n";
        } else {
            bool found = false;
            SearchNameHelper(this->root, name, found);
        }
    }
    void removeID(std::string ufid) { RemoveIDHelper(this->root, ufid); }
    void removeInorder(int N) {
        if (this->root == nullptr) {
            std::cout << "unsuccessful" << "\n";
        } else {
            int counter = 0;
            Node *temp = RemoveInorderHelper(root, N, counter);
            if (temp == nullptr) {
                std::cout << "unsuccessful" << "\n";
            } else if (temp == root) {
                root = Remove(temp);
            }
        }
    }
    void printLevelCount() {
        if (this->root == nullptr) {
            std::cout << "0" << "\n";
        } else {
            std::cout << this->root->height << "\n";
        }
    }
};

#endif //GATORAVL_AVLTREE_H
