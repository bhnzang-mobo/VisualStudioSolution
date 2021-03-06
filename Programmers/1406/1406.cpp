#pragma warning(disable: 4996);
#include <iostream>

using namespace std;
typedef struct node {
	struct node* prev;
	struct node* next;
	char id;
}node;
typedef struct mystr {
	struct node* cur;
	struct node* front;
}mystr;

void str_init(mystr *mystr,char id) {
	mystr->cur = (node*)malloc(sizeof(node));
	node* dummy_last = (node*)malloc(sizeof(node));
	dummy_last->id = '\0';
	dummy_last->next = NULL;
	dummy_last->prev = mystr->cur;

	mystr->cur->prev = NULL;
	mystr->cur->next = dummy_last;
	mystr->cur->id = id;
	mystr->front = mystr->cur;
}

void str_insert(mystr* mystr, char id) {
	node* newnode = (node*)malloc(sizeof(node));

	newnode->id=id;
	newnode->prev = mystr->cur->prev;
	newnode->next = mystr->cur;
	if (mystr->cur== mystr->front) {
		mystr->front = newnode;
	}
	else {
		mystr->cur->prev->next = newnode;
	}
	mystr->cur->prev = newnode;

}

char str_delete(mystr* mystr) {
	node* delnode = mystr->cur->prev;
	if (delnode == NULL) {
		return '\0';
	}
	if (delnode == mystr->front) {
		mystr->front = delnode->next;
	}
	else {
		delnode->prev->next = mystr->cur;
	}
	char deldata = delnode->id;

	mystr->cur->prev = delnode->prev;
	free(delnode);

	return deldata;
}

void str_prev(mystr* mystr) {
	if (mystr->cur->prev != NULL) {
		mystr->cur = mystr->cur->prev;
	}
}
void str_next(mystr* mystr) {
	if (mystr->cur->next != NULL) {
		mystr->cur = mystr->cur->next;
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	mystr cont;
	char inp = cin.get();
	str_init(&cont, inp);
	str_next(&cont);
	if (inp != '\n') {
		cin.get(inp);
		while (inp != '\n') {
			str_insert(&cont, inp);
			scanf("%c", &inp);
		}
	}
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		char flag;
		scanf(" %c", &flag);
		switch (flag) {
		case 'L' :
			str_prev(&cont);
			break;
		case 'D':
			str_next(&cont);
			break;
		case 'B':
			str_delete(&cont);
			break;
		case 'P':
			char new_char;
			scanf(" %c", &new_char);
			str_insert(&cont, new_char);
			break;
		default:
			break;
		}
	}
	node* ans = cont.front;
	while (ans->next!=NULL) {
		cout << ans->id;
		ans = ans->next;
	}
}


