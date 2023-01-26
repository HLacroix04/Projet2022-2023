#include <Arduino.h>

#define _TASK_MICRO_RES         // Support for microsecond resolution
#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_PRIORITY
#define _TASK_WDT_IDS
#define _TASK_TIMECRITICAL
#include <TaskScheduler.h>

//variables
char carac[6];
float Upanel; 
unsigned long valIrradiance;
unsigned long valTemperature;
int i;

long overrun = 0;     // flag that tells if task has an overrun
unsigned long count = 0;    // counter for tast execution count

void Debug_print();
void Voltage();
void choiceTempSun();
void display();

Scheduler runner;
Scheduler hpr;

Task t4(900000, TASK_FOREVER, &display);
Task t3(700000, TASK_FOREVER, &choiceTempSun);
Task t2(800000, TASK_FOREVER, &Voltage);
Task t1(5000000, TASK_FOREVER, &Debug_print);


extern unsigned long count;


void setup() {

  Serial.begin(250000);
  Serial.println("Scheduler TEST");

  runner.init();
  Serial.println("Initialized scheduler");


  //additon task t1 to task scheduler
  runner.addTask(t1);
  Serial.println("added t1");

  //Task with the most importent priority
  hpr.addTask(t2);
  Serial.println("added t2");

  //additon task t3 to task scheduler
  runner.addTask(t3);
  Serial.println("added t3");

  //additon task t4 to task scheduler
  runner.addTask(t4);
  Serial.println("added t4");

  runner.setHighPriorityScheduler(&hpr);

  delay(1000);

  //tasks activation
  t1.enable();
  Serial.println("Enabled t1");

  t2.enable();
  Serial.println("Enabled t2");

  t3.enable();
  Serial.println("Enabled t3");

  t4.enable();
  Serial.println("Enabled t4");
}



void Debug_print() {
  Scheduler &s = Scheduler::currentScheduler();
  Task &t = s.currentTask();

  Serial.print(millis()); Serial.print("\tStart delay = "); Serial.println(t.getStartDelay());
  Serial.print("Count = ");
  Serial.println(count);
  if (overrun == 1) {
    Serial.println("Overrun");
    overrun = 0;
  }
  count = 0;
}

void Voltage(){

  Upanel = analogRead(A0) / 46.45;
  if (overrun == 1) {
    Serial.println("Overrun");
    overrun = 0;
  }
}

void choiceTempSun(){
  //Get the number of bytes available for reading from the serial port
  if(Serial.available()){ 
    for(i=0; i<10; i++){

      //To read the serial port
      carac[i]=Serial.read();

      //If we receive the character 'E'
      if(carac[i]==69){
        //i++;
        valIrradiance=Serial.parseFloat();
      }

      //If we receive the character 'T'
      if(carac[i]==84){
        valTemperature=Serial.parseFloat()+273;
      }

    }
  }
  if (overrun == 1) {
    Serial.println("Overrun");
    overrun = 0;
  }
}

void display(){
  Scheduler &s = Scheduler::currentScheduler();
  Task &t = s.currentTask();
  if (t.getOverrun() < 0) {
    overrun = 1;
  }

  //JSON format
  Serial.print("{\"Ir\":");
  Serial.print(valIrradiance);

  Serial.print(",\"T\":");
  Serial.print(valTemperature);

  Serial.print(",\"V\":");
  Serial.print(Upanel);
  Serial.println("}");
}

void loop() {
  // put your main code here, to run repeatedly:
  runner.execute();
}


