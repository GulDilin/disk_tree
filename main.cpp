#include "List.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

struct Dir
{
    string name;
    List<Dir> * dirs;

    friend bool operator < (const Dir &rhs, const Dir &lhs) {
        return (strcmp(rhs.name.c_str(), lhs.name.c_str()) <0);
    }
};

void split(List<string> * splited, string str, char separator){
    size_t i;
    while ((i = str.find_first_of(separator)) != string::npos)
    {
        if (i > 0) splited->add(str.substr(0, i));
        str = str.substr(i + 1);
    }
    if (str.length() > 0) splited->add(str);
}

void show(List<Dir> * list, int level){
    if (list->size() == 0) return;
    Dir tmp;
    List<Dir>::Node * node = list->get_first();

    for (int j = 0; j < list->size(); ++j) {
        tmp = node->item;
        for (int i = 0; i < level; ++i) cout << " ";
        cout << tmp.name << endl;
        show((tmp.dirs), level + 1);
        node = node->next;
    }
}

void sort(List<Dir> * list){
    if (list->size() == 0) return;
    list -> sort();
    List<Dir>::Node * node = list->get_first();

    for (int j = 0; j < list->size(); ++j) {
        sort(node->item.dirs);
        node = node->next;
    }
}


int main(int argc, char const *argv[])
{
    int n;

    cin >> n;

    string path;
    string name;
    auto * splited = new List<string>();


    Dir root;
    root.name = "root";
    root.dirs = new List<Dir>;

    Dir temp_root;
    for (int i = 0; i < n; ++i)
    {
        cin >> path;

        // split names by '/'
        splited->clear();
        split(splited, path, '\\');

        temp_root = root;
        List<string>::Node * node = splited->get_first();

        // add all splitted dir names
        for (int j = 0; j < splited->size(); ++j) {
            name = node->item;
            node = node->next;

            bool is_exist = false;
            List<Dir>::Node * node1 = temp_root.dirs->get_first();

            //search for directory with that name
            for (int k = 0; k < temp_root.dirs->size(); ++k) {
                if (node1->item.name == name){
                    temp_root = node1->item;
                    is_exist = true;
                    break;
                }
                node1 = node1->next;
            }

            //create dir if not exist
            if (!(is_exist))
            {
                Dir tmp;
                tmp.name = name;
                tmp.dirs = new List<Dir>();
                temp_root.dirs->add(tmp);
                temp_root = tmp;
            }
        }
    }
    sort((root.dirs));
    show((root.dirs), 0);
}