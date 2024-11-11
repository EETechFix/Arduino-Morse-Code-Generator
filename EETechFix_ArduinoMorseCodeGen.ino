/* Morse Code Generator
Morse code is a character encoding scheme used in telecommunication that encodes text characters
as standardized sequences of two different signal durations called dots and dashes or dits and dahs.
Morse code is named for Samuel Morse (1791 - 1872) an American painter and inventor who is best
remembered for his invention of the single-wire telegraph system and the co-inventor of Morse code
There is no distinction between upper-case and lower-case letters. Each Morse code symbol is formed by a
sequence of dots and dashes. The dot duration is the basic unit of time measurement in Morse code
transmission.

The duration of a dash is three times the duration of a dot. Each dot or dash within
a character is followed by a period of signal absence, called a space, equal to the dot duration.
The letters of a word are separated by a space of duration equal to three dots, and the words are
separated by a space equal to seven dots.
*/

const int speakerPin = 8;
const int dotDelay = 100; // in milliseconds, 100 -200
const int toneHz = 600; //600Hz - 1000Hz

char* letters[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

char* numbers[] = {
"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."}; // 0-9

void setup()
{
pinMode(speakerPin, OUTPUT);
Serial.begin(115200);
Serial.println(" Enter your message, then press Send");
Serial.println(" (Characters text a -z, A-Z, 0 - 9)");
}

void loop()
{
char ch;
if (Serial.available() > 0)
{
ch = Serial.read(); // retrieve letter's code from array
if (ch >= 'a' && ch <= 'z')
{
getCode(letters[ch - 'a']); // 'k'= 107 - 'a'= 97 ('k' - 'a' = 10)
}
else if (ch >= 'A' && ch <= 'Z')
{
getCode(letters[ch - 'A']); // 'A'= 65  'Z' = 90
}
else if (ch >= '0' && ch <= '9')  // '9'= 57
{
getCode(numbers[ch - '0']); // '0'= 48
}
else if (ch == ' ')  // ' ' = space (32)
{
delay(dotDelay * 7); // spacing between words
}
}
}

void getCode(char* string) // sequences through each string retrieve dot or dash element
{
int i = 0;
while (string[i] != '\0')
{
sendElement(string[i]);
i++;
}
delay(dotDelay * 3); // spacing between letters
}


void sendElement(char dotOrDash) // transmit dot or dash element as morse code
{
tone(speakerPin, toneHz);
if (dotOrDash == '.')
{
delay(dotDelay); // dot duration
}
else
{
delay(dotDelay * 3); // dash duration
}
noTone(speakerPin);
delay(dotDelay); // spacing between dots and dashes
}
