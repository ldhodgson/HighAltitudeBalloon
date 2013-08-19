// Author: Liam Hodgson
// Purpose: Extract the latitude, longitude and altitude from the gps data.

char GPGGA[6] = "GPGGA";
bool flag = false;
int commaCount;
char c;
bool endFlag = false;

void setup(){
  Serial.begin(9600);
}

//****Prints out the type of message string being received.
//void loop(){
//  
//  if(Serial.available()){
//    if(Serial.read() == '$'){ //checks if start of string
//      c = '\0';
//      do{
//        if(Serial.available()){
//          Serial.print(c);
//          c = Serial.read();
//        }
//      }while(c != ',');
//      
//      Serial.println();  
//    }
//  
//  flag = false;
//  
//  }
//}

//****Filters out the message string we don't need (only want GPGGA)
//void loop(){
//  
//  if(Serial.available()){
//    if(Serial.read() == '$'){ //checks if start of string
//      int i = 0;
//      do{
//        if(Serial.available()){
//          if(Serial.read() != GPGGA[i]){ //checks if next character in string matches correct string
//            Serial.println("Nope.");
//            flag = true;
//            break;
//          }
//          i++;
//        }
//      }while(i < 5); //only loops for first 5 characters after '$'
//      
//      if(flag == false)
//        Serial.println("Yup.");  
//    }
//  
//  flag = false;
//  
//  }
//}

void loop(){
  
  if(Serial.available()){
    c = Serial.read();
    if(c == '$'){ //checks if start of string
    Serial.print('a');
      int i = 0;
      do{
        if(Serial.available()){
          if(Serial.read() != GPGGA[i]){ //checks if next character in string matches correct string
            flag = true;
            break;
          }
          i++;
        }
      }while(i < 5); //only loops for first 5 characters after '$'
      
      if(flag == false) //extracts lat, long, alt
        commaCount = 0;
        do{
          if(Serial.available()){
            c = Serial.read(); 
            if(c == ',')
              commaCount++;
            if(commaCount == 2 || commaCount == 4 || commaCount == 8){
              if(commaCount == 8)
                endFlag = true; // flag if end of data string
              do{
                Serial.print('b');
                if(Serial.available()){ // reads GPS data until next comma
                  c = Serial.read();
                  Serial.print(c);
                }
              }while(c != ',');
              Serial.println();
              commaCount++;
            }
          }
        }while(endFlag == false);
    }
  
  flag = false;
  endFlag = false;
  
  }
}
