
#include"main.h"

extern uint16_t DAC_DataTable[]={\
   409,450,491,532,573,\
   614,655,696,737,778,\
   819,859,900,941,982,   
};

//const uint8_t *DAC_VoltageTable[]={\
//   "0.5V","0.55V","0.6V","0.65V","0.7V",\
//   "0.75V","0.8V","0.85V","0.9V","0.95V",\
//   "1.0V","1.05V","1.1V","1.15V","1.2V",
//};

extern uint8_t *H7826_Gain[]={\
   "1777","3957","8219","16099","30000",\
   "53553","92088","153228","247647","389988",\
   "600000","903899","1336006","1940673","2774562",
};

extern uint8_t *H7826_01_Gain[]={\
   "1250","2580","4998","9182","16125",\
   "27238","44478","70500","108843","164139",\
   "242364","351127","499999","700890","968472",
};

