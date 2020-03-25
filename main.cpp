#include "List.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Dir
{
    string name;
    List<Dir> * dirs;
};

void split(List<string> * splited, string str, char separator){
    cout << "begin split" << endl;
    string temp = str;
    string sub;
    while (temp.find_first_of(separator) >=0 && temp.find_first_of(separator) < temp.length())
    {
        sub = temp.substr(0, temp.find_first_of(separator));
        if (sub.length() > 0) splited->add(sub);
        temp = temp.substr(temp.find_first_of(separator) + 1);

    }
    if (temp.length() > 0) splited->add(temp);
    cout << "end split" << endl;
}

void show(List<Dir> * list, int level){
    if (list->size() == 0) return;
    Dir temp;
    List<Dir>::Iterator iterator = list->get_begin_iterator();

    while(iterator.has_next()){
        temp = *iterator.next();
        for (int i = 0; i < level; ++i) cout << " ";
        cout << temp.name << endl;
        show((temp.dirs), level + 2);
    }
}


Dir * search_by_name(List<Dir> * list, string name)
{
    Dir *res = 0;
    Dir *temp;
    List<Dir>::Iterator iterator = list->get_begin_iterator();
    while(iterator.has_next()){
        temp = iterator.next();
        if (temp->name == name){
            res = temp;
            break;
        }
    }
    return res;
}


int main(int argc, char const *argv[])
{
    int n;

    cin >> n;

    string path;
    string name;
    List<string> * splited = new List<string>();


    Dir *root = new Dir;
    root->name = "root";
    root->dirs = new List<Dir>;


    // root->name = "root";
    // root->dirs = new List<Dir>();

    // // root->dirs->add();

    Dir* temp;
    Dir* temp_pointer;
    Dir* temp_root;

    temp = new Dir;
    temp->name = "temp1";
    temp->dirs = new List<Dir>;
    root->dirs->add(*temp);


    temp_root = new Dir;
    temp_root->name = "temp3";
    temp_root->dirs = new List<Dir>;
    temp->dirs->add(*temp_root);

    temp_root = new Dir;
    temp_root->name = "temp4";
    temp_root->dirs = new List<Dir>;
    temp->dirs->add(*temp_root);

    temp = new Dir;
    temp->name = "temp2";
    temp->dirs = new List<Dir>;
    root->dirs->add(*temp);

    show(((*(root)).dirs), 0);


    for (int i = 0; i < n; ++i)
    {
        cout << endl << i << " circle" << endl;
        cin >> path;
        splited->clear();

        cout << "cleared" << endl;
        split(splited, path, '/');
        cout << "splited: ";
        splited->show();

        List<string>::Iterator names = splited->get_begin_iterator();
        cout << "created iterator: ";
        temp_root = root;
        while(names.has_next()){
            name = *(names.next());
            cout << "name: " <<  name << endl;
            temp = search_by_name(temp_root->dirs, name);
            cout << "find pointer with that name: " << temp_pointer << endl;

            if (temp == 0)
            {
                temp = new Dir;
                temp->name = name;
                temp->dirs = new List<Dir>();
                cout << "before add" << endl;

                temp_root->dirs->add(*temp);
                cout << "added" << endl;
            }
            temp_root = temp;
            cout << "test" << endl;
        }

    }
    cout << "show";
    show((root->dirs), 0);
}