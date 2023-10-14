#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <map>

using namespace std;

//Inicializar La Baraja De Cartas
vector<string> deck = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q","K"};

//Baraja la Baraja
void shuffleDeck(){
    static mt19937 mt(static_cast<unsigned int>(time(nullptr)));
    shuffle(deck.begin(), deck.end(), mt);
}

//Darle Valor A Las Cartas
int getCardValue(string card){
    if (card== "A"){
        return 11;
    }else if(card =="K" || card =="Q" || card =="J"){
        return 10;
    }else{
        return stoi(card);
    }
}

//Calcular El Valor De Una Mano
int calculateHandValue(vector<string>hand){
    int value = 0;
    int numAces = 0;
    for (string card : hand){
        int cardValue = getCardValue(card);
        if (cardValue==11){
            numAces++;
        }
        value += cardValue;
    }
    while (numAces>0 && value>21){
        value -=10;
        numAces--;
    }
    return value;
}


//Inicializar los numeros y colores de la ruleta
vector<string> rouletteNumbers = {"0" , "00", "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8", "9", "10", "11" , "12" , "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26" , "27", "28" , "29" , "30" , "31" , "32", "33", "34", "35", "36"};
vector<string> redNumbers = {"0" , "00" ,"3", "8", "10", "12", "17", "19", "24", "26", "29", "31", "36"};
vector<string> blackNumbers = {"1", "2", "4", "5", "6", "7", "9", "11", "13", "14", "15", "16", "18", "20", "21", "22", "23", "25", "27", "28", "30", "32", "33", "34", "35"};
int girarRuleta() {
    return rand() % 37;
}


