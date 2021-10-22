#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

class textEditor {

    private:
    char leftStack[100]="";
    char rightStack[100]="";
    int topl=-1;
    int topr=-1;
    public:
        void insertWord(char word[]);
        void insertCharacter(char character);
        bool deleteCharacter();
        bool backSpaceCharacter();
        void moveCursor(int position);
        void moveLeft(int position);
        void moveRight(int position);
        void findAndReplaceChar(char findWhat, char replaceWith);
        void examineTop();
        void push(char arr[],int& top, char &c);
        char pop(char arr[], int& top);
        bool isEmpty(char arr[], int top);
        int Size(char arr[], int top);
        char Top(char arr[], int top);
        void Print()
};

void textEditor::push(char arr[],int& top, char &c)
{
    top++;
    strncat(arr,&c,1);
}

char textEditor::pop(char arr[], int& top)
{

        char c = arr[top--];
        return c;

}

bool textEditor::isEmpty(char arr[], int top)
{
    if(top==-1)
        return true;
    return false;
}

int textEditor::Size(char arr[], int top)
{
    return top+1;
}

char textEditor::Top(char arr[], int top)
{
    return arr[top];
}

void textEditor::examineTop(){
    if(isEmpty(leftStack, topl))
        cout << "\nleftStack: empty\t";
    else{
        int S = Size(leftStack, topl);
        cout << "\nleftStack: " <<Top(leftStack,topl)<< "," <<S<< "\t\t";
    }
    if(isEmpty(rightStack, topr))
        cout << "\nrightStack: empty\n";
    else{
        int S = Size(rightStack, topr);
        cout << "\nrightStack: " <<Top(rightStack,topr)<< "," <<S<< "\t\t";
    }

}

void textEditor::insertWord(char word[]) {
    int i=0;

    while(word[i]!='\n') {
        insertCharacter(word[i]);
        i++;
    }
} 

void textEditor::insertCharacter(char character){
    push(leftStack,topl,character);
}

bool textEditor::deleteCharacter(){

    if (isEmpty(rightStack, topr))
        return false;
    else
        pop(rightStack,topr);
    return true;
}

bool textEditor::backSpaceCharacter(){

    if (isEmpty(leftStack, topl))
        return false;
    else
        pop(leftStack, topl);
    return true;
}

void textEditor::moveCursor(int position){

    int leftSize, rightSize, count;
    leftSize = Size(leftStack, topl);
    rightSize = Size(rightStack, topr);
    if (position < leftSize)
        moveLeft(position);
    else {
        count = position - leftSize;
        moveRight(count);
    }
}



void textEditor::moveLeft(int position){
    int leftSize;
    leftSize = Size(leftStack, topl);
    while(position!=leftSize) {
        char c = Top(leftStack,topl);
        push(rightStack,topr,c);
        pop(leftStack, topl);
        leftSize = Size(leftStack, topl);
    }
}

void textEditor::moveRight(int count){
    int rightSize, i=1;
    rightSize = Size(rightStack, topr);
    if (count > rightSize)
        cout << "Cannot move the cursor, right, to the specified position";
    else {
        while(i<=count) {
            char c = Top(rightStack,topr);
            push(leftStack, topl, c);
            pop(rightStack, topr);
            i++;
        } 
    } 
}

void textEditor::findAndReplaceChar(char findWhat, char replaceWith){

    int count=1, originalCursorPoistion = Size(leftStack, topl);
    moveCursor(0); //Move characters from left stack to right stack
    //Move characters from right stack to left stack and examine
    while(!isEmpty(rightStack, topr)) {
        if(Top(rightStack,topr)==findWhat) {
        deleteCharacter();
        insertCharacter(replaceWith);
        }
        else
            moveCursor(count);
            count++;
    }
    moveCursor(originalCursorPoistion); //Retain the original cursor position
}

void textEditor::Print()
{
    int i;
    char s,p;
    cout<<"Text Stack: ";
    for (i = 0; i <= leftStack.size(); i++)
        s = leftStack[i];
        cout<<s;
    cout<<"\n";

    cout<<"Redo Stack: ";
    for (i = 0; i <= rightStack.size(); i++)
        p= rightStack[i];
        cout<<p;
   cout<<"\n";

}
int main() {
    int i=0,num;
    char text[80];
    char char1,char2;
    int pos;
    textEditor txt;

    while(1)
    {   int choice;
        cout<<"\nTEXT EDITOR\n";
        cout<<"---------------------------------------------------------------------\n";
        cout<<"Menu:\n";
        cout<<"1. Write\n2. Cursor Movement\n3. Delete letter from right stack\n4. Delete letter from left stack\n5. Find & replace\n6. Print\n7. Exit";
        cout<<"\n---------------------------------------------------------------------";
        cout<<"\nEnter choice: ";
        cin>>choice;

        switch (choice)
        {
            case 1:
                cout << "Enter the word to be inserted: ";
                fflush(stdin);
                fgets(text,80,stdin);
                cout<<text<<" ";
                txt.insertWord(text);

                cout << "Inserting the word:";
                txt.examineTop();
                break;
            case 2:
                cout << "Enter the position you want to shift the cursor: ";
                cin>>pos;
                cout << "Move cursor to the position: "<<pos<<endl;
                txt.moveCursor(pos);
                txt.examineTop();
                break;
            case 3:
                cout << "Enter how many letter permanantly delete from right stack: ";
                cin>>num;
                for(i=0;i<num;i++){
                    if(!txt.deleteCharacter())
                        cout << "There is nothing to delete. Move your cursor accordingly to delete the character";
                    else
                        cout << "Delete characters using DEL: ";
                        txt.examineTop();
                }

                break;
            case 4:
                cout << "Enter how many letter permanantly delete from left stack: ";
                cin>>num;
                for(i=0;i<num;i++){
                    if(!txt.backSpaceCharacter())
                        cout << "There is nothing to delete. Move your cursor accordingly to delete the character";
                    else
                        cout << "Delete characters using Backspace: ";
                        txt.examineTop();
                }

                break;
            case 5:
                cout << "Which letter do you want to replace: ";
                cin>>char1;
                cout << "With what letter: ";
                cin>>char2;
                txt.findAndReplaceChar(char1,char2);
                //cout << "Replace occurrences of"<< char1<< "with"<< char2: ";
                txt.examineTop();

            case 6:
                txt.Print();

            default:
                cout<<"Invalid Input!\n";
        }
    }
    return 0;
}
 