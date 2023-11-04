#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class AuthenticationSystem {
private:
    unordered_map<string, string> users; // Username and password storage

public:
    void registerUser(const string& username, const string& password) {
        // In a real system, you should securely hash and store the password.
        users[username] = password;
        cout << "User " << username << " registered successfully." << endl;
    }

    bool authenticateUser(const string& username, const string& password) {
        if (users.find(username) != users.end() && users[username] == password) {
            cout << "User " << username << " authenticated successfully." << endl;
            return true;
        }
        cout << "Authentication failed. Invalid username or password." << endl;
        return false;
    }
};

int main() {
    AuthenticationSystem authSystem;

    // Register a user
    authSystem.registerUser("user1", "password123");

    // Attempt authentication
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (authSystem.authenticateUser(username, password)) {
        cout << "Welcome, " << username << "!" << endl;
    } else {
        cout << "Authentication failed. Access denied." << endl;
    }

    return 0;
}
