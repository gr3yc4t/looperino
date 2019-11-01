#ifndef DEBUG_GUARD
#define DEBUG_GUARD

//#define DEBUG

inline void debug(const char *message){
  #ifndef DEBUG
    ;
  #else
    Serial.println(message);
  #endif 
}

inline void debug(unsigned int num){
  #ifndef DEBUG
    ;
  #else
    Serial.println(num);
  #endif 
}



#endif
