//Integrantes: 
//Marcia Gutiérrez Castillo
//Frans Trujillo Flores
//Frank Calef Bustamante Mauricio 

#include <iostream>
#include <string>

// Definición del nodo para la lista enlazada
struct Node {
    int key;
    std::string value;
    Node* next = nullptr;
};

// Definición de la lista enlazada
class LinkedList {
public:
    Node* head = nullptr;

    void push_front(int key, const std::string& value) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->next = head;
        head = newNode;
    }

    void remove(int key) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) return;

        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
    }

    std::string search(int key) {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "Key not found";
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << "(" << current->key << ", " << current->value << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Definición de la tabla hash
class HashTable {
private:
    static const int TABLE_SIZE = 10;
    LinkedList table[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    void insertItem(int key, const std::string& value) {
        int index = hashFunction(key);
        table[index].push_front(key, value);
    }

    void removeItem(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    std::string searchItem(int key) {
        int index = hashFunction(key);
        return table[index].search(key);
    }

    void displayHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Index " << i << ": ";
            table[i].print();
        }
    }
};

int main() {
    HashTable hashTable;

    // Insertar algunos valores
    hashTable.insertItem(1, "Apple");
    hashTable.insertItem(2, "Banana");
    hashTable.insertItem(42, "Grapes");
    hashTable.insertItem(4, "Orange");
    hashTable.insertItem(12, "Mango");

    // Mostrar la tabla hash
    hashTable.displayHashTable();

    // Buscar valores
    std::cout << "Value for key 2: " << hashTable.searchItem(2) << std::endl;
    std::cout << "Value for key 12: " << hashTable.searchItem(12) << std::endl;

    // Eliminar un valor
    hashTable.removeItem(2);
    hashTable.displayHashTable();

    return 0;
}
