#include <iostream>
#include<string>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include<conio.h> //CONSOLE INPUT OUTPPUT. FOR WORKING SCREEN CLEAR AND GETCH
#include<iomanip> //FOR WORKING SETW - SET WIDTH
#define Product struct Prod


void add(FILE * fp);
void modify(FILE * fp);
void display(FILE * fp);
void Indivisual(FILE *fp);
void password();
FILE * del(FILE * fp);
void printChar(char ch,int n);
void title();
FILE *tp;


void gotoxy(int x,int y)
{
    COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

struct pass
{
    char pass[25];
} pa;

struct Prod
{
    char name[100];
    char category[50];
    int product_id;
    float price;
    int stock;
    char time[30];
};

using namespace std;

int main()
{
    cout << fixed << setprecision(2); //HOW MANY NUMBERS WILL SHOW AFTER POINT
    int ch,id,k,i;
    char c,pas[50];
    SetConsoleTitle("Product Record Management System | GREEN UNIVERSITY OF BANGLADESH | 213002039");
    FILE * fp;
    Product s;
    int option;
    char another;

    if((fp=fopen("db.txt","rb+"))==NULL)
    {
        if((fp=fopen("db.txt","wb+"))==NULL)
        {
            cout<<"Can't create or open Database."<<endl;
            return 0;
        }
    }

    system("color 0");
    gotoxy(42,8);
    cout << "LOGIN(If 1st login press ENTER)";
    gotoxy(42,10);
    cout << "____________________________________";
    gotoxy(42,11);
    cout << "|\tEnter password :             |";
    gotoxy(42,12);
    cout << "|__________________________________|";
    gotoxy(65,11);

    while( k<10)
    {
        pas[k]=getch();
        char s=pas[k];
        if(s==13)
            break;
        else
            cout << "*";
        k++;
    }

    pas[k]='\0';
    tp=fopen("F:/Password.txt","r+");
    fgets(pa.pass,25,tp);
    if(strcmp(pas,pa.pass)==0)
    {
        system("cls");
        gotoxy(10,3);
        cout << "<<<< Loading Please Wait >>>>";
        for(i=0; i<5; i++)
        {
            cout << "\t(*_*)";
            Sleep(50);
        }
        cout << " \n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *";
        cout << "\n\n\t\t\t\t\t     *                    *";
        cout << "\n\n\t\t\t\t\t     *       Welcome      *";
        cout << "\n\n\t\t\t\t\t     *                    *";
        cout << "\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *";
        cout << "\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ";
        getch();

        title();
        cout << "\n\n\t\t\t\tLab Final || CSE104";
        cout << "\n\n\t\t\t  GREEN UNIVERSITY OF BANGLADESH\n\t\t\t";
        cout << "\n\n\t\t\t  MD SAIFUL ISLAM RIMON | 213002039\n\t\t\t";
        printChar('=',38);
        cout << "\n\n\n\t\t\t       press any key to Enter";
        getch();

        while(1)
        {
            title();
            cout << "\n\t";
            printChar('*',64);

            cout << "\n\n\t\t\t  MD SAIFUL ISLAM RIMON | 213002039\n\t\t\t";
            cout << "\n\n\t\t\t\t1. Add Product";
            cout << "\n\n\t\t\t\t2. Modify Product";
            cout << "\n\n\t\t\t\t3. Show All Product";
            cout << "\n\n\t\t\t\t4. Individual View";
            cout << "\n\n\t\t\t\t5. Remove Product";
            cout << "\n\n\t\t\t\t6. Change Password";
            cout << "\n\n\t\t\t\t7. Logout\n\t";
            printChar('*',64);
            cout << "\n\n\t\t\t\tEnter Your Option :--> ";
            cin>>option;

            switch(option)
            {
            case 1:
                add(fp);
                break;
            case 2:
                modify(fp);
                break;
            case 3:
                display(fp);
                break;
            case 4:
                Indivisual(fp);
                break;
            case 5:
                fp=del(fp);
                break;
            case 6:
                system("cls");
                system("color 0f");
                password();
                break;
            case 7:
                return 1;
                break;
            default:
                cout << "\n\t\tNo Action Detected";
                cout << "\n\t\tPress Any Key\n\n\n";
                getch();
                system("pause");
            }
        }
    }
    else
    {
        cout << "Wrong Password . Get Out";
        getch();
    }
    return 1;

}

void password()
{
    char c;
    cout << "\nEnter new password :";
    fflush(stdin);
    gets(pa.pass);
    cout << "\nSave password (y/n) :";
    fflush(stdin);
    cin >> c;
    if(c=='y'||c=='Y')
    {
        tp=fopen("F:/Password.txt","w+");
        fwrite(&pa,sizeof(pa),1,tp);
        fclose(tp);
        cout << "\n\tPassword Saved\n";
    }
    else
    {
        cout << "Password not saved :\n";
        cout << "Press any key to continue >>>";
        getch();
    }
}

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void title()
{
    system("cls");
    system("COLOR 00");
    cout << "\n\n\t";
    printChar('=',19);
    cout << " Product Record Management System ";
    printChar('=',19);
    cout << "\n";
}

void add(FILE * fp)
{
    title();

    char another='y';
    Product s;
    int i;
    float price;

    fseek(fp,0,SEEK_END);
    while(another=='y'||another=='Y')
    {

        cout << "\n\n\t\tEnter Full Name of Product: ";
        fflush(stdin);
        fgets(s.name,100,stdin);
        s.name[strlen(s.name)-1]='\0';

        cout << "\n\n\t\tEnter Category (Hint: Mouse/Keyboard/Monitor etc.): ";
        fflush(stdin);
        fgets(s.category,50,stdin);
        s.category[strlen(s.category)-1]='\0';

        cout << "\n\n\t\tEnter Product ID number: ";
        cin >> s.product_id;

        cout << "\n\n\t\tEnter Product price: ";
        cin >> s.price;

        cout << "\n\n\t\tStock available: ";
        cin>> s.stock;

        time_t now = time(0); //current date and time based on system

        char* dt  = ctime(&now); //convert now to string form
        fflush(stdin);
        strcpy(s.time,dt);
        s.time[strlen(s.time)-1]='\0';

        fwrite(&s,sizeof(s),1,fp);

        cout << "\n\n\t\tAdd another Product?(Y/N)?";
        fflush(stdin);
        another=getchar();
    }
}

FILE * del(FILE * fp)
{
    title();

    Product s;
    int flag=0,tempproduct_id,siz=sizeof(s);
    FILE *ft;

    if((ft=fopen("temp.txt","wb+"))==NULL)
    {
        cout << "\n\n\t\t\t\\t!!! ERROR !!!\n\t\t";
        system("pause");
        return fp;
    }

    cout << "\n\n\tEnter ID number of the product to Delete the Record";
    cout << "\n\n\t\t\tProduct ID No. : ";
    cin >> tempproduct_id;

    rewind(fp);


    while((fread(&s,siz,1,fp))==1)
    {
        if(s.product_id==tempproduct_id)
        {
            flag=1;
            cout << "\n\tRecord Deleted for";
            cout << "\n\n\t\t" << s.name << "\n\n\t\t" << s.category << "\n\n\t\t" << s.product_id << "\n\t";
            continue;
        }

        fwrite(&s,siz,1,ft);
    }


    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("temp.txt","db.txt");

    if((fp=fopen("db.txt","rb+"))==NULL)
    {
        cout << "ERROR";
        return  NULL;
    }

    if(flag==0)
        cout << "\n\n\t\tNO Product FOUND WITH THE INFORMATION\n\t";

    printChar('-',65);
    cout << "\n\t";
    system("pause");
    return fp;
}

void modify(FILE * fp)
{
    title();

    Product s;
    int i,flag=0,tempproduct_id,siz=sizeof(s);
    float price;

    cout << "\n\n\tEnter ID Number of Product to MODIFY the Record : ";
    cin >> tempproduct_id;

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        if(s.product_id==tempproduct_id)
        {
            flag=1;
            break;
        }
    }

    if(flag==1)
    {
        fseek(fp,-siz,SEEK_CUR);
        cout << "\n\n\t\t\t\tRecord Found\n\t\t\t";
        printChar('=',38);
        cout << "\n\n\t\t\tProduct Name: " << s.name;
        cout << "\n\n\t\t\tProduct ID: " << s.product_id << "\n\t\t\t";
        printChar('=',38);
        cout<<"\n\nWhich option you want to MODIFY?\n1. NAME\n2. CATEGORY\n3. PRODUCT ID\n4. PRICE\n5. STOCK\n\n";
        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
        {
            cout << "\n\n\t\t\tEnter Full Name of Product: ";
            fflush(stdin);
            fgets(s.name,100,stdin);
            s.name[strlen(s.name)-1]='\0';
            break;
        }
        case 2:
        {
            cout << "\n\n\t\t\tEnter Category: ";
            fflush(stdin);
            fgets(s.category,50,stdin);
            s.category[strlen(s.category)-1]='\0';
            break;
        }
        case 3:
        {
            cout << "\n\n\t\t\tEnter Product ID number: ";
            cin >> s.product_id;

            break;
        }
        case 4:
        {
            cout << "\n\n\t\t\tEnter Product price: ";
            cin >> s.price;
            break;
        }
        case 5:
        {
            cout << "\n\n\t\t\tStock available: ";
            cin>> s.stock;
            break;
        }
        default:
            cout << "Wrong Option Chosen!";
            break;
        }


        fwrite(&s,sizeof(s),1,fp);
    }

    else
        cout << "\n\n\t!!!! ERROR !!!! RECORD NOT FOUND";

    cout << "\n\n\t";
    system("pause");

}

