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
	Node *first; // Первый элемент
	Node *last; // Последний элемент
};

// Добавить элемент в конец списка
void input(List &list, int znachenie){
	Node *current = new Node{ znachenie, nullptr }; // Создаем новый элемент
	if (list.first == nullptr)   // Список пуст
		list.last=list.first = current;
	else{
		list.last->next = current;   // Элемент будет за последним
		list.last = current; // Элемент становится последним
	}
}
void print_list(List &list){
	for (Node *p = list.first; p; p = p->next)
	{
		cout << p->znachenie;
		if (p->next != nullptr) cout << "->"; // Элемент не последний
	}

}

void add_elements(List &list){
	cout << "Input new elements" << endl;
	string new_elements;
	int znachenie=0;
	Node *curr = new Node{ znachenie, nullptr };
//	Node *curr = new Node;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, new_elements);
	// В строке элеменрты списка через пробелы
	for (int i = 0; i < new_elements.length(); i++){
		if (new_elements[i] != ' ')
			znachenie = znachenie * 10 + new_elements[i] - 48;
		else{
			input(list, znachenie);
			znachenie = 0;
		}
		if (i == new_elements.length() - 1)
			input(list, znachenie);
	}
}
// Удаляем элемент из списка с заданным значением (значение вводится с клавиатуры)

// Извлечь элемент p из списка, функция 
// возвращает адрес извлекаемого элемента или 0 в случае ошибки
Node * removeP(List & list, Node *p)
{
	Node *pF = list.first;
	if (pF == 0) return 0;
	if (p == pF) //  Извлекаемый элемент первый
	{
		list.first = pF->next; // Первым будет второй элемент
		if (list.first == nullptr) list.last = nullptr;
		return p;
	}
	Node *pPred = pF; // Поиск предыдущего элемента
	while (pPred->next != p) {
		pPred = pPred->next;
		if (pPred == 0) // Элемента p нет в списке
			return 0;
	}
	pPred->next = p->next;
	if (p->next == nullptr) list.last = pPred;
	return p;

}

void delete_element(List &list){
	cout << "Input deleting element" << endl;
	int deleting_element = 0;
	cin >> deleting_element;
	bool element_availability = false;
	for (Node *p = list.first; p; )
	{
		if (p->znachenie == deleting_element)
		{
			Node *pNext = p->next;
			removeP(list, p);
			delete p;
			p = pNext;
		}
		else p = p->next;
	}

	if (element_availability == false)
		cout << "Such element isn't in your list" << endl;
}

// Ищем позицию элемента с заданным значением (значение вводится с клавиатуры)
void find_pozitions(List &list){
	cout << "Input element whose position you want to find" << endl;
	int finding_element = 0;
	cin >> finding_element;
	int pozitions = 0;
	bool element_availability = false;
	Node *current = list.first;
	while (current != nullptr){
		if (current->znachenie == finding_element){
			cout << pozitions << " ";
			pozitions++;
			element_availability = true;
		}
		else
			pozitions++;
		current = current->next;
	}
	if (element_availability == false)
		cout << "Such element isn't in your list" << endl;
}

// Заменем в элементе его значение, позиция и значение вводится с клавиатуры
void replace_element(List &list){
	cout << "Input pozition and new element" << endl;
	int pozition = 0, new_element, i = 0;
	cin >> pozition >> new_element;
	bool element_availability = false;
	Node *current = list.first;
	while (current != nullptr){
		if (i == pozition){
			current->znachenie = new_element;
			element_availability = true;
		}
		current = current->next;
		i++;
	}
	if (element_availability == false)
		cout << "Such pozition isn't in your list";
}

// Сортировка списка через массив, вначале список записывается в массив
void sort_elements(List &list){
	Node *current = list.first;
	int n = 0;
	while (current != nullptr){
		n++;
		current = current->next;
	}
	current = list.first;
	int *a=new int[n];
	for (int i = 0; i < n; i++){
		a[i] = current->znachenie;
		current = current->next;
	}
	// Сортировка массива методом пузырька
	for (int i = n - 1; i >= 0; i--){
		for (int j = 0; j < i; j++){
			if (a[j] > a[j + 1]){
				int repl = a[j];
				a[j] = a[j + 1];
				a[j + 1] = repl;
			}
		}
	}
	// Переписываем массив в список
	current = list.first;
	for (int i = 0; i < n; i++){
		current->znachenie = a[i];
		current = current->next;
	}
	delete[] a;
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
		if (argc == 2){ // Все данные в одной строке разделены , 
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
		else{ // Все данные в разных строках
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
			switch (ch){
			case 1:
				current = list.first;
				if (current != nullptr)
					print_list(list);
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
