#include <iostream>
#include <stdio.h>
#include <string.h>
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
		cout << "Select one of the operation:" << endl;
		cout << "1. Print list" << endl;
		int ch;
        	cin >> ch;
		switch(ch){
			case 1:
				current = list.first;
                		print_list(current);
                		current = nullptr;
				break;
		}
	}
}
