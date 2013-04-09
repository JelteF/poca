#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "bigInt.h"
#define pause system("PAUSE");
#define nl << '\n' <<
#define nl2 << '\n'
#define space << " " <<
#define getal [0]
#define kleur [1]
using namespace std;
//declare arrays
int deck [52][2]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//kaarten in het deck
    myHand[2][2]={0,0,0,0},//kaarten in mijn hand
    flop[3][2]={0,0,0,0,0,0},//kaarten in de flop
    turn[1][2]={0,0},//kaart in de turn
    river[1][2]={0,0},//kaart in de river
    oppHand[2][2]={0,0,0,0},//kaarten in de tegenstanders hand
    myCards[7][2]={0,0,0,0,0,0,0,0,0,0,0,0,0,0},//kaarten die je kunt gebruiken en is gedefineerd om te testen
    oppCards[7][2]={0,0,0,0,0,0,0,0,0,0,0,0,0,0},//idem tegenstander
    myUsedCards[5][2]={0,0,0,0,0,0,0,0,0,0},//kaarten die gebruikt worden door mij
    oppUsedCards[5][2]={0,0,0,0,0,0,0,0,0,0};//idem tegenstander
//declare integers
int cards=0,
    type=0,
    a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0, i=0, j=0, k=0, m=0, n=0, p=0, q=0, r=0, s=0, t=0, u=0, v=0, w=0, x=0, y=0, z=0,
    myFirstCard=0,
    myFirstCardTemp=0,
    mySecondCard=0,
    mySecondCardTemp=0,
    endCard1=0,
    endCard2=0,
    flopFirstCard=0,
    flopSecondCard=0,
    flopThirdCard=0,
    turnCard=0,
    riverCard=0,
    oppFirstCard=0,
    oppSecondCard=0,
    checkStraightFlush=0,
    setCards=0,
    readCards=0,
    flopWins=0,
    flopLosses=0,
    turnWins=0,
    turnLosses=0,
    riverWins=0,
    riverLosses=0,
    winsInt=0,
    lossesInt=0,
    totalMatches=0,
    line=0,
    winner=0,//of iemand de combi heeft 0=niemand 1=ik 2=tegenstander 3=beide
    temp=0;
double winChance=0,
    loseChance=0,
    tieChance=0,
    winLoseRatio;
string combi="",
    myHandFilename="",
    flopFilename="",
    turnFilename="",
    riverFilename="",
    readFilename="",
    myHandNumber="",
    flopNumber="",
    turnNumber="",
    file="",
    winsStr="",
    lossesStr="",
    lineStr="";
