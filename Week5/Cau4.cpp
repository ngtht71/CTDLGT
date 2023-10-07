#include <iostream>
#include <map>

using namespace std;

class Student {
    int id;
    string name;
    string Class;

public:
    Student(int id, string name, string Class) {
        this->id = id;
        this->name = name;
        this->Class = Class;
    }

    void printStudent() {
        cout << name << " " << Class;
    }

    string getName() { return name; }
    string getClass() { return Class; }
};

class ManageStudent {
    map <int, Student*> stdList;

public:
    map<int, Student*> getMap() {
        return stdList;
    }

    void insert (int ID, string Name, string Class){
        Student* newStudent =  new Student (ID, Name, Class);
        stdList.insert({ID, newStudent});
    }

    void deleteStd (int ID) {
        stdList.erase(ID);
    }

    string Infor (int ID) {
        if (stdList.count(ID) > 0)
            return stdList[ID]->getName() + "," + stdList[ID]->getClass();

        return "NA,NA";
    }
};


int main (){
    ManageStudent* manage = new ManageStudent();

    string operation;
    while (true) {
        cin >> operation;
        if (operation == "Insert") {
            int id; cin >> id;
            string name; cin >> name;
            string Class; cin >> Class;

            manage->insert(id, name, Class);
        }

        else if (operation == "Delete") {
            int id; cin >> id;
            manage->deleteStd(id);
        }

        else if (operation == "Infor") {
            int id; cin >> id;
            string infor = manage->Infor(id);
            cout << infor << endl;
        }
        else break;
    }
    return 0;
}