void display(FILE * fp)
{
    title();
    Product s;
    int i,siz=sizeof(s);

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        cout << "\n\t\tNAME : " << s.name;
        cout << "\n\n\t\tCategory : " << s.category;
        cout << "\n\n\t\tProduct ID : " << s.product_id;
        cout << "\n\n\t\tProduct price: " << s.price << " BDT";
        cout << "\n\n\t\tStock Available: " <<s.stock << " PCS.";
        cout << "\n\n\t\tDate added: " <<s.time  ;

        cout << "\n\t";
        printChar('-',65);
    }
    cout << "\n\n\n\t";
    printChar('*',65);
    cout << "\n\n\t";
    system("pause");
}

void Indivisual(FILE *fp)
{
    title();

    int tempproduct_id,flag,siz,i;
    Product s;
    char another='y';

    siz=sizeof(s);

    while(another=='y'||another=='Y')
    {
        cout << "\n\n\tEnter Product ID Number: ";
        cin >> tempproduct_id;

        rewind(fp);

        while((fread(&s,siz,1,fp))==1)
        {
            if(s.product_id==tempproduct_id)
            {
                flag=1;
                break;
            }
        }

        if(flag==1)
        {
            cout << "\n\t\tNAME : " << s.name;
            cout << "\n\n\t\tCategory : " << s.category;
            cout << "\n\n\t\tProduct ID : " << s.product_id;
            cout << "\n\n\t\tProduct price: " << s.price << " BDT";
            cout << "\n\n\t\tStock Available: " <<s.stock << " PCS.";
            cout << "\n\n\t\tDate added: " <<s.time  ;

            cout << "\n\t";
            printChar('-',65);

        }
        else
            cout << "\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!";

        cout << "\n\n\t\tShow another Product information? (Y/N)?";
        fflush(stdin);
        another=getchar();
    }
}


