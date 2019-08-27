#define out1 2
#define out2 3
#define out3 4
#define out4 5

#define in1 A3
#define in2 A2
#define in3 A1
#define in4 A0

unsigned char memory[20];
unsigned char score = 0;
unsigned char loc = 0;
bool isOver = false;
bool isDisplayed = false;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);

  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);

  memory[score++] = random(1, 4);
}

bool isClicked = false;
unsigned char clickButton = 0;

void loop() {
  if (isOver) return;
  int state1 = digitalRead(in1);
  int state2 = digitalRead(in2);
  int state3 = digitalRead(in3);
  int state4 = digitalRead(in4);
  
  if (!isDisplayed) {
    displayMemory();
  } else {
    if (!isClicked) {
      if (state1 == LOW) {
        isClicked = true;
        clickButton = 1;
      } else if (state2 == LOW) {
        isClicked = true;
        clickButton = 2;
      } else if (state3 == LOW) {
        isClicked = true;
        clickButton = 3;
      } else if (state4 == LOW) {
        isClicked = true;
        clickButton = 4;
      }
    } else {
      if (clickButton != 0) {
        if (clickButton != memory[loc++]) {
          isOver = true;
          digitalWrite(out1, HIGH);
          digitalWrite(out2, HIGH);
          digitalWrite(out3, HIGH);
          digitalWrite(out4, HIGH);
          delay(500);
          digitalWrite(out1, LOW);
          digitalWrite(out2, LOW);
          digitalWrite(out3, LOW);
          digitalWrite(out4, LOW);
        } else {
          if (loc == score) {
            memory[score++] = random(1, 4);
            isDisplayed = false;
            loc = 0;
            clickButton = 0;
          }
        }
      }
      delay(250);
      isClicked = false;
    }
  }
}

void onPin(int led) {
  switch(led) {
    case 1:
      delay(500);
      digitalWrite(out1, HIGH);
      delay(500);
      digitalWrite(out1, LOW);
      break;
    case 2:
      delay(500);
      digitalWrite(out2, HIGH);
      delay(500);
      digitalWrite(out2, LOW);
      break;
    case 3:
      delay(500);
      digitalWrite(out3, HIGH);
      delay(500);
      digitalWrite(out3, LOW);
      break;
    case 4:
      delay(500);
      digitalWrite(out4, HIGH);
      delay(500);
      digitalWrite(out4, LOW);
      break;
  }
}

void displayMemory() {
  for (int i = 0; i < score; i++) {
    onPin(memory[i]);
  }
  isDisplayed = true;
}
