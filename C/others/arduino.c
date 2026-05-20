int w;
int a;
int s;
int d;
int shift;
int space;
int ctrl;
#define w_input 2
#define a_input 3
#define s_input 4
#define d_input 5
#define shift_input 6
#define space_input 7
#define ctrl_input 8
void setup()
{
  Serial.begin(9600);
  pinMode(w_input, INPUT_PULLUP);
  pinMode(a_input, INPUT_PULLUP);
  pinMode(s_input, INPUT_PULLUP);
  pinMode(d_input, INPUT_PULLUP);
  pinMode(shift_input, INPUT_PULLUP);
  pinMode(space_input, INPUT_PULLUP);
  pinMode(ctrl_input, INPUT_PULLUP);
}
void loop()
{
  w = digitalRead(w_input);
  a = digitalRead(a_input);
  s = digitalRead(s_input);
  d = digitalRead(d_input);
  shift = digitalRead(shift_input);
  space = digitalRead(space_input);
  ctrl = digitalRead(ctrl_input);
  if(w == 0)
  {
    Serial.println("w_on");
  }
  else
  {
    Serial.println("w_off");
  }
  if(a == 0)
  {
    Serial.println("a_on");
  }
  else
  {
    Serial.println("a_off");
  }
  if(s == 0)
  {
    Serial.println("s_on");
  }
  else
  {
    Serial.println("s_off");
  }
  if(d == 0)
  {
    Serial.println("d_on");
  }
  else
  {
    Serial.println("d_off");
  }
  if (shift == 0)
  {
    Serial.println("shift_on");
  }
  else
  {
    Serial.println("shift_off");
  }
  if (space == 0)
  {
    Serial.println("space_on");
  }
  else
  {
    Serial.println("space_off");
  }
  if (ctrl == 0)
  {
    Serial.println("ctrl_on");
  }
  else
  {
    Serial.println("ctrl_off");
  }
  delay(250);
}