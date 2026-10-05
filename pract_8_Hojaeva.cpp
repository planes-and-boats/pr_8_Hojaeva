#define DEBUG_TEST_MODE

#include <iostream>
#include <string>
#include <istream>
#include <exception>

using namespace std;

struct Message {
	int id;
	char sender[50];
	int importance;
};

struct Node {
	Message message;
	Node* next = nullptr;
	Node* prev = nullptr;
};

struct List {
	Node* head = nullptr;
	Node* tail = nullptr;
};

static void printMessage(Message message) {
	cout << "ID: " << message.id << " | Важность: " << message.importance << endl;
	cout << "Текст: " << message.sender << endl;
}

static Message NewMessage() {
	Message message{};
	string num;
	message.id = rand() % 1000;
	cout << "Введите текст сообщение: ";
	cin.ignore();
	cin.getline(message.sender, 50);
	cout << "Введите важность сообщения: ";
	cin >> num;
	try {
		message.importance = stoi(num);
	}
	catch (exception) { throw invalid_argument("не удалось переобразовать строчку в число."); }
	return message;
}

static Message DefaultMessage() {
	Message message = {
		(rand() % 1000),
		"This is Massive Attack!",
		34
	};
	printMessage(message);
	return message;
}

static void push_front(Message message, List* list) {
	Node* ptr = new Node{ message, nullptr, nullptr };
	ptr->next = list->head;
	if (list->head != nullptr)
		list->head->prev = ptr;
	if (list->tail == nullptr)
		list->tail = ptr;
	list->head = ptr;

	ptr = nullptr;
}
static void push_back(Message message, List* list) {
	Node* ptr = new Node{ message, nullptr, nullptr };
	ptr->prev = list->tail;
	if (list->tail != nullptr)
		list->tail->next = ptr;
	if (list->head == nullptr)
		list->head = ptr;
	list->tail = ptr;

	ptr = nullptr;
}

