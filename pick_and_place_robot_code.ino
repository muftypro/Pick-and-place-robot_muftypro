#include <AFMotor.h>
#include <Servo.h>
Servo servo_round, servo_picker, servo_left, servo_right;

int command, state_round, state_picker;
int count_round = 0, count_picker = 0, count_left = 30, count_right = -50, max_picker = 50;



void setup() {

  // Define the servo signal pins
  servo_left.attach(4);
  servo_right.attach(6);
  servo_round.attach (10);
  servo_picker.attach(12) ;

  //default positoin of servo
  servo_right.write(count_right); //forward,backward
  //  servo_left.write(count_left); //up down
  servo_picker.write(50); //picker
  Serial.begin(9600);

}

void loop() {

  if (Serial.available() > 0) {
    command = Serial.read();

    Serial.print("command=");
    Serial.println(command);



    //    rectangle sign=4=52
    //    cross sign=5=53
    //    triangle sign=6=54
    //    circle sign=7=55

    //    select button=8=56
    //    start button=9=57


    if (command == 53)    //close picker || value of cross sign=53
    {
      //      int lowest = 8; //8 degree thakle clip 2 ta thik moto close thake
      max_picker = max_picker - 5;
      if (max_picker == 6) {
        max_picker = 8;
      }
      servo_picker.write(max_picker); //8 degree is perfect

      delay(500);

    }
    else if (command == 52)   //open picker
    {
      max_picker = 50;
      servo_picker.write(max_picker);
      delay(500);

    }
    else if (command == 49) {       //rotate body to right

      state_round = servo_round.read();
      state_round = state_round + 5;
      servo_round.write(state_round);

    }

    else if (command == 48) {   //rotate body to left
      state_round = servo_round.read();
      state_round = state_round - 5;
      servo_round.write(state_round);

    }


    //    left arrow=0=48
    //    right arrow=1=49
    //    upper arrow=2=50
    //    down arrow=3=51


    else if (command == 51) {       //up
      //      count_left = count_left + 5;
      count_left = servo_left.read() + 5;

      servo_left.write(count_left);


    }

    else if (command == 50) {     //down
      count_left = servo_left.read() - 5;
      servo_left.write(count_left);

    }

    else if (command == 54) {       //forward
      count_right = servo_right.read() + 5;
      servo_right.write(count_right);
    }

    else if (command == 55) {     //backward
      count_right = servo_right.read() - 5;
      servo_right.write(count_right);
    }
  }
}
