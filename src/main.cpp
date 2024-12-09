#include <Arduino.h>
#define RED_PIN 32
#define YELLOW_PIN 33
#define GREEN_PIN 25
#define BUZZER_PIN 15
#define BUTTON_PIN 21
#define RED_STATE 0
#define RED_YELLOW_STATE 1
#define YELLOW_STATE 2
#define GREEN_STATE 3
#define RED_MILLIS 10000
#define GREEN_MILLIS 5000
#define RED_YELLOW_MILLIS 2000
int tl_state; // Traffic light state.
unsigned long tl_timer; // Traffic light timer.
int buttonState = 0;

void red_light()
{
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
}
void red_yellow_light()
{
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
}
void yellow_light()
{
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
}
void green_light()
{
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
}
void green_sound()
{
    tone(BUZZER_PIN, 1000); 
    delay(500);        
    noTone(BUZZER_PIN);
    delay(1500);
}
void red_sound()
{
    tone(BUZZER_PIN, 1000); 
    delay(250);        
    noTone(BUZZER_PIN);
    delay(250);
}
void setup()
{
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    tl_state = RED_STATE;
    tl_timer = millis() + RED_MILLIS;
}
void loop()
{
    tl_timer--;
    buttonState = digitalRead(BUTTON_PIN);
    switch (tl_state)
    {
        case RED_STATE:
            red_light();
            red_sound();
            if (tl_timer == 0) 
            {
                tl_timer = millis() + RED_YELLOW_MILLIS;
                tl_state = RED_YELLOW_STATE;
            }
            break;
        case RED_YELLOW_STATE:
            red_yellow_light();
            noTone(BUZZER_PIN);
            if (tl_timer == 0)
            {
                tl_timer = millis() + GREEN_MILLIS;
                tl_state = GREEN_STATE;
            }
            break;
        case YELLOW_STATE:
            yellow_light();
            noTone(BUZZER_PIN);
            if (tl_timer == 0)
            {
                tl_timer = millis() + RED_MILLIS;
                tl_state = RED_STATE;
            }
            break;
        case GREEN_STATE:
            green_light();
            green_sound();
            if (tl_timer <= 0 && buttonState)
            {
                tl_timer = millis() + RED_YELLOW_MILLIS;
                tl_state = YELLOW_STATE;
            }
            break;
    }
}