#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/mman.h>       
#include <linux/fb.h>       
#include <sys/ioctl.h>      

#define FILEPATH "/dev/fb1"                     //Filepath to LED matrix
#define NUM_LED 64                              //Number of LED
#define FILESIZE (NUM_LED * sizeof(uint16_t))   //Size required for LED  

//color codes
#define White           0xFFFF
#define Yellow          0xFFE0           
#define Orange          0xFD20 
#define Pink            0xF81F
#define Cyan            0x07FF  
#define Green           0x07E0
#define Red             0xF800    
#define Magenta         0xF81F   
#define Maroon          0x7800 
#define DarkCyan        0x03EF
#define DarkGreen       0x03E0
#define Navy            0x000F
#define Purple          0x780F
#define LightGrey       0xC618
#define DarkGrey        0x7BEF
#define Blue            0x001F
#define Olive           0x7BE0
#define GreenYellow     0xAFE5            

/*Arrays and pointer*/          
uint rainbow[7];            //Array for colors of the rainbow
uint color[19];             //Array for all the color
uint16_t *map;              //a pointer that maps to LED
uint16_t *p;                //a pointer to the starting address of map pointer

/*Function*/   
void delay(int);            //function to keep the lights on
void initialize();          //function to intialize the colors to color array
void initializerainbow();   //function to intialize rainbow to array rainbow

void choose();              //function to choose between options

void option1();             //Option1 prints a rainbow
int rainbow1();             //Rainbow1 refers to the first diagonal on the LED screen
int rainbow2();             //Second diagonal on the LED screen
int rainbow3();             //Third diagonal on the LED screen
int rainbow4();             //Fourth diagonal
int rainbow5();             //Fifth diagonal
int rainbow6();             //Sixth diagonal
int rainbow7();             //Seventh diagonal
int rainbow8();             //Eight diagonal
int rainbow9();             //Ninth diagonal
int rainbow10();            //Tenth diagonal
int rainbow11();            //Eleven diagonal
int rainbow12();            //Tweleve diagonal
int rainbow13();            //Thirteen diagonal
int rainbow14();            //Fourteen diagonal
int rainbow15();            //Fiftheen diagonal

void option2();             //Option2 prints the color the user chooses
void printcolorcode();      //Prints color code
void lightup(int colorcode, int delaytime); //Lights up the screen

void option3();             //Option 3 is a snake game
int movementcalculation(int current, int move, int app);    //Calculate user input and light up accordingly 

int main(void)
{
    int i;
    int LED;

    /*Variable to get screen info*/
    struct fb_fix_screeninfo fix_info;

    /* Open LED frame buffer device */
    LED = open(FILEPATH, O_RDWR);           //O_RDWR opens, read and write linux
    if (LED == -1) 
    {
	printf("Error: Could not access LED");
	exit(0);
    }

    /* Read fixed screen info of the open device, used to check if LED was found */
    if (ioctl(LED, FBIOGET_FSCREENINFO, &fix_info) == -1)   //Octl() function calls to system device 
    {
	printf("Error: Could not get screen info of LED");      
	close(LED);
	exit(1);
    }   

    /* Check if RPi-Sense FB has been found */
    if (strcmp(fix_info.id, "RPi-Sense FB") != 0) 
    {
	printf("Error: RPi-Sense FB not found\n");
	close(LED);
	exit(2);
    }

    /* map the led frame buffer device into memory */
    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, LED, 0); //maps process address space with LED, so LED can be accessed using array/pointer
    if (map == MAP_FAILED) 
    {
	printf("Error: Could not map the file\n");
    close(LED);
	exit(3);
    }

    p = map; //pointer to the start of the memory area

    /*Initialize array for the different colors*/
    initialize();
    initializerainbow();

    lightup(0,0);   //Used to clear LED matrix
    
    choose();

    /* un-map and close LED */
    if (munmap(map, FILESIZE) == -1) //munmap() unmaps LED
    {
	printf("Error un-mmapping the file");
    }
    close(LED);

    return 0;
}

void delay(int t)
{
    /*usleep() suspends current processes, used to keep LED lights on*/
    usleep(t * 10000); 
}

void choose()
{
    int choice;

    /*Print the different options*/
    printf("\nEnter 1 to see the rainbow\n");
    printf("Enter 2 to see the color you want\n");
    printf("Enter 3 to play snakes\n");
    printf("Enter 4 to exit\n:");
    scanf("%d", &choice);

    /*Determins option function to call*/
    if (choice == 1)
    {
        option1();
        choose();
    }
    if (choice == 2)
    {
        option2();
        choose();
    }
    if (choice == 3)
    {
        option3();
    }
    if (choice == 4)
    {
        exit(1);
        lightup(0,0);
    }
    else
    {
        printf("Invalid choice, choose again");
        choose();
    }
}

