String  print_time ()
{

  Time t = rtc.time();

  memset(day, 0, sizeof(day));
  switch (t.day)
  {
  case 1: 
    strcpy(day, "Sunday"); 
    break;
  case 2: 
    strcpy(day, "Monday"); 
    break;
  case 3: 
    strcpy(day, "Tuesday"); 
    break;
  case 4: 
    strcpy(day, "Wednesday"); 
    break;
  case 5: 
    strcpy(day, "Thursday"); 
    break;
  case 6: 
    strcpy(day, "Friday"); 
    break;
  case 7: 
    strcpy(day, "Saturday"); 
    break;
  }

  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d", day, t.yr, t.mon, t.date, t.hr, t.min, t.sec);

  String str(buf);

  return str;

  //"ACCES: " + print_time ()
}


void save(){

  // x ++;


  //if( lock == false ){


  if(acces == true && lock == false ){
   // delay(2500);
    myFile = SD.open("danel.txt", FILE_WRITE);

    if(myFile){
      String w = "ACCES: " + print_time () ;      
      myFile.println(w);
      myFile.close();
      num = 0;
    }
  } 
   if ( acces == false){
     delay(2500);
    myFile = SD.open("teest.txt", FILE_WRITE);
    if(myFile){
      String c = "DENIED: " + print_time () + " || Card number: " + num;      
      myFile.println(c);
      myFile.close();
      num = 0;
    }



  }


  //  }

  //  else{
  //
  //    x = 0;
  //  }


}


//void Read(){
//  char debug = Serial.read();
//
//  if(debug == 'r'){
//
//    Serial.print("Acces list:");
//    Serial.println(" ");
//
//
//    for(int i = 0; i < 10; i++){
//      if(data [i] != 0){
//
//        Serial.println(data[i]);
//      }
//
//    }
//
//  }
//}