bool bool1=true,
    stop=false,
    usedDeck [52]=//welke kaarten al gepakt zijn
{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

//copy rijen van een array in een andere array
void copyArray(int source[][2], int goal[][2], int sourceRow, int goalRow, int rows)/*het aantal rijen, dat in "rows" wordt aangegeven,
                                                                                    wordt vanaf de sourcerow in source naar de goalrow in goal gekopieerd*/
{
     for(h=0;h<rows;h++)
     {
        for(m=0; m<=1; m++)
        goal[h+goalRow][m]=source[h+sourceRow][m];
     }
}
//print een array
void printArray(int print[][2], int rows)//print een bepaald aantal van de rijen van een array in de console
{
    for(i=0;i<rows;i++)
    {
        cout << print[i]getal space print[i]kleur nl2;
    }
    cout nl2;
}
//sorteer een array
void cardsSort(int cards[][2])
{
     bool flag=true;    // set flag to 1 to start first pass
     int temp;        // holding variable
     for(i = 1; (i <= 7) && flag; i++)
     {
          flag = false;
          for (j=0; j < (6); j++)
         {
               if (cards[j+1][0] > cards[j][0])      // ascending order simply changes to <
              {
                    temp = cards[j][0];         // swap elements
                    cards[j][0] = cards[j+1][0];
                    cards[j+1][0] = temp;
                    temp = cards[j][1];         // swap elements
                    cards[j][1] = cards[j+1][1];
                    cards[j+1][1] = temp;
                    flag = true;              // indicates that a swap occurred.
               }
          }
     }
     return;   //arrays are passed to functions by address; nothing is returned
}

//convert functions
string intToStr(int number)//convert een integer naar een string
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
int strToInt(string strConvert) //convert een string naar een integer
{
  int intReturn;
  intReturn = atoi(strConvert.c_str());
  return(intReturn);
}
string createFilename(string begin)//de standaard manier die door ons gebruikt wordt om een bestandsnaam te maken
{
    file=begin;
    file+=" ";
    file+=intToStr(myFirstCard);
    file+=" ";
    file+=intToStr(mySecondCard);
    file+=".txt";
    return file;
}

int choose (int boven, int onder)//functie om de x boven y uit te rekenen
{
    int result=0;
    string hold;
    BigInt::Rossi resultBig(0);
    BigInt::Rossi onderBig(1);
    BigInt::Rossi bovenBig(1);
    BigInt::Rossi bovenMinusOnderBig(1);

    for (i = 2; i <= onder; i++)
    {
        BigInt::Rossi factor1(i);
        onderBig = onderBig * factor1;
    }
    for (i = 2; i <= boven; i++)
    {
        BigInt::Rossi factor2(i);
        bovenBig = bovenBig * factor2;
    }
    for (i = 2; i <= boven-onder; i++)
    {
        BigInt::Rossi factor3(i);
        bovenMinusOnderBig = bovenMinusOnderBig * factor3;
    }
    resultBig = bovenBig/(onderBig * bovenMinusOnderBig);
    hold= resultBig.toStrDec();
    result=strToInt(hold);
    return result;
}

//deal cards functions
int deckCheck(int check)//check of de gekozen kaart al uit het deck is en zo ja kijk dan voor eentje hoger.
{
    while (usedDeck[check])
    {
         check++;
    }
    return check;
}
void deal(int deal[][2], int handCard, int deckCard)//kopieer de kaart uit het deck naar de plek in de hand waar hij hoort en zet hem als gebruikt in usedDeck
{
     copyArray(deck, deal, deckCard, handCard, 1);
     usedDeck[deckCard]=true;
}
void dealAllCards()//deel alle kaarten
{
    deal(myHand, 0, myFirstCard);//stopt de eerst uitgekozen kaart van het deck in je hand
    deal(myHand, 1, mySecondCard);
    deal(flop, 0, flopFirstCard);
    deal(flop, 1, flopSecondCard);
    deal(flop, 2, flopThirdCard);
    deal(turn, 0, turnCard);
    deal(river, 0, riverCard);
/*  deal(oppHand, 0, oppFirstCard);
    deal(oppHand, 1, oppSecondCard);*/
}
void addToCards(int cards[][2], int hand[][2])//myCards of oppCards definieren, welke het is moet ingevuld worden bij cards
{
     copyArray(hand, cards, 0, 0, 2);//copy de handkaarten in cards
     copyArray(flop, cards, 0, 2, 3);//idem flop
     copyArray(turn, cards, 0, 5, 1);//idem turn
     copyArray(river, cards, 0, 6, 1);//idem river
}

int checkLower(int card, int cardsBefore)//checkt hoeveel kaarten die eerder getrokken zijn een lager nummer hebben en trekt dat aantal van het nummer van de kaart af
{
    int temp=card;
    for(i=0;i<cardsBefore;i++)
    {
        if(i==0 && myFirstCard<card)
            temp--;
        if(i==1 && mySecondCard<card)
            temp--;
        if(i==2 && flopFirstCard<card)
            temp--;
        if(i==3 && flopSecondCard<card)
            temp--;
        if(i==4 && flopThirdCard<card)
            temp--;
        if(i==5 && turnCard<card)
            temp--;
    }
    return temp;
}

//functies om op verschillende alle combinaties te controleren
void four(int usedCards[][2], int cards[][2], int x)//functie om voor four of a kind te controleren
{
   for(i=0;i<4;i++)
    {
        bool flag=false;
        if(cards[i]getal==cards[i+1]getal==cards[i+2]getal==cards[i+3]getal)//kijk of de kaarten hetzelfde getal hebben, dus een four of a kind
        {

            copyArray(cards, usedCards, i, 0, 4);//voegt andere Four of a Kind toe aan gebruikte kaarten
            u=0;
            winner+=x;//er is een four of a kind voor deze speler
            //combi="Four of a Kind";
            if(i==0)//check of de hoogste kaart bij de four of a kind hoort
            {
                u=4;//sla de kaarten van de four of a kind over
            }
            copyArray(cards, usedCards, u, 5, 1);//voeg de hoogste kaart op de kaarten van de four of a kind na toe aan de gebruikte kaarten
        }
    }
}
void fullHouse(int usedCards[][2], int cards[][2], int x)
{
    bool flag=false;
    for(i=0;i<5;i++)//zoek een Three of a Kind in je hand
    {
        if(cards[i]getal==cards[i+1]getal==cards[i+2]getal)//kijk of de kaarten hetzelfde getal hebben
        {
           flag=true;//er is een Three of a Kind
           copyArray(cards, usedCards, i, 0, 3);//voegt de Three of a Kind toe aan gebruikte kaarten
        }
        if(flag)//Als er een Three of a Kind is
        {
            for(r=0;r<6;r++)//zoek naar een Pair
            {
               if (r==i)//niet degene in de Three of a Kind
               {
                    r=i+3;//sla Three of a Kind over
                    if(r>=6)//checken dat er nog genoeg kaarten over zijn
                        break;
               }
               if(cards[r]getal==cards[r+1]getal)//kijk of de kaarten hetzelfde getal hebben
               {
                    winner+=x;//er is een Pair
                    //combi="Full House";
                    copyArray(cards, usedCards, r, 3, 2);//voegt Pair toe aan gebruikte kaarten
                    break;
               }
            }
            break;
        }

    }
}
void flush(int usedCards[][2], int cards[][2], int x)
{
    for(i=0;i<=2;i++)
    {
        n=i;
        j=0;
        copyArray(cards, usedCards, i, 0, 1);//voegt kaart i uit cards toe aan usedCards
        for(k=1;k<5;k++)
        {
             if(cards[i]kleur==cards[n+k]kleur)//kijk of de kaarten dezelfde kleur hebben
             {
                j++;
                copyArray(cards, usedCards, n+k, k, 1);//voegt andere gebruikte kaarten toe
             }
             else if(n<3)
             {
                  k--;//moet hij 1 keer meer door deze for loop
                  n++;//maar hij moet wel naar de volgende kaart
             }
             else
             break;
        }
        if(j==4)//vijf kaarten van dezelfde kleur
        {
            winner+=x;//er is een flush
            //combi="Flush";
            break;
        }
    }
}
void straight(int usedCards[][2], int cards[][2], int y, int aantalKaarten)//aantal kaarten is een extra waarde om deze functie ook te kunnen gebruiken voor straightflush
{
    for(r=0;r<aantalKaarten-3;r++)
    {
        s=r;
        p=0;
        copyArray(cards, usedCards, r, 0, 1);//voegt kaart i uit cards toe aan usedCards
        for (t=1;t<5;t++)
        {
            if(cards[r][0]==5)
            {
                for(u=1;u<5;u++)
                {
                    if(cards[s+u][0]==2 && cards[0][0]==14)
                    {
                        p+=2;
                        copyArray(cards, usedCards, s+u, 3, 1);
                        copyArray(cards, usedCards, 0, 4, 1);
                    }

                    else if(cards[s+u-1][0]-1==cards[s+u][0])//check of de kaart 1 kaart hoger is dan degene die er direct onder staat in cards
                    {
                        p++;
                        copyArray(cards, usedCards, s+u, u, 1);//voegt andere gebruikte kaarten toe
                    }
                    else if(cards[s+u-1][0]==cards[s+u][0] && s<aantalKaarten-2)
                    {
                        u--;
                        s++;
                    }
                    else
                        break;
                }
                break;
            }
            else if(cards[s+t-1][0]-1==cards[s+t][0])//check of de kaart 1 kaart hoger is dan degene die er direct onder staat in cards
            {
                p++;
                copyArray(cards, usedCards, s+t, t, 1);//voegt andere gebruikte kaarten toe
            }
            else if(cards[s+t-1][0]==cards[s+t][0] && s<aantalKaarten-3)//als het twee dezelfde kaarten zijn en er nog genoeg kaarten over zijn
            {
                t--;//moet hij 1 keer meer door deze for loop
                s++;//maar hij moet wel naar de volgende kaart
            }
            else
            break;
        }
        if(p==4)//vijf opeenvolgende kaarten
        {
            winner+=y;//er is een straat
            //combi="Straight";
            //checkStraightFlush=1;
            break;
        }

    }
}
void straightFlush(int usedCards[][2], int cards[][2], int x)
{
    int usedFlushCards[7][2];
    for(i=0;i<3;i++)
    {

        n=i;
        j=0;
        copyArray(cards, usedFlushCards, i, 0, 1);//voegt kaart i uit cards toe aan usedCards
        for(k=1;k<7-n;k++)
        {
             if(cards[i]kleur==cards[n+k]kleur)//kijk of de kaarten dezelfde kleur hebben
             {
                j++;
                copyArray(cards, usedFlushCards, n+k, k, 1);//voeg de andere kaarten van de flush toe aan de gebruikte kaarten
             }
             else if(n<3)
             {
                  k--;//moet hij 1 keer meer door deze for loop
                  n++;//maar hij moet wel naar de volgende kaart
             }
             else
             break;
        }
        if(j>=4)//vijf kaarten van dezelfde kleur
        {
            straight(usedCards, usedFlushCards, x, j);//check of er een straightflush in de kaarten zit
            //if (checkStraightFlush==1)
                //combi="Straightflush";
            break;
        }
    }
}
void three(int usedCards[][2], int cards[][2], int x)
{
    bool flag=false;
    for(i=0;i<5;i++)
    {
             if(cards[i]getal==cards[i+1]getal==cards[i+2]getal)//kijk of de kaarten hetzelfde getal hebben
             {
                flag=true;//een three of a kind
                copyArray(cards, usedCards, i, 0, 3);//voegt de kaarten van de three of a kind toe aan gebruikte kaarten
             }
        if(flag)//een three of a kind
        {
            winner+=x;//er is een Thre of a kind
            //combi="Three of a Kind";
            u=0;
            for(p=0;p<2;p++)//zoek de twee hoogste overgebleven kaarten
            {
                 if(u==i)//je kunt de kaarten van de Three of a Kind niet nogmaals toevoegen aan de hand
                 {
                      u=i+3;//sla de kaarten van de Three of a Kind over
                 }
                 copyArray(cards, usedCards, u, 3+p, 1);//sla de hoogste twee overgebleven kaarten op in de gebruikte kaarten
                 u++;
            }
            break;
        }
    }
}
void twoPair(int usedCards[][2], int cards[][2], int x)
{
    bool flag=false;
    bool flag2=false;
    for(i=0;i<4;i++)//als de eerste pair verder zit dan kaart 4 en 5, kan er geen ander pair zijn
    {
        if(cards[i]getal==cards[i+1]getal)//kijk of de kaarten hetzelfde getal hebben
        {
            flag=true;//er is een paar
            copyArray(cards, usedCards, i, 0, 2);//voegt de kaarten van de eerste Pair to aan gebruikte kaarten
        }
        if(flag)
        {
            for(r=i+2;r<6;r++)
            {
               if(cards[r]getal==cards[r+1]getal)//kijk of de kaarten hetzelfde getal hebben
               {
                   winner+=x;//er is een paar
                   //combi="Two Pair";
                   copyArray(cards, usedCards, r, 2, 2);//voegt andere gebruikte kaarten toe
                   p=0;
                   if(p==i)//je kunt de kaarten van de pair niet nogmaals toevoegen aan de hand
                   {
                        p=i+2;//sla de kaarten van de pair over
                        if(p==r)//sla de kaarten van de tweede pair over
                        {
                            p=r+2;
                        }
                   }
                        copyArray(cards, usedCards, p, 4, 1);//voeg de hoogste kaart op de kaarten van de pairs na toe
                }
                break;
            }
            break;
        }
    }

}
void onePair(int usedCards[][2], int cards[][2], int x)
{
    bool flag=false;
    for(i=0;i<6;i++)
    {
        if(cards[i]getal==cards[i+1]getal)//kijk of de kaarten hetzelfde getal hebben
        {
            flag=true;//er is een pair
            copyArray(cards, usedCards, i, 0, 2);//voegt andere gebruikte kaarten toe
        }
        if(flag)//een pair
        {
            winner+=x;//er is een pair
            //combi="One Pair";
            u=0;
            for(p=0;p<3;p++)//ga de kaarten af in je hand en op tafel
            {
                 if(u==i)//je kunt de kaarten van de pair niet nogmaals toevoegen aan de hand
                 {
                      u=i+2;//sla de kaarten van de pair over
                 }
                 copyArray(cards, usedCards, u, 2+p, 1);
                 u++;
            }
            break;
        }
    }
}
void highCard(int usedCards[][2], int cards[][2])
{
     copyArray(cards, usedCards, 0, 0, 5);//voegt de hoogste 5 kaarten van cards toe aan usedCards
}

//check who wins function
void checkWinner()
{
    winner=0;
    for(a=0; a<=8; a++)
    {
        switch(a)
        {
        case 0://Begin met straight flush checken
            straightFlush(myUsedCards, myCards, 1);//Voor de speler zijn kaarten
            straightFlush(oppUsedCards, oppCards, 2);//Voor de tegenstander zijn kaarten
            //checkStraightFlush=0;
            break;//Anders loopt hij alle andere mogelijkheden gelijk ook af
        case 1://Idem voor de rest van de kaarten
            four(myUsedCards, myCards, 1);
            four(oppUsedCards, oppCards, 2);
            break;
        case 2:
            fullHouse(myUsedCards, myCards, 1);
            fullHouse(oppUsedCards, oppCards, 2);
            break;
        case 3:
            flush(myUsedCards, myCards, 1);
            flush(oppUsedCards, oppCards, 2);
            break;
        case 4:
            straight(myUsedCards, myCards, 1, 6);
            straight(oppUsedCards, oppCards, 2, 6);
            checkStraightFlush=0;
            break;
        case 5:
            three(myUsedCards, myCards, 1);
            three(oppUsedCards, oppCards, 2);
            break;
        case 6:
            twoPair(myUsedCards, myCards, 1);
            twoPair(oppUsedCards, oppCards, 2);
            break;
        case 7:
            onePair(myUsedCards, myCards, 1);
            onePair(oppUsedCards, oppCards, 2);
            break;
        case 8:
            highCard(myUsedCards, myCards);
            highCard(oppUsedCards, oppCards);
            winner=3;
            //combi="High Card";
            break;
        }
        if(winner!=0)
            break;//Als er iemand een combinatie heeft stop dan met de loop

    }
    if (winner==3)//Beide spelers dezelfde combinatie
    {
        for(i=0;i<5;i++)//Degene bij wie het eerst een hogere kaart wordt gevonden wint.
                        //Dit is het geval doordat de kaarten eerder zo gesorteerd zijn dat de belangrijkste kaarten bovenaan staan
        {
            if(myUsedCards[i][0]>oppUsedCards[i][0])//Check of de speler een hogere kaart heeft
            {
                winner=1;
                break;
            }
            if(myUsedCards[i][0]<oppUsedCards[i][0])//Check of de tegenstandere een hogere kaart heeft
            {
                winner=2;
                break;
            }
        }

    }
}
void printWinChance(int wins, int losses)
{
    winChance=((double) wins/(totalMatches))*100;
    loseChance=((double) losses/(totalMatches))*100;
    tieChance=((double) (totalMatches-wins-losses)/(totalMatches))*100;
    if(losses==0)
        winLoseRatio=1;
    else
        winLoseRatio=(double) wins/losses;
    cout << "Er is " << wins << " keer gewonnen" nl
        "Er is " << losses << " keer verloren" nl
        "Er is " << winChance << "% kans om te winnen" nl
        "Er is " << loseChance << "% kans om te verliezen"nl
        "Er is " << tieChance << "% kans om te gelijk te spelen" nl
        "Er is een Win/Lose ratio van " << winLoseRatio nl2;
}

//main functions
void createDeck ()
{
    cards=1;
    type=1;
    for(i=0;i<52;i++)
    {
          if (cards!=14)
          {
              cards++;
          }
          else
          {
              type++;
              cards=2;
          }
          deck [i][0]=cards;
          deck [i][1]=type;
          usedDeck[i]=0;
          cout << i << ":  " << deck [i][0] space deck [i][1] nl2;
    }
}
void manual ()//calculate winchance for certain cards
{
    cout << "Kies getal voor jouw eerste kaart:"nl2;//vraag wat de kaarten zijn
    cin >> myFirstCard;
    cout << "Kies getal voor jouw tweede kaart:"nl2;
    cin >> mySecondCard;
    cout << "Kies getal voor eerste flop kaart:"nl2;
    cin >> flopFirstCard;
    cout << "Kies getal voor tweede flop kaart:"nl2;
    cin >> flopSecondCard;
    cout << "Kies getal voor derde flop kaart:"nl2;
    cin >> flopThirdCard;
    cout << "Kies getal voor turn kaart:"nl2;
    cin >> turnCard;
    cout << "Kies getal voor river kaart:"nl2;
    cin >> riverCard;
/*  cout << "Kies getal voor tegenstanders eerste kaart:"nl2;
    cin >> oppFirstCard;
    cout << "Kies getal voor tegenstanders tweede kaart:"nl2;
    cin >> oppSecondCard;*/
    dealAllCards();

    for(oppFirstCard=0;oppFirstCard<52;oppFirstCard++)//kies eerste kaart van de tegenstander
    {
        oppFirstCard=deckCheck(oppFirstCard);
        if (oppFirstCard>51)
        {
            break;
        }
        deal(oppHand, 0, oppFirstCard);
        for(oppSecondCard=oppFirstCard+1;oppSecondCard<52;oppSecondCard++)//begin bij 1 kaart verder dan de eerste kaart van de tegenstander
        {
            oppSecondCard=deckCheck(oppSecondCard);
            if (oppSecondCard>51)
            {
                break;
            }
            deal(oppHand, 1, oppSecondCard);
            addToCards(myCards, myHand);//stop de kaarten die de speler mag gebruiken in array myCards
            addToCards(oppCards, oppHand);//stop de kaarten de de tegenstander mag gebruiken in array oppCards
            cardsSort(myCards);//sorteer myCards
            cardsSort(oppCards);//sorteer oppCards

            checkWinner();//check wie er gewonnen heeft

            if (winner==1)//voeg een win toe
                riverWins++;
            if (winner==2)//voeg een loss toe
                riverLosses++;
            usedDeck[oppSecondCard]=false;//stop de tweede kaart van de tegenstander terug in het deck
        }
        usedDeck[oppFirstCard]=false;//stop de eerste kaart van de tegenstander terug in het deck
    }
    totalMatches=990;
    printWinChance(riverWins, riverLosses);
}
void read ()
{
    while (true)
    {
        cout << "0 for my hand, 1 for flop, 2 for turn, 3 for river and 4 to quit"nl2;
        cin >> readCards;
        if (readCards==4)
            break;
        cout << "Kies getal voor jouw eerste kaart:"nl2;
        cin >> myFirstCard;
        cout << "Kies getal voor jouw tweede kaart:"nl2;
        cin >> mySecondCard;
        if (readCards==0)
        {
            readFilename=createFilename("my hand");
            ifstream readFile (readFilename);
            if (readFile.is_open())
            {
                getline(readFile, winsStr);
                getline(readFile, lossesStr);
                //er zijn geen ints van de strings te maken, want ze zijn te lang
                //dus ga ik dingen doen met de bigInt class
                int lengthWins=winsStr.size(), lengthLosses=lossesStr.size(),
                    winsPow=pow(10.0,1+lengthWins/2), lossesPow=pow(10.0,1+lengthLosses/2),
                    signifigance=1000000;
                string wins1stHalfStr="", wins2ndHalfStr="", losses1stHalfStr="", losses2ndHalfStr="";
                for(i=0;i<lengthWins/2;i++)
                    wins1stHalfStr+=winsStr[i];
                for (i=lengthWins/2; i<lengthWins;i++)
                    wins2ndHalfStr+=winsStr[i];
                for(i=0;i<lengthLosses/2;i++)
                    losses1stHalfStr+=lossesStr[i];
                for (i=lengthLosses/2; i<lengthLosses;i++)
                    losses2ndHalfStr+=lossesStr[i];
                BigInt::Rossi wins1stHalfBig(strToInt(wins1stHalfStr));
                BigInt::Rossi wins2ndHalfBig(strToInt(wins2ndHalfStr));
                BigInt::Rossi losses1stHalfBig(strToInt(losses1stHalfStr));
                BigInt::Rossi losses2ndHalfBig(strToInt(losses2ndHalfStr));
                BigInt::Rossi winsPowBig(winsPow);
                BigInt::Rossi lossesPowBig(lossesPow);
                BigInt::Rossi winsBig(0);
                BigInt::Rossi lossesBig(0);
                BigInt::Rossi totalMatches(41951448);
                BigInt::Rossi totalMatchesFactor(1000);
                BigInt::Rossi decimalFactor(signifigance);
                BigInt::Rossi winChanceBig(0);
                BigInt::Rossi loseChanceBig(0);
                BigInt::Rossi tieChanceBig(0);
                totalMatches = totalMatches*totalMatchesFactor;
                winsBig = wins1stHalfBig*winsPowBig + wins2ndHalfBig;
                lossesBig = losses1stHalfBig*lossesPowBig + losses2ndHalfBig;
                winChanceBig=(winsBig*decimalFactor)/totalMatches;
                loseChanceBig=(lossesBig*decimalFactor)/totalMatches;
                tieChanceBig=((totalMatches-lossesBig-winsBig)*decimalFactor)/totalMatches;
                winChance=((double)winChanceBig.toUlong())/(signifigance/100);
                loseChance=((double)loseChanceBig.toUlong())/(signifigance/100);
                tieChance=((double)tieChanceBig.toUlong())/(signifigance/100);
                if(lossesStr=="0")
                    winLoseRatio=1;
                else
                {
                    BigInt::Rossi winLoseBig(0);
                    winLoseBig= (winsBig*decimalFactor)/lossesBig;
                    winLoseRatio= ((double) winLoseBig.toUlong())/signifigance;
                }
                cout << "Er is " << winsBig.toStrDec() << " keer gewonnen" nl
                    "Er is " << lossesBig.toStrDec() << " keer verloren" nl
                    "Er is " << winChance << "% kans om te winnen" nl
                    "Er is " << loseChance << "% kans om te verliezen"nl
                    "Er is " << tieChance << "% kans om te gelijk te spelen" nl
                    "Er is een Win/Lose ratio van " << winLoseRatio nl2;
            }
            else cout << "Unable to open file" nl2;
        }
        else
        {
            cout << "Kies getal voor eerste flop kaart:"nl2;
            cin >> flopFirstCard;
            cout << "Kies getal voor tweede flop kaart:"nl2;
            cin >> flopSecondCard;
            cout << "Kies getal voor derde flop kaart:"nl2;
            cin >> flopThirdCard;
            if(readCards==1)
            {
                int card1, card2, card3;
                card1=checkLower(flopFirstCard, 2);
                card2=checkLower(flopSecondCard, 3);
                card3=checkLower(flopThirdCard, 4);
                line=0;
                for (n=0; n<card1; n++)
                {
                    line+=choose(49-n, 2);
                }
                for (n=card1; n<card2; n++)
                {
                    line+=48-n;
                }
                line+=card3-card2;
                readFilename=createFilename("flop");
                ifstream readFile (readFilename);
                if (readFile.is_open())
                {
                    for(k=0; k<line*2; k++)
                        getline(readFile, lineStr);
                    getline(readFile, winsStr);
                    getline(readFile, lossesStr);
                    winsInt=strToInt(winsStr);
                    lossesInt=strToInt(lossesStr);
                    totalMatches=2140380;//ander aantal matches maken
                    printWinChance(winsInt, lossesInt);
                }
                else cout << "Unable to open file" nl2;
            }
            else
            {
                cout << "Kies getal voor turn kaart:"nl2;
                cin >> turnCard;
                if(readCards==2)
                {
                    int card1, card2, card3, card4;
                    card1=checkLower(flopFirstCard, 2);
                    card2=checkLower(flopSecondCard, 3);
                    card3=checkLower(flopThirdCard, 4);
                    card4=checkLower(turnCard, 5);
                    line=0;
                    for (n=0; n<card1; n++)
                    {
                        line+=choose(49-n, 2);
                    }
                    for (n=card1; n<card2; n++)
                    {
                        line+=48-n;
                    }
                    line+=card3-card2;
                    line*=47;
                    line+=card4;
                    readFilename=createFilename("turn");
                    ifstream readFile (readFilename);
                    if (readFile.is_open())
                    {
                        for(k=0; k<line*2; k++)
                            getline(readFile, lineStr);
                        getline(readFile, winsStr);
                        getline(readFile, lossesStr);
                        winsInt=strToInt(winsStr);
                        lossesInt=strToInt(lossesStr);
                        totalMatches=45540;//ander aantal matches maken
                        printWinChance(winsInt, lossesInt);
                    }
                    else cout << "Unable to open file" nl2;
                }
                else if(readCards==3)
                {
                    cout << "Kies getal voor river kaart:"nl2;
                    cin >> riverCard;
                    int card1, card2, card3, card4, card5;
                    card1=checkLower(flopFirstCard, 2);
                    card2=checkLower(flopSecondCard, 3);
                    card3=checkLower(flopThirdCard, 4);
                    card4=checkLower(turnCard, 5);
                    card5=checkLower(riverCard, 6);
                    line=0;
                    for (n=0; n<card1; n++)
                    {
                        line+=choose(49-n, 2);
                    }
                    for (n=card1; n<card2; n++)
                    {
                        line+=48-n;
                    }
                    line+=card3-card2;
                    line*=47;
                    line+=card4;
                    line*=46;
                    line+=card5;
                    readFilename=createFilename("river");
                    ifstream readFile (readFilename);
                    if (readFile.is_open())
                    {
                        for(k=0; k<line*2; k++)
                            getline(readFile, lineStr);
                        getline(readFile, winsStr);
                        getline(readFile, lossesStr);
                        winsInt=strToInt(winsStr);
                        lossesInt=strToInt(lossesStr);
                        totalMatches=990;//ander aantal matches maken
                        printWinChance(winsInt, lossesInt);
                    }
                    else cout << "Unable to open file" nl2;
                }
            }
        }
    }
}
void autoWrite()
{
        cout << "Kies beginkaart voor de eerste handkaart:"nl2;
        cin >> myFirstCardTemp;
        cout << "Kies beginkaart voor de tweede handkaart:"nl2;
        cin >> mySecondCardTemp;
        cout << "Kies eindkaart voor de eerste handkaart:"nl2;
        cin >> endCard1;
        cout << "Kies eindkaart voor de tweede handkaart:"nl2;
        cin >> endCard2;
        for(myFirstCard=0;myFirstCard<13;myFirstCard++)//deel eerste handkaart
        {
            if (bool1)//neem de gekozen eerste handkaart
                myFirstCard=myFirstCardTemp;
            deal(myHand, 0, myFirstCard);
            for(mySecondCard=myFirstCard+1;mySecondCard<26;mySecondCard++)//beginnen bij 1 een kaart verder dan de eerste handkaart en doorgaan tot de aas van de andere kleur
            {
                for(mySecondCard=mySecondCard; mySecondCard>12 && mySecondCard<13+myFirstCard;mySecondCard++){}//zorgen dat er geen gelijkwaardige combinaties ontstaan
                if (bool1)//neem de gekozen tweede handkaart
                {
                    mySecondCard=mySecondCardTemp;
                    bool1=false;
                }
                if ((myFirstCard==endCard1 && mySecondCard>=endCard2)||myFirstCard>endCard1)//stop als het programma bij of voorbij de eindkaarten is
                {
                    stop=true;
                    break;
                }
                deal(myHand, 1, mySecondCard);
                myHandFilename=createFilename("my hand");//maak de bestandsnaam voor myHand bestand
                ofstream myHandFile (myHandFilename, ios::out | ios::app);//maak de filestream en open het bestand voor output aan het einde van de file
                flopFilename=createFilename("flop");//idem rest van de files
                ofstream flopFile (flopFilename, ios::out | ios::app);
                turnFilename=createFilename("turn");
                ofstream turnFile (turnFilename, ios::out | ios::app);
                riverFilename=createFilename("river");
                ofstream riverFile (riverFilename, ios::out | ios::app);
                BigInt::Rossi myHandWins(0);
                BigInt::Rossi myHandLosses(0);
                //deel de rest van de kaarten
                for(flopFirstCard=0;flopFirstCard<50;flopFirstCard++)//loop alle eerste flopkaarten af
                {
                    flopFirstCard=deckCheck(flopFirstCard);
                    if (flopFirstCard>49)//als er geen mogelijke kaarten meer in het deck zitten neem dan een nieuwe handkaart
                    {
                         break;
                    }
                    deal(flop, 0, flopFirstCard);//deel de eerste flopkaart
                    for(flopSecondCard=flopFirstCard+1;flopSecondCard<51;flopSecondCard++)//beginnen bij 1 kaart verder dan de eerste flopkaart
                    {
                         flopSecondCard=deckCheck(flopSecondCard);
                         if (flopSecondCard>50)
                         {
                               break;
                         }
                         deal(flop, 1, flopSecondCard);
                         for(flopThirdCard=flopSecondCard+1;flopThirdCard<52;flopThirdCard++)//beginnen bij 1 kaart verder dan de tweede flopkaart
                         {
                              flopThirdCard=deckCheck(flopThirdCard);
                              if (flopThirdCard>51)
                              {
                                   break;
                              }
                              deal(flop, 2, flopThirdCard);


                              for(turnCard=0;turnCard<52;turnCard++)//kies turnkaart
                              {

                                   turnCard=deckCheck(turnCard);
                                   if (turnCard>51)
                                   {
                                         break;
                                   }
                                   deal(turn, 0, turnCard);
                                   for(riverCard=0;riverCard<52;riverCard++)//kies riverkaart
                                   {

                                        riverCard=deckCheck(riverCard);
                                        if (riverCard>51)
                                        {
                                            break;
                                        }
                                        deal(river, 0, riverCard);
                                        addToCards(myCards, myHand);
                                        cardsSort(myCards);//sorteer myCards
                                        for(oppFirstCard=0;oppFirstCard<51;oppFirstCard++)//kies eerste kaart van de tegenstander
                                        {
                                             oppFirstCard=deckCheck(oppFirstCard);
                                             if (oppFirstCard>50)
                                             {
                                                  break;
                                             }
                                             deal(oppHand, 0, oppFirstCard);
                                             for(oppSecondCard=oppFirstCard+1;oppSecondCard<52;oppSecondCard++)//begin bij 1 kaart verder dan de eerste kaart van de tegenstander
                                             {
                                                  oppSecondCard=deckCheck(oppSecondCard);
                                                  if (oppSecondCard>51)
                                                  {
                                                       break;
                                                  }
                                                  deal(oppHand, 1, oppSecondCard);
                                                  addToCards(oppCards, oppHand);
                                                  cardsSort(oppCards);//sorteer oppCards

                                                  checkWinner();//check wie er gewonnen heeft

                                                  if (winner==1)//voeg een win toe
                                                      riverWins++;
                                                  if (winner==2)//voeg een loss toe
                                                      riverLosses++;
                                                  usedDeck[oppSecondCard]=false;//stop de tweede kaart van de tegenstander terug in het deck
                                             }
                                             usedDeck[oppFirstCard]=false;//stop de eerste kaart van de tegenstander terug in het deck
                                        }
                                        turnWins+=riverWins;//voeg de wins van die met deze river zijn gehaald toe aan de wins die met deze turns zijn gehaald
                                        turnLosses+=riverLosses;//idem losses
                                        riverFile << riverWins nl riverLosses nl2;//sla de wins en losses van deze river op
                                        riverWins=0;//reset wins
                                        riverLosses=0;//reset losses
                                        usedDeck[riverCard]=false;
                                   }
                                   flopWins+=turnWins;//idem hierboven
                                   flopLosses+=turnLosses;
                                   turnFile << turnWins nl turnLosses nl2;//sla wins en losses van deze turn op
                                   turnWins=0;
                                   turnLosses=0;
                                   usedDeck[turnCard]=false;
                              }
                              BigInt::Rossi flopWinsBig(flopWins);
                              BigInt::Rossi flopLossesBig(flopLosses);
                              myHandWins = myHandWins + flopWinsBig;//idem hierboven
                              myHandLosses = myHandLosses + flopLossesBig;
                              flopFile << flopWins nl flopLosses nl2;//sla wins en losses van deze flop op
                              flopWins=0;
                              flopLosses=0;
                              usedDeck[flopThirdCard]=false;
                         }
                         usedDeck[flopSecondCard]=false;
                    }
                    usedDeck[flopFirstCard]=false;
                }
                myHandFile << myHandWins.toStrDec()  nl myHandLosses.toStrDec() nl2;//sla wins en losses van deze hand op

                myHandFile.close();//sluit alle files
                flopFile.close();
                turnFile.close();
                riverFile.close();
                cout << "Files voor " << intToStr(myFirstCard) << " " << intToStr(mySecondCard) << " gedaan" nl2;//print dat hij al de files voor deze combinatie handkaarten gedaan heeft
                usedDeck[mySecondCard]=false;
            }
            if (stop)
                break;
            usedDeck[myFirstCard]=false;
        }
}

int main()
{
    createDeck();

    cout nl2;
    cout << "0 for auto, 1 for manual and 2 for reading"nl2;
    cin >> setCards;

    if (setCards==1)
    {
        manual();
        pause
    }
    else if(setCards==2)
    {
        read();
    }
    else if(setCards==0)
    {
        autoWrite();
        cout << "Nu is het eindelijk klaar!!!!!!!!";
        pause
    }
    return 0;
}
