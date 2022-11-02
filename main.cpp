#include <iostream>
#include <fstream>

using namespace std;

typedef struct Node
{
    string data;
    Node *l;
    Node *r;
} Node;

typedef enum type_obj_tree { OBJ_LEFT, OBJ_RIGHT} OBJ_TYPE;

Node* addElement(Node* &root, string animalLeft, OBJ_TYPE type);
Node* inputSave(Node* &root);
bool getAnswer();
void game(Node* root);

int main()
{
    Node* root = NULL;
    addElement(root, "Это домашнее животное??", OBJ_LEFT);
    addElement(root, "кошка", OBJ_LEFT);
    addElement(root, "волк", OBJ_RIGHT);

    int ex = 0;
    while (ex == 0)
    {
        game(root);

        cout << "Хотите продолжить?" << endl;
        cout << "0 - да" << endl;
        cout << "любая другая цифра - нет" << endl;
        cin >> ex;
    }   
}

bool getAnswer()
{
    cout << "Да - 1" << endl;
    cout << "Нет - 2" << endl;

    int response;
    cin >> response;
    while (response != 1 && response != 2)
    {
        cout << "Введено неверное значение" << endl;
        cin >> response;
    }
    if (response == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Node* addElement(Node* &root, string input, OBJ_TYPE type)
{
    Node* res = new Node;
    res->l = NULL;
    res->r = NULL;
    res->data = input;

    if (root == NULL)
    {
        root = res;
    }
    else
    {
        switch (type)
        {
        case OBJ_LEFT:
            root->l = res;
            break;
        case OBJ_RIGHT:
            root->r = res;
            break;
        }
    }
    return res;
}

void game(Node *root)
{
    while (true)
    {
        cout << root->data << endl;
        if (getAnswer())
        {
            if (root->l != NULL)
            {
                root = root->l;
            }
            else
            {
                cout << "Ура, победа" << endl;
                break;
            }
        }
        else
        {   
            if (root->r != NULL)
            { 
                root = root->r;
            }
            else
            {
                string question;
                string animal;
                string temp;

                cout << "К сожалению, я не знаю, что это за животное(" << endl;
                cout << "Пожалуйста, введите вопрос при ответе 'да', на который, ответом будет ваше животное" << endl;

                cin.ignore();
                getline(cin, question);

                cout << "Пожалуйста, ввдеите животное, которое загадали" << endl;

                getline(cin, animal);
                
                temp = root->data;
                root->data = question;

                addElement(root, animal, OBJ_LEFT);
                addElement(root, temp, OBJ_RIGHT);
                break;
            }
        }
    }
}

Node* inputSave(Node* &root)
{
    ifstream file;
    file.open("save.txt");
    if (file.is_open())
    {
        cout << "Сохранение загружено" << endl;
        cout << "_______________________________" << endl;

        int i = 0;
        while (!file.eof())
        {
            string temp;
            getline(file, temp);
            
        }
        file.close();
    }
}