
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void initialization(int arrayA[],int arrayB[]);
int deal(int arrayA[],int arrayB[]);
void translate(int array[],double card[]);
double player_state(double card[],int arrayA[],int arrayB[]);
void computer_state(double card[],int arrayA[],int arrayB[]);
string input_check();

int main()
{
    srand(time(NULL));
    double card[52] = {1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5,
        1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5,
        1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5,
        1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5};
    int userCard[12] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int compCard[12] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    computer_state(card, userCard, compCard);
    while (true)
    {
        cout << "Would you like to play it again?(y/n)" << endl;
        string answer = input_check();
        if (answer == "y" || answer == "Y")
        {
            initialization(userCard, compCard);
            computer_state(card, userCard, compCard);
        }
        else
        {
            cout << "Bye! Never try it again!" << endl;
            return 0;
        }
    }
}

string input_check()
{
    string input;
    cin >> input;
    while (true)
    {
        if (input == "y" || input == "Y" || input == "n" || input == "N") return input;
        else
         {cout << "Please enter y or n" << endl; cin >> input;}
    }
}

void initialization(int arrayA[],int arrayB[])     //restart the game
{
    for (int i =0;i<12;++i)
    {arrayA[i] = -1;arrayB[i] = -1;}
}

int deal(int arrayA[],int arrayB[])      //generate an unused card
{
    while (true)
    {
        int arrayNum = rand() % 52,Flag = 0;
        for (int i=0;i<12;++i)
        {  if (arrayA[i] == arrayNum || arrayB[i] == arrayNum)
                Flag = 1;}
        if (Flag == 0) return arrayNum;
    }
}

void translate(int array[],double card[])     //show user the card he has
{
    for (int i = 0;array[i] != -1;++i)
    {
        int cardNum,arrayNum = array[i];
        cardNum = arrayNum % 13 + 1;
        switch (arrayNum / 13)
        {
            case 0 : cout << "Heart ";break;
            case 1 : cout << "Spade ";break;
            case 2 : cout << "Diamond ";break;
            case 3 : cout << "Club ";break;
        }
        switch (cardNum)
        {
            case 11 : cout << 'J';break;
            case 12 : cout << 'Q';break;
            case 13 : cout << 'K';break;
            default: cout << cardNum;break;
        }
        cout << ';';
    }
    cout << endl;
}

double player_state(double card[],int arrayA[],int arrayB[])
{
    int i = 0;
    for (i = 0;i < 2;++i)
        arrayA[i] = deal(arrayA,arrayB);
    cout << "You have got the cards ";
    translate(arrayA,card);     //initialize user
    double cardPoint = card[arrayA[0]] + card[arrayA[1]];
    while (true)
    {
        if (cardPoint > 21)
        {cout << "You have losed." << endl;
            return 0;}     //the user has losed derectly
        cout << "Whether do you want another card?(Y/N)" << endl;
        string answer = input_check();
        if (answer == "Y" || answer == "y")
        {arrayA[i] = deal(arrayA,arrayB);cardPoint += card[arrayA[i]];++i;    //the user pick another card
         cout << "Given another card: ";
            translate(arrayA,card);}
        else return cardPoint;
    }
}

void computer_state(double card[],int arrayA[],int arrayB[])
{
    double cardPointA = player_state(card,arrayA,arrayB);
    if (cardPointA == 0)
    {cout << "I win!" << endl;return;}     //case 1: if the player's card number larger than 21, the game ended
    int i = 0;
    for (i = 0;i < 2;++i)
        arrayB[i] = deal(arrayA,arrayB);
    cout << "\nI have got the cards: ";
    translate(arrayB,card);     //initialize
    double cardPointB = card[arrayB[0]] + card[arrayB[1]];
    if (cardPointB > 21)
    {cout << "You win!" << endl;
        return;}     //case 2: if the computer's card number larger than 21, the game ended
    while (cardPointB <= cardPointA)
    {
        if (cardPointB < cardPointA)
        {arrayB[i] = deal(arrayA,arrayB);cardPointB += card[arrayB[i]];++i;
          cout << "Given another card: ";
            translate(arrayB,card);}    //the computer pick another card
        else
        {
            int number = 0;
            for (int j = 0;arrayA[j] != -1;++j)
                number +=1;      //calculate the number of user's card
            if (number > i)
                {arrayB[i] = deal(arrayA,arrayB);cardPointB += card[arrayB[i]];++i;
                cout << "Given another card: ";
                    translate(arrayB,card);}     //the computer pick another card
            else if (number < i)
                {cout << "I win!" << endl;return;}     //case 3: with the same points, computer has more cards, the game ended
            else
                {
                    if (cardPointB == 21)
                    {cout << "It's a win-win!" << endl;return;}    //case 4: we harmoniously ended the game
                    else
                    {arrayB[i] = deal(arrayA,arrayB);cardPointB += card[arrayB[i]];++i;
                            cout << "Given another card: ";
                            translate(arrayB,card);}     //the computer pick another card
                }
        }
        if (cardPointB > 21)
        {cout << "You win!" << endl;
            return;}     //case 2(again): if the computer's card number larger than 21, the game ended
    }
    cout << "I win!" << endl;return;   //case 5: Finally! The computer has won!!!! TAT
}
