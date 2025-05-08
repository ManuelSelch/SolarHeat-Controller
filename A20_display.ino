#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setupDisplay() {
  u8g2.begin();
}

void updateDisplay() {
  printDisplaySecurity();
  delay(2000);
  printDisplayNormal();
  delay(2000);
}

void printDisplayNormal(){
    u8g2.clearBuffer();         
    u8g2.setFont(u8g2_font_fub30_tf);  
    u8g2.setCursor(0,32);   
    
    u8g2.print(String(tempSolar));  
    


    u8g2.setFont(u8g2_font_t0_15_tf);  
    u8g2.setCursor(80,32);       
    u8g2.print("Solar");     
       
    u8g2.setFont(u8g2_font_fub30_tf);  
    u8g2.setCursor(0,64);       
    u8g2.print(String(tempTank));     

    u8g2.setFont(u8g2_font_t0_15_tf);  
    u8g2.setCursor(80,64);       
    u8g2.print("Keller"); 
    u8g2.sendBuffer();    
  
}



void printDisplaySecurity(){
    Serial.print("display security: ");
    Serial.println(tempSecurity);
    
    u8g2.clearBuffer();         
    u8g2.setFont(u8g2_font_fub30_tf);  
    u8g2.setCursor(0,32);   
    u8g2.print(String(tempSecurity));  

         
    u8g2.setFont(u8g2_font_t0_15_tf);  
    u8g2.setCursor(80,32);       
    u8g2.print("Security");     
    u8g2.sendBuffer();    
}
