# include <iostream>
# include <vector>
// # include <algorithm>
using namespace std;

// enum MembersType{
//     STUDENT, FACULTY, LIBRARIAN
// };

class Members{

    protected:

    int id;
    string name;

    public:

    virtual int getId() = 0;
    virtual string getName() = 0;
    virtual void displayDetails() = 0;
    virtual void notificationDetails(string operation, string name) = 0;

    Members(int id, string name){
        this->id = id;
        this->name = name;
    }

    bool operator==(const Members& other) const {
        return (typeid(*this) == typeid(other) && this->id == other.id);
    }
};

// Members

class Student : public Members{

public:
    Student(int id, string name) : Members(id, name){}

    void displayDetails(){
        cout << "\nID: " << id << endl;
        cout << "Name: " << name << endl;
    }

    void notificationDetails(string operation, string name){
        if(operation == "add"){
            cout << "\nNew Book named '" << name << "' added to Library";
        }
        if(operation == "remove"){
            cout << "\nBook name '" << name << "' removed from Library";
        } 
    }

    int getId(){
        return id;
    }

    string getName(){
        return name;
    }
};

// Faculty

class Faculty : public Members{

public:
    Faculty(int id, string name) : Members(id, name){}

    void displayDetails(){
        cout << "\nID: " << id << endl;
        cout << "Name: " << name << endl;
    }

    void notificationDetails(string operation, string name){
        if(operation == "add"){
            cout << "\nNew Book named '" << name << "' added to Library";
        }
        if(operation == "remove"){
            cout << "\nBook name '" << name << "' removed from Library";
        } 
    }

    int getId(){
        return id;
    }

    string getName(){
        return name;
    }
};

// Librarian

class Librarian : public Members{

public:
    Librarian(int id, string name) : Members(id, name){}

    void displayDetails(){
        cout << "\nID: " << id << endl;
        cout << "Name: " << name << endl;
    }

    void notificationDetails(string operation, string name){
        if(operation == "add"){
            cout << "\nNew Book named '" << name << "' added to Library";
        }
        if(operation == "remove"){
            cout << "\nBook name '" << name << "' removed from Library";
        } 
    }

    int getId(){
        return id;
    }

    string getName(){
        return name;
    }
};

// Factory

class MembersFactory{

    public:

    static Members* addMember(string member, int id, string name){

        if(member == "student"){
            return new Student(id, name);
        }
        else if(member == "faculty"){
            return new Faculty(id, name);
        }
        else if(member == "librarian"){
            return new Librarian(id, name);
        }
        else{
            return nullptr;
        }
    }
};

// Builder Pattern

class Book{

    public:

    string name;
    string author;
    string edition;
    string genre;

    void displayBook(){
        cout << "Book name: " << name << endl;
        cout << "Author name: " << author << endl;
        cout << "Edition: " << edition << endl;
        cout << "Genre: " << genre << endl;
    }

    bool operator==(const Book& other) const {
        return (this->name == other.name);
    }
};

class Builder{

    virtual Builder& setName(string name) = 0;
    virtual Builder& setAuthorName(string author) = 0;
    virtual Builder& setEdition(string edition) = 0;
    virtual Builder& setGenre(string author) = 0;
    virtual Book build() = 0;
};

class BookBuilder : public Builder{

    Book book;
    
    public:

    BookBuilder& setName(string name){
        book.name = name;
        return *this;
    }

    BookBuilder& setAuthorName(string author){
        book.author = author;
        return *this;
    }

    BookBuilder& setEdition(string edition){
        book.edition = edition;
        return *this;
    }

    BookBuilder& setGenre(string genre){
        book.genre = genre;
        return *this;
    }

    Book build(){
        return book;
    }
};

// Library

class Library{

    static Library* instance;

    vector<Members*> members;
    vector<Book> books;

    Library(){cout << "Welcome to Library Management System\n";}

public:

    static Library* getInstance(){
        if(instance == nullptr){
            instance = new Library();
        }
        return instance;
    }

    void registerMembers(Members* member){
        members.push_back(member);
    }

    void unregisterMembers(Members* member){

        for(auto itr = members.begin(); itr != members.end();){
            if(*itr == member){
                members.erase(itr);
            }
            else{
                 itr++;
            }
        }
    }

    void notifyMembers(string operation, Book& book){

        if(operation == "add"){
            for(auto& member : members){
                member->notificationDetails(operation, book.name);
            }
        }
        if(operation == "remove"){
            for(auto& member : members){
                member->notificationDetails(operation, book.name);
            }
        }
        
    }

    void addBook(Book& book){
        books.push_back(book);
        notifyMembers("add", book);
    }

    void removeBook(Book& book){
        for(auto itr = books.begin(); itr != books.end();){
            if(*itr == book){
                books.erase(itr);
                notifyMembers("remove", book);
            }
            else{
                ++itr;
            }
        }
    }

    void displayMembers(){
        for(auto members : members){
            members->displayDetails();
        }
    }
};

Library* Library::instance = nullptr;

int main(){

    Members* m1 = MembersFactory::addMember("student", 101, "Ajay");
    Members* m2 = MembersFactory::addMember("faculty", 102, "Vishal");
    Members* m3 = MembersFactory::addMember("librarian", 103, "Varun");

    Library* lib = Library::getInstance();

    lib->registerMembers(m1);
    lib->registerMembers(m2);
    lib->registerMembers(m3);

    BookBuilder builder;
    Book book1 = builder.setName("Harry Potter")
                        .setAuthorName("J.K Rowling")
                        .setEdition("5th")
                        .setGenre("Fantasy")
                        .build();
                        
    // book1.displayBook();

    lib->addBook(book1);
    lib->removeBook(book1);

    // lib->un_registerMembers(m2);
    lib->displayMembers();

    return 0;
}