//ENTRADA DEL PROGRAMA METODO MAIN
int main (){
    cout << "=================================" << endl;
    cout << "|      WELCOME TO THE CASINO    |" << endl;
    cout << "=================================" << endl;
    bool continuar=true;
    while (continuar==true){
        string option;
        cout << "Do You Want To Play In This Casino?: ";
        cin >> option;
        if (option=="Yes" || option=="yes" || option=="Si" || option=="si" || option=="YES"){
             int age;
             cout << "How Old Are You?: ";
             cin >> age;
             if (age>=18){
                 bool continuacion_inicial=true;
                 while (continuacion_inicial==true){
                 string game;
                 cout << "===============" << endl;
                 cout << "|List Of Game.|" << endl;
                 cout << "===============" << endl;
                 cout << "1. Black/Jack." << endl;
                 cout << "2. Select/The/Random/Number." << endl;
                 cout << "3. Adivine/The/Number/Par/Inpar. " << endl;
                 cout << "4. Roulete/Game." << endl;
                 cout << "0. Exit." << endl;
                 cout << "Select A Option: ";
                 cin >> game;
                 if (game=="1"){
                     bool continuar2=true;
                     while (continuar2==true){
                         string option2;
                         cout << "=======" << endl;
                         cout << "|Rules|" << endl;
                         cout << "=======" << endl;
                         cout << "¡Please Your Atention Here.!" << endl;
                         cout << "1. You compete against the house. The number that is closest to 21 wins and wins double the bet. " << endl;
                         cout << "2. The A's are worth 11 or 1, that depends on how you want to adapt it. The J,K,Q are worth 10. " << endl;
                         cout << "GOOD LUCK" << endl;
                         cout << "Do You Want To Continue Play BlackJack?: ";
                         cin >> option2;
                         if (option2=="Yes" || option2=="yes" || option2=="Si" || option2=="si" || option2=="YES"){
                             srand(time(0)); //Numeros Aleatorios Con La Hora Actual.
                             int coins;
                             coins = 0;
                             ifstream inFile("coinscasino.txt");//Lee Las Monedas Del Jugador.
                             if (inFile.is_open()){
                                 inFile >> coins;
                                 inFile.close(); //De Almacenamiento Que Se Utiliza 
                             }
                             //Nueva Recarga De Monedas
                             int newCoins;
                             string input1;
                             while(true){
                                 cout << "Enter The Amount Of Coins To Recharge: ";
                                 try{
                                     cin >> input1;
                                     newCoins = stoi(input1);
                                     break; //Salir Del Bucle Si Es Exitosa.
                                 }
                                 catch (invalid_argument & e)
                                 {
                                     cout << "Invalid Input. Please Enter A Number. " << endl;
                                     //Continuar Con El Bucle.
                                 }
                             }
                             coins += newCoins;
                             //Guardar Monedas En El Archivo
                             ofstream outFile("coinscasino.txt");
                             if (outFile.is_open()){
                                 outFile << coins;
                                 outFile.close();
                             }
                             while (coins>0){
                                 //Bucle Para El Jugador
                                 cout << "You Have " << coins << " Coins. " << endl;
                                 //Barajar Las Cartas
                                 shuffleDeck(),
                                 //Obtener Apuesta Del Jugador
                                 cout << "Enter Your Bet: ";
                                 int bet;
                                 cin >> bet;
                                 if (bet<=0 || bet>coins){
                                     cout << "Invalid Bet. Please Enter A Bet Between 1 and " << coins << "." << endl;
                                     continue;
                                 }
                                 //Repartir A Cartas
                                 vector<string>playerHand;
                                 vector<string>dealerHand;
                                 playerHand.push_back(deck.back());
                                 deck.pop_back();
                                 dealerHand.push_back(deck.back());
                                 deck.pop_back();
                                 playerHand.push_back(deck.back());
                                 deck.pop_back();
                                 dealerHand.push_back(deck.back());
                                 deck.pop_back();
                                 //Mostrar Cartas
                                 cout << "Your Cards: ";
                                 for (string card:playerHand){
                                     cout << card << " ";
                                 }
                                 cout << "(Total Value: " << calculateHandValue(playerHand) << ")" << endl;
                                 cout << "Dealers Cards: ";
                                 cout << dealerHand[0] << " ";
                                 cout << "Unknown" << " ";
                                 cout << "(Total Value: " << getCardValue(dealerHand[0]) << ")" << endl;
                                 //Turno Del Jugador 
                                 while (true){
                                     cout << "Do You Want To Hit Or Stand: ";
                                     string choice;
                                     cin >> choice;
                                     if (choice=="Hit"){
                                         playerHand.push_back(deck.back());
                                         deck.pop_back();
                                         cout << "Your Cards: ";
                                         for (string card:playerHand){
                                             cout << card << " ";
                                         }
                                         cout << "(Total Value: " << calculateHandValue(playerHand) << ")" << endl;
                                         if (calculateHandValue(playerHand)>21){
                                             cout << "You Bust. Dealer Wins. " << endl;
                                             coins -= bet;
                                             break;
                                         }
                                     }else if (choice=="Stand"){
                                         break;
                                     }else{
                                         cout << "Invalid Choice. Please Enter Either 'Hit' Or 'Stand'. " << endl;
                                     }
                                 }
                                 //Turno Del Dealer
                                 if (calculateHandValue(playerHand)<=21){
                                     cout << "Dealers Cards: ";
                                     for (string card: dealerHand){
                                         cout << card << " ";
                                     }
                                     cout << "(Total Value: " << calculateHandValue(dealerHand) << ") " << endl;
                                     while (calculateHandValue(dealerHand)==17){
                                         dealerHand.push_back(deck.back());
                                         deck.pop_back();
                                         cout << "Dealer Hits. Dealers Cards: ";
                                         for (string card: dealerHand){
                                             cout << card << " ";
                                         }
                                         cout << "(Total Value: " << calculateHandValue(dealerHand) << ") " << endl;
                                     }if (calculateHandValue(dealerHand)>21){
                                         cout << "Dealer Busts. You Win. " << endl;
                                         coins += bet;
                                     }else if (calculateHandValue(dealerHand)>calculateHandValue(playerHand)){
                                         cout << "Dealers Wins. " << endl;
                                         coins -= bet;
                                     }else if (calculateHandValue(dealerHand)<calculateHandValue(playerHand)){
                                         cout << "You Win. " << endl;
                                         coins += bet;
                                     }else {
                                         cout << "Its A Tie. " << endl;
                                     }
                                 }
                                 //Mostrar El Dinero Restante
                                 cout << "You Have " << coins << " Remaining. " << endl;
                                 //Guardar Las Monedas Restantes En El Archivo
                                 ofstream outFile("coinscasino.txt");
                                 if (outFile.is_open()){
                                     outFile << coins;
                                     outFile.close();
                                 }
                                 //Preguntar Si Quieren Seguir Jugando
                                 cout << "Do You Want To Play Again?(Yes/Not): ";
                                 string playAgain;
                                 cin >> playAgain;
                                 if (playAgain!="Yes"){
                                     break;
                                 }
                             }
                             cout << "Thanks For You Playing! " << endl;
                             continuar2=false;
                         }
                         else if (option2=="Not" || option2=="NOT" || option2=="not" || option2=="No" || option2=="no"){
                             cout << "Okey, Good Day." << endl;
                             continuar2=false;
                         }
                     }
                 }

                 else if (game=="2"){
                     cout << "===============" << endl;
                     cout << "|    RULES    |" << endl;
                     cout << "===============" << endl;
                     string option2;
                     cout << "!Please, Your Atention Is Important In This Moment. " << endl;
                     cout << "1. Is Simple, Adivine The Number The Amoun Numbers Is TEN." << endl;
                     cout << "2. If You Guess The Number You Will Win 10 Times Your Bet." << endl;
                     cout << "GOOD LUCK." << endl;
                     cout << "Do You Want To Continue Play TheRandomNumber?: ";
                     cin >> option2;
                     if(option2=="Yes"){
                         bool continuar=true;
                         while(continuar==true){
                             int coins;
                             coins = 0;
                             ifstream inFile("coinscasino.txt");
                             if(inFile.is_open()){
                                 inFile >> coins;
                                 inFile.close();
                             }                             //Almacena Las Monedas
                             string opcionfinal;
                             cout << "Do You Want Continue?(Yes/Not): ";
                             cin >> opcionfinal;
                             if(opcionfinal=="Yes"){
                                 int newCoins;
                                 cout << "Enter The Amount Of Coins To Recharge: ";
                                 cin >> newCoins;
                                 coins+=newCoins;
                                 ofstream outFile("coinscasino.txt");
                                 if (outFile.is_open()){
                                     outFile << coins;
                                     outFile.close();
                                 }
                                 while(coins>0){        //Bucle Del Jugador
                                     cout << "You Have " << coins << " Coins. " << endl;
                                     int bet;
                                     cout << "Enter Your Bet: ";                                 //Solicita La Apuesta
                                     cin >> bet;
                                     if (bet<=1 || bet>coins){
                                         cout << "Invalid Bet. Please Enter A Bet Between 1 and " << coins << " ." << endl;
                                         continue;
                                     }
                                     cout << "Remember The Number Win Exist In The Parameters Of 1 and 10" << endl;
                                     int a;
                                     cout << "Write the number: ";
                                     cin >> a;                                     //Aqui Se Inicializa El Juego
                                     srand(time(NULL));
                                     int computerMove=rand()%10+1;                   //Aleatoridad Numerica
                                     if(computerMove==a){
                                         cout << "You Win! " << endl;
                                         coins+=bet*10;
                                     }
                                     else {
                                         cout << "You Loss. " << endl;
                                         coins-=bet;
                                     }
                                     cout << "You Have " << coins << " Remaining. " << endl;
                                     ofstream outFile("coinscasino.txt");
                                     if(outFile.is_open()){
                                         outFile << coins;
                                         outFile.close();
                                     }
                                     cout << "Do You Wish To Continue?(Yes/Not): ";                      //Aqui Pregunta Si Continuar Jugando O NO
                                     string playagain;
                                     cin >> playagain;
                                     if (playagain!="Yes"){
                                         break;
                                         continuar=false;
                                     }
                                     cout << "Thanks For You Playing. " << endl;
                                     continuar=false;
                                 }
                             }
                             else if (opcionfinal=="Not"){
                                 break;
                                 continuar=false;
                             }
                         }
                     }
                     else if(option=="Not"){
                         cout << "Okey. Bai" << endl;
                     }
                 }

                 else if(game=="3"){
                     cout << "================" << endl;
                     cout << "|     RULES    |" << endl;
                     cout << "================" << endl;
                     string option2;
                     cout << "!Please, Your Atention In This Comment Is More Important That The Game. " << endl;
                     cout << "1. The Game Is About Guessing If The Next Number That The Computer Creates Is Even Or Odd.  " << endl;
                     cout << "NO MORE RULES. GOOD LUCK." << endl;
                     cout << "Do You Want To Continue Play TheAdivineTheNumber Par Or Impar. ";         //Esta Es La Seccion De REGLAS
                     cin >> option2;
                     if (option2=="Yes"){
                         bool continuar=true;
                         while(continuar==true){
                             int coins;
                             coins = 0;
                             ifstream inFile("coinscasino.txt");
                             if(inFile.is_open()){
                                 inFile >> coins;
                                 inFile.close();
                             }
                             string opcionfinal;
                             cout << "Do You Want Continue?(Yes/Not): ";                //Como Anterioirmente Esta Parte Guarda Las Monedas Recargadas
                             cin >> opcionfinal;                                        //Y Pregunta Al Jugador Si Continuar Jugando O NO
                             if(opcionfinal=="Yes"){
                                 int newCoins;
                                 cout << "Enter The Amount Of Coins To Recharge: ";
                                 cin >> newCoins;
                                 coins+=newCoins;
                                 ofstream outFile("coinscasino.txt");
                                 if(outFile.is_open()){
                                     outFile << coins;
                                     outFile.close();
                                 }
                                 while(coins>0){
                                     cout << "You Have " << coins << " Coins." << endl;
                                     int bet;
                                     cout << "Enter Your Bet: ";
                                     cin >> bet;
                                     if(bet<=1 || bet>coins){
                                         cout << "Invalid Bet. Please Enter A Bet Between 1 And " << coins << " ." << endl;
                                         continue;
                                     }
                                     cout << "Remember The Number Win Exist In The Parameters Of 1 And Infinity. " << endl;
                                     cout << "And You Just Have To Find Out If The Next Number Is Even Or Odd. " << endl;
                                     cout << "If You Guess If The Number Is Even Or Odd You Will Win Tree Times The Bet. " << endl;
                                     string a;
                                     cout << "Write The Concept(Par/Impar): ";
                                     cin >> a;
                                     srand(time(NULL));                                //Aleatoridad De Numeros Pares O Impares
                                     int computerMove=rand()%10+100;
                                     if(a=="Par" || a=="par"){
                                         if(computerMove%2==0){
                                             cout << "The Number Is Par! " << endl;
                                             cout << "You Win!" << endl;
                                             coins+=bet*2;
                                         }
                                         else{
                                             cout << "Sorry Your Loss. " << endl;
                                             cout << "The Number Is Impar. " << endl;
                                             coins -=bet;
                                         }
                                         
                                     }
                                     else if(a=="Impar" || a=="impar"){
                                         if(computerMove%2==0){
                                             cout << "Sorry The Number Is Par!" << endl;
                                             cout << "You Loss. " << endl;
                                             coins-=bet;
                                         }
                                         else{
                                             cout << "The Number Is Impar!. Congratulations. " << endl;
                                             cout << "You Win!" << endl;
                                             coins+=bet*2;
                                         } 
                                     }
                                     else {
                                         cout << "Remember The Options(Par Or Impar)" << endl;
                                     }
                                     cout << "You Have " << coins << " Remaining. " << endl;
                                     ofstream outFile("coinscasino.txt");
                                     if(outFile.is_open()){
                                         outFile << coins;
                                         outFile.close();
                                     }
                                     cout << "Do You Wish To Continue?(Yes/Not): ";
                                     string playagain;
                                     cin >> playagain;
                                     if (playagain!="Yes"){                         //Pregunta Al Jugador Si Continuar Apostando O NO
                                         break;
                                         continuar=false;
                                     }
                                     cout << "Thanks For You Playing. " << endl;
                                     continuar=false;
                                 }
                             }
                             else if(opcionfinal=="Not"){                           //Salida Del Juego
                                 break;
                                 continuar=false;
                             }
                         }
                     }
                     else if(option2=="Not"){
                         cout << "Okey. Bai " << endl;
                     }
                 }

                 else if(game=="4"){
                     cout << "================" << endl;
                     cout << "|     RULES    |" << endl;
                     cout << "================" << endl;
                     
                     string option2;
                     cout << "Please your attention here, the rules in this game is very easy." << endl;
                     cout << "Select a number and a color that is coincidence in the rulete and you win" << endl;
                     cout << "Do you want to continue play?(Yes/Not): ";
                     cin >> option2;
                     if(option2=="Yes"){
                            bool continuar_juego = true;

                            while (continuar_juego=true) {
                                int coins; 
                                coins = 0;
                                ifstream inFile("coinscasino.txt");
                                if(inFile.is_open()){
                                    inFile >> coins;
                                    inFile.close();
                                }
                                string opcionfinal;
                                cout << "Do You Want Continue?(Yes/Not): ";
                                cin >> opcionfinal;
                                if(opcionfinal=="Yes"){
                                    int newCoins;
                                    cout << "Enter The Amount Of Coins To Recharge: ";
                                    cin >> newCoins;
                                    coins+=newCoins;
                                    ofstream outFile("coinscasino.txt");
                                    if(outFile.is_open()){
                                        outFile << coins;
                                        outFile.close();
                                    }

                                    while(coins>0){
                                        cout << "You Have " << coins << " Coins. " << endl;
                                        int bet;
                                        cout << "Enter Your Bet: ";
                                        cin >> bet;
                                        if(bet<=1 || bet>coins){
                                            cout << "Invalid Bet. Please Enter A Bet Between 1 and " << coins << " ." << endl;
                                            continue;
                                        }
                                        cout << "Remember that to win the number that falls on the roulette or the color has to fall " << endl;
                                        int numero;
                                        cout << "Write The Number You Want(0-36): " ;
                                        cin >> numero;
                                        if (numero<0 || numero>36){
                                            cout << "Invalid Number. Please Write A Valid Number. " << endl;
                                            break;
                                        }
                                        string color;
                                        cout << "Choose A Color For Bet(Red Or Black): ";
                                        cin >> color;

                                        if(color != "Red" && color!="Black"){
                                            cout << "Invalid Color. Please Remember Red Or Black. " << endl;
                                            break;
                                        }

                                        srand(time(0));
                                        int resultadoRuleta = girarRuleta();
                                         cout << "The Roulette Stopped At Number: " << resultadoRuleta << endl;

                                                                             if (numero == resultadoRuleta) {
                                        if ((color == "Red" && find(redNumbers.begin(), redNumbers.end(), to_string(resultadoRuleta)) != redNumbers.end()) ||
                                            (color == "Black" && find(blackNumbers.begin(), blackNumbers.end(), to_string(resultadoRuleta)) != blackNumbers.end())) {
                                            cout << "You win " << bet * 10 << " coins!" << endl;
                                            coins += bet * 10;
                                        } else {
                                            cout << "You guessed the number but not the color. You win " << bet * 5 << " coins!" << endl;
                                            coins += bet * 5;
                                        }
                                    } else if ((color == "Red" && find(redNumbers.begin(), redNumbers.end(), to_string(resultadoRuleta)) != redNumbers.end()) ||
                                               (color == "Black" && find(blackNumbers.begin(), blackNumbers.end(), to_string(resultadoRuleta)) != blackNumbers.end())) {
                                        cout << "You guessed the color but not the number. You win " << bet * 5 << " coins!" << endl;
                                        coins += bet * 5;
                                    } else {
                                        cout << "Sorry, you didn't guess the number or the color. You lose " << bet << " coins." << endl;
                                        coins -= bet;
                                    }



                                        cout << "You Have " << coins << " Remaining. " << endl;
                                        ofstream outFile("coinscasino.txt");
                                        if(outFile.is_open()){
                                            outFile << coins;
                                            outFile.close();
                                        }
                                        cout << "Do You With To Continue?(Yes/Not): ";
                                        string playagain;
                                        cin >> playagain;
                                        if(playagain!="Yes"){
                                            break;
                                            continuar=false;
                                        }
                                        cout << "Thanks For You Playing. " << endl;
                                        continuar=false;

                                    }

                                }
                                else if(opcionfinal=="Not"){
                                    break;
                                    continuar=false;
                                }
                            }
                     } 
                     else if(option2=="Not")
                     {
                        cout << "Okey. Bai" << endl;
                     }
                 }

                 else if(game=="0"){
                     cout << "Bai.Thanks For You Visiting." << endl;
                     continuacion_inicial=false;
                     continuar=false;
                 }
                 }
                 }
             else if (age<18){
                 cout << "It's Impossible That You Enter The Casino." << endl;
                 continuar=false;
                 }
        }
        else if (option=="Not" || option=="not" || option=="No" || option=="no" || option=="NOT"){
            cout << "Thanks For You Visiting." << endl;
            continuar=false;
        }
    }
    return 0;
}