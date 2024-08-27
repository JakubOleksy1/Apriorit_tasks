#include <iostream>
#include <string>
#include <unordered_map>

class TelephoneBook {
public: 
    void addContact(const std::string& name, const std::string &number) {
        contacts[name] = number;
    }

    std::string findContact(const std::string& name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            return it->second;
        }
        return "Contact not found";
    }

    void deleteContact(const std::string& name) {
        contacts.erase(name);
    }

private: 
    std::unordered_map<std::string, std::string> contacts;
};

int main() {
    TelephoneBook book;
    book.addContact("Julia", "123-456-7890");
    book.addContact("Bob", "987-654-3210");

    std::cout << "Julia's number: " << book.findContact("Julia") << std::endl;
    std::cout << "Bob's number: " << book.findContact("Bob") << std::endl;

    book.deleteContact("Julia");
    std::cout << "Julia's number after deletion: " << book.findContact("Julia") << std::endl;

    return 0;
}

// I decided to choose unordered_map because it has O(1) time complexity for insertion, deletion, and search operations.
// This is because unordered_map uses hashing to store elements.
// The key is hashed and the value is stored at the hashed location.
// This makes the operations very fast.
