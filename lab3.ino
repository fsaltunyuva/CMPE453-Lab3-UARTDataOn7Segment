// 7 Segment Display's a-b-c-d-e-f-g for numbers 0-9 (https://media.geeksforgeeks.org/wp-content/uploads/20200413202916/Untitled-Diagram-237.png)
// a corresponds to PORTD's 5th bit
// b corresponds to PORTD's 7th bit
// c corresponds to PORTB's 4th bit (Only this one requires different PORT)
// d corresponds to PORTD's 3rd bit
// e corresponds to PORTD's 2nd bit
// f corresponds to PORTD's 4th bit
// g corresponds to PORTD's 6th bit
// dot corresponds to PORTB's 3rd bit

// The anode implementation of 7 segment display is used
// So, the bits are set to 1 to turn off the display

void displayDigit(int digit) { // Function to display a digit on the 7 segment display
  switch(digit){ // Switch case to display the corresponding bits for the digit
    case 0: 
      // Turn on a, b, c, d, e, f and turn off g
      PORTB = 0b00001100;
      PORTD = 0b01000000;
      break;
    
    case 1: 
      // Turn on b and c
      PORTB = 0b00001011;
      PORTD = 0b01111111;
      break;

    case 2: 
      // Turn on a, b, d, e, g
      PORTB = 0b00011011;
      PORTD = 0b00010000;
      break;
    
    case 3: 
      // Turn on all bits except c and f
      PORTB = 0b00001011;
      PORTD = 0b00010100;
      break;
    
    case 4: 
      //Turn on b, c, f, and g bits for 4
      PORTB = 0b00001011;
      PORTD = 0b00101100;
      
      delay(1000); // Delay for 1 second

      // Turn on all bits except c and f (for 3)
      PORTB = 0b00001011;
      PORTD = 0b00010100;

      delay(1000); // Delay for 1 second

      // Turn on all bits except c and f (for 2)
      PORTB = 0b00011011;
      PORTD = 0b00010000;

      delay(1000); // Delay for 1 second
               
      // Turn on b and c bits (for 1)
      PORTB = 0b00001011;
      PORTD = 0b01111111;
       
      delay(1000); // Delay for 1 second

      // Turn on all bits except g (for 0)
      PORTB = 0b00001100;
      PORTD = 0b01000000;

      delay(1000); // Delay for 1 second
      break;
    
    case 5: 
      // Turn on all bits except b and e
      //PORTB=0b00001011;
      //PORTD=0b10000100;

      // Turn on all bits except c and f (for 2)
      PORTB = 0b00011011;
      PORTD = 0b00010000;
      break;
    
    case 6: 
      // Turn on all bits except b 
      PORTB = 0b00001011;
      PORTD = 0b10000000;
      break;
    
    case 7: 
      // Turn on a, b, and c bits
      PORTB = 0b00001011;
      PORTD = 0b01011100;
      break;
    
    case 8: 
      // Turn on all bits
      PORTB = 0b00001011;
      PORTD = 0b00000000;
      break;
    
    case 9: 
      // Turn on all bits except e
      PORTB = 0b00001001;
      PORTD = 0b00001100;
      break;
  }
}

void setup() { // Setup function
  Serial.begin(9600);  // Initialize the serial communication at 9600 baud rate
  DDRB = 0xFF; // Set PORTB as output
  DDRD = 0xFF; // Set PORTD as output
}

void loop() {
  if (Serial.available() > 0) { // Check if there is any data available in the serial buffer
    String input = Serial.readStringUntil('\n'); // Read the data from the serial buffer until a newline character
    int number = input.toInt(); // Convert the input string to an integer

    if (input == "d") { // If the input is 'd', turn off the display (set all bits to 1 )
      PORTD = 0xff;
      PORTB = 0xff; 
      return; 
    } 

    if (number >= 0) { // If the input is a positive number, display the number on the 7 segment display
      String numString = String(number); // Convert the number to a string

      for (int i = 0; i < numString.length(); i++) { // Iterate through the digits of the number
        int digit = numString.charAt(i) - '0'; // Get the digit at the current position
        displayDigit(digit); // Display the digit on the 7 segment display
        delay(1000); // Delay for 1 second
      }
    }
  }
}
