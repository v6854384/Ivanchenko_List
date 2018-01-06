#include <iostream>
#include <string.h>
#include <string>
#include <limits>
using namespace std;

struct Node{
	int znachenie;
	Node *next;
};

struct List{
	Node *first;
	Node *last;
};

void input(List &list, int znachenie){
	Node *current = new Node{znachenie, nullptr};
	if (list.first == nullptr)
		list.first = current;
	else{
		if (list.first -> next == nullptr) 
			list.first -> next = current;
		if (list.last != nullptr) 
			list.last -> next = current;
		list.last = current;
    }
}
void print_list(Node *&current){
	do{
		if (current -> next != nullptr)
			cout << current -> znachenie << " -> ";
		else
			cout << current -> znachenie << endl;
		current = current -> next;
	} while (current != nullptr);
}

void add_elements(List &list){
	cout << "Input new elements" << endl;
	string new_elements;
	int znachenie;
	Node *curr = new Node{znachenie, nullptr};
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, new_elements);
	for (int i = 0; i < new_elements.length(); i++){
		if (new_elements[i] != ' ')
			znachenie = znachenie * 10 + new_elements[i] - 48;
		else{
			input(list, znachenie);
			znachenie = 0;
		}
		if (i == new_elements.length() - 1)
			input(list,znachenie);
	}
}

int main(int argc, char *argv[]){
	int znachenie;
	List list;
	list.first = nullptr;
	list.last = nullptr;
	Node *current = nullptr;
	if (argc == 1)
		cout << "The list is empty" << endl;
	if (argc > 1){
		if (argc == 2){
			for (int i = 0; i < strlen(argv[1]); i++){
				if ((argv[1][i] >= '0') && (argv[1][i] <= '9'))
					znachenie = znachenie * 10 + argv[1][i] - 48;
				else{
					if (argv[1][i] == ','){
						input(list, znachenie);
						znachenie = 0;
					}
				}
				if (i == strlen(argv[1]) - 1)
					input(list, znachenie);
			}
		}
		else{
			for (int i = 0; i < argc - 1; i++){
				znachenie = atoi(argv[i + 1]);
				input(list, znachenie);
			}
		}
		string flag_exit = "no";
		while ((flag_exit != "y") && (flag_exit != "yes") && (flag_exit != "Yes") && (flag_exit != "YES")){
			cout << endl;
			cout << "Select one of the operations:" << endl;
			cout << "1. Print list" << endl;
			cout << "2. Add elements to the list" << endl;			
			cout << "3. End the program" << endl;
			int ch;
        		cin >> ch;
			switch(ch){
				case 1:
					current = list.first;
               		 		print_list(current);
               	 			current = nullptr;
					break;
				case 2:
					add_elements(list);
					break;
        case 3:
					cout << "Do you want to end the program?" << endl;
					cin >> flag_exit;
					break;
			}
		}
	}
}
