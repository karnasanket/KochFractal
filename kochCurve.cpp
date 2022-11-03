#include <iostream>
#include <math.h>
#include <string>
# define M_PI           3.14159265358979323846  /* pi */

using namespace std;

    /* This is recursive function that calls itself until it reaches the base case which is levels reaches 0
        When the base function is reaches, this fucntions calculates the x and y based on its current length, which is determines by the levels.
        When the x and y is calculated, the function draw a line from that x to the y.

        This method needs to be called with 3 parameters. 1st is the length of the points from (x,y) to (x1,y1)
        Second is the levels, which determines the number of times the recursive funtion gets called
        Thirds is the "turnAngle" or the relative angle of the line, which determines if the line being draw is a flat line, or a slanted line at a an angle

        This method through its recursive calls, draw line segments from one (x,y) to another (x1,y1) which eventually draws the fractal 
    */

    /* How it really works: 
        When the first call from main happens, that is length of the entire line. If the level is 0, the function skips the (leves>0) part
        Then it goes straight to the calculation of two points that is entered.
        These two points are calulated with the trig and the angle. The angle is converted to radian using the value of pi/180
        The cos of the angle* length gives us the x coord of the point and the sin of the angle*length gives us the y corrs (because in the Unit circle (x,y) is (cos,sin))
        Given that the first points is already set in the main function, all koch needs to do is "rlineto" to the new x,y coords to draw a line

        If the levels is >0, we divide the function and call itself.
        Meaning: There is goign to be a koch fractal "bump" in the middle of line. So we divide the length of the line/3.

        First call is for the first line of the 1/3 segement, that is going to be at the same angle as the line, hence why we pass +0.0 for angle and call koch for level-1

        Second call is the first slanted, 60degree line that is drawn in the 2/3rd segment of the line, that is the same length as line/3. So,
        we call koch for that line with levels-1 

        Third call is the second slanted line, that goes from the tip of the first slanted line to the tip start point of the 3/3rd segment of the line. 
        The angle for this is going to be the opposite of 1st slanted, so angle-60 degree. So, we call this fucntion with levels-1.

        Last call is the 3/3rd segment of the line, which is at the same angle as the main line, so we do not add any angle to it. Its length is still line/3, so we call that 
        with levels-1. 

        We recursively call the function by dividing it /3 and decreasing the levels so we reach the base case of the function so the desired line from one point to the other is drawn. 
    */
void koch(double length, int levels, double turnAngle) {
    
    if(levels > 0) { // if levels > 0, so has not reached base case yet
        koch(length/3, levels-1, turnAngle + 0.0); // call for the only line of the 1/3rd segement
        koch(length/3, levels-1, turnAngle + 60.0); // call for the 1/2 line of the 2/3rd segment at an angle
        koch(length/3, levels-1, turnAngle - 60.0); // call for the 2/2 line of the 2/3rd segment at an angle also
        koch(length/3, levels-1, turnAngle + 0.0); // call for the only line of the 3/3rd segment
    } else { // when base case is reached
        double x = length*cos(turnAngle*(M_PI/180)); // find the x coord of the point that we need to draw the line to 
        double y = length*sin(turnAngle*(M_PI/180)); // find the y coord of the point that we need to draw the line to 
        cout << x << " " << y << " rlineto" << endl; // draw the line to the new x,y
    }
}


    /* This method caculates the neccesary variables to call the koch function that is draws the snowflake
        This method doesnt ask the user for input, rather the user inputs into the command line with the execuatble
        It is expected that there is 6 total arguements in the command line, or the program will not work

        If the executable is koch.exe, then the command line would be ./koch 72 360 504 360 4 
                                                                        .exe x1  y1  x2  y2 levels

        This method then stores the values in a int variables and calls the koch function after doing some trig-based
        mathematics for the desired relative angle.
        This method also outputs command that would work on .ps file as the command line would direct the output to a .ps file
        to be able to view the snowflake.
    */
int main(int argc, char* argv[]) {

    if(argc != 6) { // if there is less than 6 arguemnts, then the program outputs "Invalid Input".
        cout << "Invalid Input" << endl;
    } else if (stoi(argv[5]) < 0) { // if 6th command of the commandline is less than 0, which is the levels, the program doesnt run
        cout << "Levels need to be higher than 0" << endl;
    } else {
        int x = stoi(argv[1]); // 1st arguement is the first x coord
        int y = stoi(argv[2]); // 2nd arguement is the first y coord
        int x1 = stoi(argv[3]); // 3rd arguement is the second x coord
        int y1 = stoi(argv[4]); // 4th arguement is the seocond y coord 
        int levels = stoi(argv[5]); // 5th arguement is the levels
        
        double xTot = (x1-x); // total x coord, basically deltaX
        double yTot = (y1-y); // total y coord, basically deltaY

        double length = sqrt((xTot*xTot) + (yTot*yTot)); // finding the distance using the distance formula
        double angle  = atan2(yTot, xTot); // finding the relative angle of the line using atan2() which is the same as tan^-1(delta(y)/delta(x)) 
                                           // aTan2() works better functionally in the case of "divide by 0"
        
        cout << "%!PS-Adobe-2.0" << endl; // first line of output to display on the .ps file for rendering the image
        cout << x << " " << y << " moveto" << endl; // moveto command which is the begin point in the coord plane
        koch(length, levels, angle); //koch function uses the length of the (x,y) to (x1,y1), the levels the user inputed and the relative angle of the line
                                     // this calls only draw a line of the koch fractal between 2 points

        koch(length, levels, angle-120); //same fucntion call as the one above, but this one is called at the angle-120, which is 1/2 points that is on one side of line
        koch(length, levels, angle-240); //same fucntion call as the one above, but this one is called at the angle-240, which is 2nd points that is on other side of line
                                         // these calls helps draw the entire snowflake   

        
        cout << "stroke \nshowpage" << endl; // .ps file requirement 

    }

    return 0;
}