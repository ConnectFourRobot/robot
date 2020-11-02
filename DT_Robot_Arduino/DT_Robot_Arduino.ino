#define eventIsSet(ev) (events & ev)
#define servoPin 6
#define sButton  8

#define Q1 1
#define Q2 2

short trigger = 0;
short events = 0;

void setup() {
 pinMode(sButton, INPUT);
 digitalWrite(sButton, LOW);
 Serial.begin(115200);
}

void clearEvent(int ev){
  events = events & (~ev);
}

void setEvent(int ev){
  events = ev | ev;
}

void Button(){
  while(1){
    if(digitalRead(sButton)== 0){
      trigger = digitalRead(sButton);
    }
    if(digitalRead(sButton)==1 && trigger ==0){
      trigger = digitalRead(sButton);
      if(eventIsSet(Q2)){
        clearEvent(Q2);
        Serial.println("Aus");
      }else{
        Serial.println("Ein");
        setEvent(Q2);
      }
    }
  }
}
void loop() {
  Button();
}