static void pop_front(List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		if (list->head == nullptr)
			return;
		Node* ptr = list->head->next;
		if (ptr != nullptr)
			ptr->prev = nullptr;
		else
			list->tail = nullptr;
		delete(list->head);
		list->head = ptr;

		ptr = nullptr;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

static void pop_back(List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		if (list->tail == nullptr)
			return;
		Node* ptr = list->tail->prev;
		if (ptr != nullptr)
			ptr->next = nullptr;
		else
			list->head = nullptr;
		delete(list->tail);
		list->tail = ptr;

		ptr = nullptr;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

static void display_forward(List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		Node* ptr = list->head;
		while (ptr != nullptr) {
			printMessage(ptr->message);
			cout << endl;
			ptr = ptr->next;
		}
		cout << "< End >" << endl;

		ptr = nullptr;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

static void display_backward(List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		Node* ptr = list->tail;
		while (ptr != nullptr) {
			printMessage(ptr->message);
			cout << endl;
			ptr = ptr->prev;
		}
		cout << "\t< End >" << endl;

		ptr = nullptr;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

static Node* find(int _id, List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		Node* ptr = list->tail;
		while (ptr != nullptr) {
			if (ptr->message.id == _id) {
				return ptr;
				break;
			}
			ptr = ptr->prev;
		}
	}
	return nullptr;
}

static void deleteMessage(Node* node, List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		if (node == nullptr)
			return;
		if (node->next == nullptr) {
			pop_back(list);
			return;
		}
		if (node->prev == nullptr) {
			pop_front(list);
			return;
		}
		Node* prev = node->prev;
		Node* next = node->next;
		prev->next = next;
		next->prev = prev;

		delete(node);
		node = nullptr;
		prev = nullptr;
		next = nullptr;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

static void clear(List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		Node* ptr = list->head;
		while (ptr != nullptr) {
			Node* ptrNext = ptr->next;
			delete(ptr);
			ptr = ptrNext;
			ptrNext = nullptr;
		}
		ptr = nullptr;
	}
	list->head = nullptr;
	list->tail = nullptr;

	cout << " --- List is clean now." << endl;
}

static void getMaxImportance(List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		Node* maxPtr = list->head;
		Node* ptr = maxPtr->next;
		while (ptr != nullptr) {
			if (maxPtr->message.importance < ptr->message.importance)
				maxPtr = ptr;
			ptr = ptr->next;
		}
		printMessage(maxPtr->message);

		ptr = nullptr;
		maxPtr = nullptr;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

static void deleteOutImportance(int importance, List* list) {
	if (list->head != nullptr && list->tail != nullptr) {
		int count = 0;
		Node* ptr = list->head;
		while (ptr != nullptr) {
			Node* ptrNext = ptr->next;
			if (importance > ptr->message.importance) {
				deleteMessage(ptr, list);
				count++;
			}
			ptr = ptrNext;
			ptrNext = nullptr;
		}
		ptr = nullptr;

		cout << " --- Удалено сообщений: " << count << endl;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

static void moveMessageToHead(Node* node, List* list) {
	if (node == nullptr)
		return;
	if (list->head != nullptr && list->tail != nullptr) {

		if (node == list->head)
			return;

		if (node == list->tail) {
			list->tail = node->prev;
			list->tail->next = nullptr;
		}
		else {
			Node* prev = node->prev;
			Node* next = node->next;
			if (next != nullptr && prev != nullptr) {
				prev->next = next;
				next->prev = prev;
			}
			prev = nullptr;
			next = nullptr;
		}

		node->next = list->head;
		list->head->prev = node;
		list->head = node;

		node = nullptr;
	}
	else {
		cout << " --- List is clean." << endl;
	}
}

int main()
{
	setlocale(NULL, "Russian");
	srand(time(NULL));

	int choice = 0;
	string choice_str;
	List list;

	Message message_test_1 = { (rand() % 1000), "Hello, world!", (rand() % 100) };
	Message message_test_2 = { (rand() % 1000), "ССП огурца!", (rand() % 100) };
	Message message_test_3 = { (999), "I am Batman!", 96 };
	Message message_test_4 = { (rand() % 1000), "This is Blur!", 60 };
	Message message_test_5 = { (rand() % 1000), "Portal Gun!", 94 };
	Message message_test_6 = { (666), "This is AC/DC!", (rand() % 100) };
	Message message_test_7 = { (rand() % 1000), "This is The Black Keys!", 87 };
	Message message_test_8 = { (rand() % 1000), "Blue Monday! This is New Order!", (rand() % 100) };

	push_back(message_test_1, &list);
	push_back(message_test_2, &list);
	push_back(message_test_3, &list);
	push_back(message_test_4, &list);
	push_back(message_test_5, &list);
	push_back(message_test_6, &list);
	push_back(message_test_7, &list);
	push_back(message_test_8, &list);

	cout << endl << "--- < История сообщений > ---" << endl;

	do {
		cout << endl << "\t< Меню >" << endl << endl;

		cout << "1. Добавление сообщения в начало." << endl;
		cout << "2. Добавление сообщения в конец." << endl;
		cout << "3. Удалить первое сообщение." << endl;
		cout << "4. Удалить последнее сообщение." << endl;
		cout << "5. Вывести историю." << endl;
		cout << "6. Вывести историю в обратном порядке." << endl;
		cout << "7. Найти сообщение." << endl;
		cout << "8. Полная очистка истории." << endl;
		cout << "9. Вывод сообщения с максимальной важностью." << endl;
		cout << "10. Удалить сообщения вне порога важности." << endl;
		cout << "11. Переместить сообщение в начало списка." << endl;
		cout << "0. Выход." << endl << endl;

		cout << "Ваш выбор: ";

		try {
			cin >> choice_str;
			cout << endl;
			try {
				choice = stoi(choice_str);
			}
			catch (exception) { throw invalid_argument("не удалось переобразовать строчку в число."); }

			switch (choice) {
			case 1: {

#ifdef DEBUG_TEST_MODE

				cout << "< Добавление дефолтного элемента в начало списка >" << endl << endl;
				Message message = DefaultMessage();
				push_front(message, &list);
				cout << endl;
				cout << "\t --- Успех!" << endl;

#else

				cout << "< Добавление элемента в начало списка >" << endl << endl;
				Message message = NewMessage();
				push_front(message, &list);
				cout << endl;
				cout << "\t --- Успех!" << endl;

#endif // DEBUG_TEST_MODE

				break;
			}
			case 2: {

#ifdef DEBUG_TEST_MODE

				cout << "< Добавление дефолтного элемента в конец списка >" << endl << endl;
				Message message = DefaultMessage();
				push_back(message, &list);
				cout << endl;
				cout << "\t --- Успех!" << endl;

#else

				cout << "< Добавление элемента в конец списка >" << endl << endl;
				Message message = NewMessage();
				push_back(message, &list);
				cout << endl;
				cout << "\t --- Успех!" << endl;

#endif // DEBUG_TEST_MODE

				break;
			}
			case 3: {
				cout << "< Удаление первого элемента >" << endl;
				cout << endl;
				pop_front(&list);
				cout << "\t --- Успех!" << endl;
				break;
			}
			case 4: {
				cout << "< Удаление последнего элемента >" << endl;
				cout << endl;
				pop_back(&list);
				cout << "\t --- Успех!" << endl;
				break;
			}
			case 5: {
				cout << "< Список сообщений от начала к концу >" << endl << endl;
				display_forward(&list);
				break;
			}
			case 6: {
				cout << "< Список сообщений от конца к началу >" << endl << endl;;
				display_backward(&list);
				break;
			}
			case 7: {

#ifdef DEBUG_TEST_MODE

				cout << "< Поиск элемента по ID: 666 >" << endl << endl;
				Node* ptr = find(666, &list);
				if (ptr == nullptr)
					cout << " --- Сообщение ненайдено." << endl;
				else {
					printMessage(ptr->message);
					cout << endl;
					cout << "< Удаление найденного элемента >" << endl << endl;
					deleteMessage(ptr, &list);
					cout << "\t --- Успех!" << endl;

					ptr = nullptr;
				}

#else

				cout << "< Поиск элемента по ID >" << endl << endl;
				cout << "Введите id: ";
				cin >> choice_str;
				cout << endl;
				try {
					choice = stoi(choice_str);
				}
				catch (exception) { throw invalid_argument("не удалось переобразовать строчку в число."); }

				Node* ptr = find(choice, &list);
				if (ptr == nullptr)
					cout << " --- Сообщение ненайдено." << endl;
				else {
					printMessage(ptr->message);
					cout << endl;

					cout << "< Удалиить найденный элемент? > \t\n1. Да \t\n2. Нет (любая другая клавиша)" << endl;
					cout << "Ваш выбор: ";
					cin >> choice_str;
					if (choice_str == "1") {
						deleteMessage(ptr, &list);
						cout << "\t --- Успех!" << endl;
					}

					ptr = nullptr;
				}

#endif // DEBUG_TEST_MODE

				break;
			}
			case 8: {
				cout << "< Очистка истории >" << endl << endl;
				clear(&list);
				break;
			}
			case 9: {
				cout << "< Вывод элемента с максемальной важностью >" << endl << endl;
				getMaxImportance(&list);
				break;
			}
			case 10: {

#ifdef DEBUG_TEST_MODE

				cout << "< Удаление элементов вне порога важности - 50 >" << endl << endl;
				deleteOutImportance(50, &list);
				cout << endl;
				cout << "\t --- Успех!" << endl;

#else

				cout << "< Удаление элементов вне порога важности >" << endl << endl;
				cout << "Введите порог важности: ";
				cin >> choice_str;
				cout << endl;
				try {
					choice = stoi(choice_str);
				}
				catch (exception) { throw invalid_argument("не удалось переобразовать строчку в число."); }

				deleteOutImportance(choice, &list);
				cout << endl;
				cout << "\t --- Успех!" << endl;

#endif // DEBUG_TEST_MODE

				break;
			}
			case 11: {

#ifdef DEBUG_TEST_MODE

				cout << "< Перемещение элемента по ID: 999 >" << endl << endl;
				Node* ptr = find(999, &list);
				if (ptr == nullptr)
					cout << " --- Сообщение ненайдено." << endl;
				else {
					printMessage(ptr->message);
					cout << endl;

					cout << "< Перемещение элемента в начало >" << endl << endl;
					moveMessageToHead(ptr, &list);
					cout << "\t --- Успех!" << endl;
				}

#else

				cout << "< Перемещение элемента >" << endl << endl;
				cout << "Введите ID: ";
				cin >> choice_str;
				cout << endl;
				try {
					choice = stoi(choice_str);
				}
				catch (exception) { throw invalid_argument("не удалось переобразовать строчку в число."); }

				Node* ptr = find(choice, &list);
				if (ptr == nullptr)
					cout << " --- Сообщение ненайдено." << endl;
				else {
					printMessage(ptr->message);
					cout << endl;

					cout << "< Перемещение элемента в начало >" << endl << endl;
					moveMessageToHead(ptr, &list);
					cout << "\t --- Успех!" << endl;

					ptr = nullptr;
				}

#endif // DEBUG_TEST_MODE

				break;
			}
			case 0: {
				cout << "Программа завершенна!" << endl;
				clear(&list);
				break;
			}
			default: {
				cout << "Неверный пункт в меню! Попробуйте еще раз." << endl;
				break;
			}
			}
		}
		catch (invalid_argument& e) {
			cout << endl << "Ошибка валидации: " << e.what() << endl;
		}
		catch (runtime_error& e) {
			cout << endl << "Ошибка работы программы: " << e.what() << endl;
		}
		catch (exception& e) {
			cout << endl << "Ошибка : " << e.what() << endl;
		}

	} while (choice != 0);
}