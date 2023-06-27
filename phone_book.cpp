#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

class Contact {
public:
    string phoneNumber;
    vector<string> emails;
    bool starred;
    Contact() : starred(false) {}
    Contact(const string& phoneNumber) : phoneNumber(phoneNumber), starred(false) {}

    void addEmail(const string& email) {
        emails.push_back(email);
    }

    void toggleStarred() {
        starred = !starred;
    }
};

class ContactBook {
private:
    map<string, Contact> contacts;

public:
    void addContact(const string& name, const string& phoneNumber, const string& email) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            it->second.addEmail(email);
        }
        else {
            Contact newContact(phoneNumber);
            newContact.addEmail(email);
            contacts[name] = newContact;
        }
        cout << "Contact added successfully!\n";
    }

    void deleteContact(const string& name) {
        if (contacts.erase(name))
            cout << "Contact deleted successfully!\n";
        else
            cout << "Contact not found!\n";
    }

    void updateContact(const string& name, const string& newPhoneNumber, const string& newEmail) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            it->second.phoneNumber = newPhoneNumber;
            it->second.emails.clear();
            it->second.addEmail(newEmail);
            cout << "Contact updated successfully!\n";
        }
        else {
            cout << "Contact not found!\n";
        }
    }

    void displayContacts() {
        if (contacts.empty()) {
            cout << "Contact book is empty.\n";
        }
        else {
            cout << "Contact book:\n";
            vector<string> starredContacts;
            vector<string> regularContacts;

            for (const auto& contact : contacts) {
                if (contact.second.starred) {
                    starredContacts.push_back(contact.first);
                }
                else {
                    regularContacts.push_back(contact.first);
                }
            }

            sort(starredContacts.begin(), starredContacts.end());
            sort(regularContacts.begin(), regularContacts.end());

            for (const auto& contact : starredContacts) {
                cout << "* " << contact << ", Phone: " << contacts[contact].phoneNumber << endl;
                cout << "  Emails:\n";
                for (const auto& email : contacts[contact].emails) {
                    cout << "  - " << email << endl;
                }
            }

            for (const auto& contact : regularContacts) {
                cout << contact << ", Phone: " << contacts[contact].phoneNumber << endl;
                cout << "  Emails:\n";
                for (const auto& email : contacts[contact].emails) {
                    cout << "  - " << email << endl;
                }
            }
        }
    }

    void toggleStarred(const string& name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            it->second.toggleStarred();
            cout << "Contact " << name << " is now ";
            if (it->second.starred) {
                cout << "starred.\n";
            }
            else {
                cout << "unstarred.\n";
            }
        }
        else {
            cout << "Contact not found!\n";
        }
    }

    void searchByName(const string& name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            cout << "Contact found:\n";
            cout << "Name: " << it->first << ", Phone: " << it->second.phoneNumber << endl;
            cout << "Emails:\n";
            for (const auto& email : it->second.emails) {
                cout << "- " << email << endl;
            }
        }
        else {
            cout << "Contact not found!\n";
        }
    }

    void searchByNumber(const string& phoneNumber) {
        bool contactFound = false;
        for (const auto& contact : contacts) {
            if (contact.second.phoneNumber == phoneNumber) {
                if (!contactFound) {
                    cout << "Contact found:\n";
                    contactFound = true;
                }
                cout << "Name: " << contact.first << endl;
                cout << "Emails:\n";
                for (const auto& email : contact.second.emails) {
                    cout << "- " << email << endl;
                }
                cout << endl;
            }
        }
        if (!contactFound) {
            cout << "Contact not found!\n";
        }
    }

    void searchByEmail(const string& email) {
        bool contactFound = false;
        for (const auto& contact : contacts) {
            for (const auto& contactEmail : contact.second.emails) {
                if (contactEmail == email) {
                    if (!contactFound) {
                        cout << "Contact found:\n";
                        contactFound = true;
                    }
                    cout << "Name: " << contact.first << endl;
                    cout << "Phone: " << contact.second.phoneNumber << endl;
                    cout << endl;
                    break;
                }
            }
        }
        if (!contactFound) {
            cout << "Contact not found!\n";
        }
    }
};

bool isValidPhoneNumber(const string& phoneNumber) {
    // Regular expression to validate phone number
    regex phoneNumberRegex(R"(^ (? : \ + 92 | 0092 | 0) ? (-) ? (3[0 - 6]{ 1 } [0 - 9] { 1 })\ - ([0 - 9]{ 7 })$)");
    return regex_match(phoneNumber, phoneNumberRegex);
}

bool isValidEmail(const string& email) {
    // Regular expression to validate email address
    regex emailRegex(R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$)");
    return regex_match(email, emailRegex);
}

int main() {
    ContactBook contactBook;
    int choice;

    do {
        cout << "===== Contact Book Menu =====\n";
        cout << "1. Add Contact\n";
        cout << "2. Delete Contact\n";
        cout << "3. Update Contact\n";
        cout << "4. Display Contacts\n";
        cout << "5. Toggle Starred\n";
        cout << "6. Search Contact\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, phoneNumber, email;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter phone number: ";
            cin >> phoneNumber;
            if (!isValidPhoneNumber(phoneNumber)) {
                cout << "Invalid phone number!\n";
                break;
            }
            cout << "Enter email address: ";
            cin >> email;
            if (!isValidEmail(email)) {
                cout << "Invalid email address!\n";
                break;
            }
            contactBook.addContact(name, phoneNumber, email);
            break;
        }
        case 2: {
            string name;
            cout << "Enter name: ";
            cin >> name;
            contactBook.deleteContact(name);
            break;
        }
        case 3: {
            string name, newPhoneNumber, newEmail;
            cout << "Enter name to update: ";
            cin >> name;
            cout << "Enter new phone number: ";
            cin >> newPhoneNumber;
            if (!isValidPhoneNumber(newPhoneNumber)) {
                cout << "Invalid phone number!\n";
                break;
            }
            cout << "Enter new email address: ";
            cin >> newEmail;
            if (!isValidEmail(newEmail)) {
                cout << "Invalid email address!\n";
                break;
            }
            contactBook.updateContact(name, newPhoneNumber, newEmail);
            break;
        }
        case 4:
            contactBook.displayContacts();
            break;
        case 5: {
            string name;
            cout << "Enter name: ";
            cin >> name;
            contactBook.toggleStarred(name);
            break;
        }
        case 6: {
            int searchOption;
            cout << "Search by:\n";
            cout << "1. Name\n";
            cout << "2. Phone Number\n";
            cout << "3. Email\n";
            cout << "Enter your choice: ";
            cin >> searchOption;

            switch (searchOption) {
            case 1: {
                string name;
                cout << "Enter name to search: ";
                cin >> name;
                contactBook.searchByName(name);
                break;
            }
            case 2: {
                string phoneNumber;
                cout << "Enter phone number to search: ";
                cin >> phoneNumber;
                if (!isValidPhoneNumber(phoneNumber)) {
                    cout << "Invalid phone number!\n";
                    break;
                }
                contactBook.searchByNumber(phoneNumber);
                break;
            }
            case 3: {
                string email;
                cout << "Enter email to search: ";
                cin >> email;
                if (!isValidEmail(email)) {
                    cout << "Invalid email address!\n";
                    break;
                }
                contactBook.searchByEmail(email);
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
            break;
        }
        case 7:
            cout << "Exiting...";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        cout << endl;
    } while (choice != 7);

    return 0;
}
