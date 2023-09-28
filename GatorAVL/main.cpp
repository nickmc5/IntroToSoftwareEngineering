#include <iostream>
#include <sstream>
#include "AVLTree.h"
#include <regex>
// ideas were used from the project 1 breakdown slides and lecture slides (insertion, deletion, rotations, etc.)

int main() {

    // create string to hold the current line, command, regexes, and AVL tree
    std::string line;
    std::string command;
    std::regex  regCommand = std::regex ("^[A-Za-z]*$");
    std::regex regName = std::regex("^[A-Za-z\\s]*$");
    std::regex regNumber = std::regex("^[0-9]{8}$");
    std::regex regN = std::regex("^[0-9]*");
    bool containsRegex;
    AVLTree tree;

    // get rid of number saying how many times to loop (didn't see that until submitting, but it still reads through all the commands)
    getline(std::cin, line);
    // loop through all the lines until all commands have been read
    while (getline(std::cin, line)) {

        // create an input stream from the current line
        std::istringstream in(line);

        // read the command from the input stream
        in >> command;

        if (command == "insert") {

            std::string name;
            std::string studentID;
            std::string temp = ""; // to test if there are extra entries after ID

            // read in name
            getline(in, name, '"');
            getline(in, name, '"');

            // check if name is valid
            containsRegex = std::regex_search(name, regName);
            if (!containsRegex) {
                std::cout << "unsuccessful\n";
            } else {

                // read to get student ID and get rid of the extra space
                in >> studentID;
                in >> temp;

                //check if student ID is valid
                containsRegex = std::regex_search(studentID, regNumber);
                if (!containsRegex || temp != "") {
                    std::cout << "unsuccessful\n";
                } else {
                    // call insert function
                    tree.insert(name, studentID);
                }
            }

        }
        else if (command == "remove") {

            std::string studentID;

            // read in student ID
            getline(in, studentID);
            if (studentID == "") {
                std::cout << "unsuccessful" << "\n";
            } else {

                studentID = studentID.substr(1);

                // check if student ID is valid
                containsRegex = std::regex_search(studentID, regNumber);
                if (!containsRegex) {
                    std::cout << "unsuccessful\n";
                } else {
                    // call remove function
                    tree.removeID(studentID);
                }
            }

        }
        else if (command == "search") {

            std::string query;

            getline(in, query);
            if (query == "") {
                std::cout << "unsuccessful" << "\n";
            } else {
                query = query.substr(1); // delete extra space

                // check if it's the student ID and if its valid
                containsRegex = std::regex_search(query, regNumber);
                if (containsRegex) {
                    // call search ID function
                    tree.searchID(query);
                } else {

                    // now we know it should be the name, check if there are quotes
                    if (query.at(0) != '"' || query.at(query.size() - 1) != '"') {
                        std::cout << "unsuccessful\n";
                    } else {

                        // get rid of the quotes
                        query = query.substr(1, query.size() - 2);

                        // check if the name is valid
                        containsRegex = std::regex_search(query, regName);
                        if (containsRegex) {
                            // call search name function
                            tree.searchName(query);
                        } else {
                            std::cout << "unsuccessful\n";
                        }
                    }
                }
            }

        }
        else if (command == "printInorder") {

            std::string temp = "";
            in >> temp;
            if (temp != "") {
                std::cout << "unsuccessful" << "\n";
            } else {
                tree.printInorder();
            }
        }
        else if (command == "printPreorder") {

            std::string temp = "";
            in >> temp;
            if (temp != "") {
                std::cout << "unsuccessful" << "\n";
            } else {
                tree.printPreorder();
            }
        }
        else if (command == "printPostorder") {

            std::string temp = "";
            in >> temp;
            if (temp != "") {
                std::cout << "unsuccessful" << "\n";
            } else {
                tree.printPostorder();

            }
        }
        else if (command == "printLevelCount") {

            std::string temp = "";
            in >> temp;
            if (temp != "") {
                std::cout << "unsuccessful" << "\n";
            } else {
                tree.printLevelCount();
            }
        }
        else if (command == "removeInorder") {

            std::string n;

            // read in student ID
            getline(in, n);
            if (n != "") {
                n = n.substr(1);
                // check if n is valid
                containsRegex = std::regex_search(n, regN);
                if (!containsRegex || std::stoi(n) < 0) {
                    std::cout << "unsuccessful\n";
                } else {
                    // call removeInorder function
                    tree.removeInorder(std::stoi(n));
                }

            } else {
                std::cout << "unsuccessful\n";
            }



        }
        else {
            std::cout << "unsuccessful" << "\n";
        }
    }
    return 0;
}
