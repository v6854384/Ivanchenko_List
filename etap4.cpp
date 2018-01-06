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
void print_list(Node *current){
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

void delete_element(List &list){
	cout << "Input deleting element" << endl;
	int deleting_element = 0;
	cin >> deleting_element;
	bool element_availability = false;
	Node *current = list.first;
	Node *previous = nullptr;
	if (current -> znachenie == deleting_element){
		if ((current == (list.first)) && (list.first != list.last)){
			list.first = list.first -> next;
			delete current;
			element_availability = true;
		}
		else{
			if ((current == list.first) && (list.first == list.last)){
				list.first = nullptr;
				list.last = list.first;
				delete current;
				element_availability = true;
			}
		}
	}
	previous = current;
	current = current -> next;
	while (current != nullptr){
		if ((current -> znachenie == deleting_element) && (current != list.last)){
			previous -> next = current -> next;
			delete current;
			element_availability = true;
		}
		else{
			if ((current -> znachenie == deleting_element) && (current == list.last)){
				list.last = previous;
				list.last -> next = nullptr;
				delete current;
				element_availability = true;
			}
		}
		previous = current;
		current = current -> next;
	}
	if (element_availability == false)
		cout << "Such element isn't in your list" << endl;
}

void find_pozitions(List &list){
	cout << "Input element whose position you want to find" << endl;
	int finding_element = 0;
	cin >> finding_element;
	int pozitions = 0;
	bool element_availability = false;
	Node *current = list.first;
	while (current != nullptr){
		if (current -> znachenie == finding_element){
			cout << pozitions << " ";
			pozitions++;
			element_availability = true;
		}
		else
			pozitions++;
		current = current -> next;
	}
	if (element_availability == false)
		cout << "Such element isn't in your list" << endl;
}

void replace_element(List &list){
	cout << "Input pozition and new element" << endl;
	int pozition = 0, new_element, i = 0;
	cin >> pozition >> new_element;
	bool element_availability = false;
	Node *current = list.first;
	while (current != nullptr){
		if (i == pozition){
			current -> znachenie = new_element;
			element_availability = true;
		}
		current = current -> next;
		i++;   
	}
	if (element_availability == false)
		cout << "Such pozition isn't in your list";
}

void sort_elements(List &list){
	Node *current = list.first;
	int n = 0;
	while (current != nullptr){
		n++;
		current = current -> next;
	}
	current = list.first;
	int a[n];
	for (int i = 0; i < n; i++){
		a[i] = current -> znachenie;
		current = current -> next;
	}
	for (int i = n - 1; i >= 0; i--){
		for (int j = 0; j < i; j++){
			if (a[j] > a[j + 1]){
				int repl = a[j];
				a[j] = a[j + 1];
				a[j + 1] = repl;
			}
		}
	}
	current = list.first;
	for (int i = 0; i < n; i++){
		current -> znachenie = a[i];
		current = current -> next;
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
			cout << "3. Delete element" << endl;
			cout << "4. Find elements' positions" << endl;
			cout << "5. Replace element" << endl;
			cout << "6. Sort elements" << endl;
			cout << "7. End the program" << endl;
			int ch;
        		cin >> ch;
			switch(ch){
				case 1:
					current = list.first;
					if(current != nullptr)
						print_list(current);
					else
						cout << "The list is empty" << endl;
               	 			current = nullptr;
					break;
				case 2:
					add_elements(list);
					break;
				case 3:
					delete_element(list);
					break;
				case 4:
					find_pozitions(list);
					break;
				case 5:
					replace_element(list);
					break;
				case 6:
					sort_elements(list);
					break;
				case 7:
					cout << "Do you want to end the program?" << endl;
					cin >> flag_exit;
					break;
			}
		}
		cout << "Good bye!" << endl;
	}
}

