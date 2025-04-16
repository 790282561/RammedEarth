#include <AccelStepper.h>
#include <Servo.h>

AccelStepper stepper_1 = AccelStepper(1, A0, A1);
AccelStepper stepper_2 = AccelStepper(1, 6, 7);
AccelStepper stepper_whip = AccelStepper(1, 8, 9);
Servo myservo;

int i = 1;  // 舵机连通指针
int lastButtonState = LOW;  // 上一次kuka输出端口电频
int buttonState;  // 目前kuka输出端口电频
long lastDebounceTime = 0;  // 上一次端口被触发时间
long debounceDelay = 20;  // 防抖间隔时间

void setup()
{
  /* kuka数据传入 */
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  /* 设置 stepper_1 的初始参数 */
  stepper_1.setMaxSpeed(2000);
  stepper_1.setSpeed(500);

  /* 设置 stepper_2 的初始参数 */
  stepper_2.setMaxSpeed(2000);
  stepper_2.setSpeed(500);

  /* 设置 stepper_whip 的初始参数 */
  stepper_whip.setMaxSpeed(4000);
  stepper_whip.setSpeed(500);

  /* 设置舵机信息串口 */
  myservo.attach(13);

  Serial.begin(9600);
}

void loop()
{
  int bool_21 = digitalRead(2);
  int bool_22 = digitalRead(3);
  int bool_23 = digitalRead(4);
  int bool_24 = digitalRead(5);

  /* -----------------------------左电机------------------------------ */
  if (bool_21 == HIGH)
  {
    stepper_1.move(2000);
    stepper_1.setSpeed(500);
    stepper_1.runSpeed();
  }
  else if (bool_21 == LOW)
  {
    stepper_1.stop();
  };

  /* -----------------------------右电机------------------------------ */
  if (bool_22 == HIGH)
  {
    stepper_2.move(2000);
    stepper_2.setSpeed(-500);
    stepper_2.runSpeed();
  }
  else if (bool_22 == LOW)
  {
    stepper_2.stop();
  };

  /* -----------------------------搅拌机------------------------------ */
  if (bool_23 == HIGH)
  {
    stepper_whip.move(2000);
    stepper_whip.setSpeed(-4000);  // 数值固定1500不再改变
    stepper_whip.runSpeed();
  }
  else if (bool_23 == LOW)
  {
    stepper_whip.stop();
  };

  /* -------------------------------舵机------------------------------ */
  if (bool_24 != lastButtonState)
  {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (bool_24 == HIGH && i == 1)  // 让舵机只转动一次
    {
      servo_open();
      i = 0;
    }

    if (bool_24 == LOW && i == 0)
    {
      servo_close();
      i = 1;
    }
  }
  lastButtonState = bool_24;
}

void servo_open() {
  int pos;
  for (pos = 90; pos <= 125; pos ++) {
    myservo.write(pos);  // 舵机角度写入
    delay(5);
  }
}

void servo_close() {
  int pos;
  for (pos = 125; pos >= 90; pos --) {
    myservo.write(pos);  // 舵机角度写入
    delay(5);  // 等待转动到指定角度
  }
}