void initialize()
{
    /*Intialize colors into color array*/
    color[0]=0;
    color[1]=White;
    color[2]=Yellow;
    color[3]=Orange;
    color[4]=Pink;
    color[5]=Cyan;
    color[6]=Green;
    color[7]=Red;
    color[8]=Magenta;
    color[9]=Maroon;
    color[10]=DarkCyan;
    color[11]=DarkGreen;
    color[12]=Navy;
    color[13]=Purple;
    color[14]=LightGrey;
    color[15]=DarkGrey;
    color[16]=Blue;
    color[17]=Olive;
    color[18]=GreenYellow;
}

void initializerainbow()
{
    /*Intialize colors into rainbow array*/
    rainbow[0]=Red;
    rainbow[1]=Orange;
    rainbow[2]=Yellow;
    rainbow[3]=Green;
    rainbow[4]=Blue;
    rainbow[5]=Magenta;
    rainbow[6]=Purple;
}

void option1()
{
    /*Prints out rainbow color diagonal row by row*/
    int count=0;
    rainbow1(count);
    rainbow2(count);
    rainbow3(count);
    rainbow4(count);
    rainbow5(count);
    rainbow6(count);
    rainbow7(count);
    rainbow8(count);
    rainbow9(count);
    rainbow10(count);
    rainbow11(count);
    rainbow12(count);
    rainbow13(count);
    rainbow14(count);
    rainbow15(count);

    delay(2.5);

    /*Prints out rainbow color diagonal row by diagonal row*/
    int i;
    for (i = 0; i < 30; i++) //it takes 15 for one cycle, one cycle is the color change from 1 to 15 diagonal row
    {
        rainbow15(i);
    }

    /*Clear LED matrix*/
    lightup(0,0);
}

