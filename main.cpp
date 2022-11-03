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
void outputSave(Node* root, ofstream &of);
void inputSave(Node* &root, ifstream &f);
bool getAnswer();
void game(Node* root);

int main()
{
    Node* root = NULL;
    ifstream file;

    file.open("save.txt");
    inputSave(root, file);

    int ex = 0;
    while (ex == 0)
    {
        game(root);

        cout << "Хотите продолжить?" << endl;
        cout << "0 - да" << endl;
        cout << "любая другая цифра - нет" << endl;
        cin >> ex;
    }  
    ofstream of;
    of.open("save.txt");
    outputSave(root, of);
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
                cout << "____________________________" << endl;
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
                animal = "Это " + animal + "?";
                
                temp = root->data;
                root->data = question;

                addElement(root, animal, OBJ_LEFT);
                addElement(root, temp, OBJ_RIGHT);
                cout << "____________________________" << endl;
                break;
            }
        }
    }
}

void inputSave(Node* &root, ifstream &file)
{
    string temp;
    if (!getline(file, temp) || temp == "")
    {
        return;
    }

    addElement(root, temp, OBJ_LEFT);
    inputSave(root->l, file);
    inputSave(root->r, file);
}

void outputSave(Node* root, ofstream &of)
{
    if (root == NULL)
    {
        of << "" << endl;
        return;
    }

    of << root->data << endl;
    outputSave(root->l, of);
    outputSave(root->r, of);
}
