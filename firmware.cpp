//Sparkjs library Simple Demo app firmware.
//This code should be pasted into your Spark IDE and flashed into your Spark device.
//
//Sparkjs library and this code are available at https://github.com/uchobby/sparkjs
//You can use this code for anything you wish, there no ties or warrantees.
//Send me an email if you have any suggestions or to let me know what you think.
//david.fowler@gmail.com
//
//This simple app needs nothing more than a Spark core to work. It publishes one 
//variable and one function. 
//Variable "rssi"
//  The variable is "rssi" which is the WiFi signal level. 
//Function "LED"
//  The function is "LED" which accepts "ON" to turn on the onboard LED. Anything other
//  then "ON" will turn off the LED.

const int DIO_LED = D7; //Built in LED on D7. It's blue and next to the usb connector

unsigned long currentMS=0;  //Used to keep the current time in milliseconds for pacing in the loop function
unsigned long oldMS=0;  //Used to keep last elapsed time in milliseconds, for pacing in the loop function

int rssi;  //WiFi Singal quality value,  registered in setup for the Spark API.

int LED(String command); //this function will control the LED when called from the Web.

//Configure the hardware and register this core's services to the Spark Server. 
void setup(void) { // Arduino style setup. This routine runs only once upon reset
   //Register our Spark functions here.  Note that we are telling the Spark module where to find 
   //the variables. We will keep the data fresh in our loop function.
  Spark.variable("rssi", &rssi, INT); //Register the rssi variable. This is the WiFi signal level
  Spark.function("LED",LED);  //Here we register the "led" function. A function is called by the 
                              //Spark Core when someone makes the web request. It receives a string
                              //with any arguments that you must parse.
  
  //Setup hardware functions
  pinMode(DIO_LED,OUTPUT);    //Set the LED pin to output mode
  digitalWrite(DIO_LED,LOW);  //Set the LED pin LOW to start, off
}

//Do all our work in the loop function. Note that the Spark Core takes care of 
//all the network stuff when loop returns so don’t get stuck in loop for long. Careful with "delay" functions
void loop(void) {
    //Use millisecond time to pace things, we want to get out of the loop function ASAP and will 
    //use this snip of code to check for when it's time to do something.
    currentMS=millis();  //Grab the current millisecond timer value
    if(currentMS>(oldMS+1000)){ //Has 1000 milliseconds elapsed since last time (1 second)
        oldMS=currentMS;  //Yes, it's time.. Keep the current milliseconds to check later.

        rssi=WiFi.RSSI();  //Grab the WiFi Signal Level value.
    }
}

//Function to control the LED. Takes a string parameter and parses it for the word "ON".
int LED(String command){  //Called by the web LED request automatically as registered in setup().
    if(command=="ON"){    //is the command string set to "ON"
        digitalWrite(DIO_LED,HIGH);  //Yes it is, turn on the LED
    }
    else {
        digitalWrite(DIO_LED,LOW);  //Nope, turn it off.
    }
    return(1);  //This value is passed all the way back to the web requester as an int. -1 usually means fail.
}