int rainbow1(int count)
{
    count=count%7;
    *(p+0)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow2(int count)
{
    count=count%7;
    rainbow1(count+1);
    *(p+1)=rainbow[count];
    *(p+8)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow3(int count)
{
    count=count%7;
    rainbow2(count+1);
    *(p+2)=rainbow[count];
    *(p+9)=rainbow[count];
    *(p+16)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow4(int count)
{
    count=count%7;
    rainbow3(count+1);
    *(p+3)=rainbow[count];
    *(p+10)=rainbow[count];
    *(p+17)=rainbow[count];
    *(p+24)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow5(int count)
{
    count=count%7;
    rainbow4(count+1);
    *(p+4)=rainbow[count];
    *(p+11)=rainbow[count];
    *(p+18)=rainbow[count];
    *(p+25)=rainbow[count];
    *(p+32)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow6(int count)
{
    count=count%7;
    rainbow5(count+1);
    *(p+5)=rainbow[count];
    *(p+12)=rainbow[count];
    *(p+19)=rainbow[count];
    *(p+26)=rainbow[count];
    *(p+33)=rainbow[count];
    *(p+40)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow7(int count)
{
    count=count%7;
    rainbow6(count+1);
    *(p+6)=rainbow[count];
    *(p+13)=rainbow[count];
    *(p+20)=rainbow[count];
    *(p+27)=rainbow[count];
    *(p+34)=rainbow[count];
    *(p+41)=rainbow[count];
    *(p+48)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow8(int count)
{
    count=count%7;
    rainbow7(count+1);
    *(p+7)=rainbow[count];
    *(p+14)=rainbow[count];
    *(p+21)=rainbow[count];
    *(p+28)=rainbow[count];
    *(p+35)=rainbow[count];
    *(p+42)=rainbow[count];
    *(p+49)=rainbow[count];
    *(p+56)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow9(int count)
{
    count=count%7;
    rainbow8(count+1);
    *(p+15)=rainbow[count];
    *(p+22)=rainbow[count];
    *(p+29)=rainbow[count];
    *(p+36)=rainbow[count];
    *(p+43)=rainbow[count];
    *(p+50)=rainbow[count];
    *(p+57)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow10(int count)
{
    count=count%7;
    rainbow9(count+1);
    *(p+23)=rainbow[count];
    *(p+30)=rainbow[count];
    *(p+37)=rainbow[count];
    *(p+44)=rainbow[count];
    *(p+51)=rainbow[count];
    *(p+58)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow11(int count)
{
    count=count%7;
    rainbow10(count+1);
    *(p+31)=rainbow[count];
    *(p+38)=rainbow[count];
    *(p+45)=rainbow[count];
    *(p+52)=rainbow[count];
    *(p+59)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow12(int count)
{
    count=count%7;
    rainbow11(count+1);
    *(p+39)=rainbow[count];
    *(p+46)=rainbow[count];
    *(p+53)=rainbow[count];
    *(p+60)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow13(int count)
{
    count=count%7;
    rainbow12(count+1);
    *(p+47)=rainbow[count];
    *(p+54)=rainbow[count];
    *(p+61)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow14(int count)
{
    count=count%7;
    rainbow13(count+1);
    *(p+55)=rainbow[count];
    *(p+62)=rainbow[count];
    delay(1);
    return 0;
}

int rainbow15(int count)
{
    count=count%7;
    rainbow14(count+1);
    *(p+63)=rainbow[count];
    delay(1);
    return 0;
}

void option2()
{
    int i,j=0;

    /*Get color to print*/
    printcolorcode();
    printf("\nPlease enter the number of the color you want to see: ");
    scanf("%d", &j);

    /* light LED one by one */
    lightup(j,5);


    /* light all LED and blinks */
    for (i = 0; i < 3; i++)
    {
        lightup(j,0);
        delay(30);
        lightup(0,0);
        delay(30);
    }

    choose();
}

void printcolorcode()
{
    /*Prints all the color code*/
    printf("\nColors available \n1:White \n2:Yellow \n3:Orange \n4:Pink");
    printf("\n5:Cyan \n6:Green \n7:Red \n8:Magenta \n9:Maroon \n10:DarkCyan");
    printf("\n11:DarkGreen \n12:Navy \n13:Purple \n14:Lightgrey \n15:Darkgrey \n16:Blue");
    printf("\n17:Olive \n18:Greenyellow");
}

void lightup(int colorcode, int delaytime)
{
    /*colorcode: chooses color*/
    /*delaytime: determines how long lights are displayed*/
    int i;
    for (i = 0; i < NUM_LED; i++) 
    {
	*(p + i) = color[colorcode];
    delay(delaytime);
    }
}

void option3()
{
    /*Snake game*/

    int movement=0;
    int currentlocation=0;
    int i=0;
    int apple;
    int iteration=0;
    srand(time(0));
    printf("the controls are 1,2,3,4 which are up down left right:");

    apple = rand() % 64;  //Set the apple at a random location  
    currentlocation = movementcalculation(currentlocation, movement, apple); //Print out on LED of current location

    do
    {
    if (apple != currentlocation)   //Continue to get user input till the snake collides with the apple
    {
        printf("\n:");
        scanf("%d", &movement);
        lightup(0,0);
        currentlocation = movementcalculation(currentlocation, movement, apple);
    }
    if (apple == currentlocation)   //Snake collides, change apple location
    {
        apple = rand() % 64;
        apple %= 64;    
        currentlocation = movementcalculation(currentlocation, 0, apple);
        iteration++;
    }
        if (iteration == 3)         //Iteration determines how many time the snake game is played
    {
        int j;
        for (j = 0; j < 3; j++)
        {
            lightup(1,0);
            delay(25);
            lightup(0,0);
            delay(25);
        }    
        choose();
    }
    }
    while (i<1);
}

int movementcalculation(int current, int move, int app)
{
    int i=1;
    int j=0;

    current+=64; //Ensures there no negative number

    /*Calculates movement and print colors*/
    
    /*Displays current location*/
    if (move == 0)
    {
        current%=64;
        *(p+current)=rainbow[i];
        *(p+app)=rainbow[j];
        delay(50);
    }
    
    /*Displays new location after moving up*/
    if (move == 1)
    {
        current+=8; //+8 is used to go up
        current%=64;
        *(p+current)=rainbow[i];
        *(p+app)=rainbow[j];
        delay(50);
    }

    /*Displays new location after moving down*/
    if (move == 2)
    {
        current-=8; //-8 is used to go up
        current%=64;
        *(p+current)=rainbow[i];
        *(p+app)=rainbow[j];
        delay(50);
    }

    /*Displays new location after moving left*/
    if (move == 3)
    {
        current+=1; //+1 is used to go right
        current%=64;
        *(p+current)=rainbow[i];
        *(p+app)=rainbow[j];
        delay(50);
    }

    /*Displays new location after moving right*/
    if (move == 4)
    {
        current-=1; //-1 is used to go left
        current%=64;
        *(p+current)=rainbow[i];
        *(p+app)=rainbow[j];
        delay(50);
    }

    return current;
}

