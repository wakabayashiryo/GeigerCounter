import math as mt

Ref_Vol = 5.0
Data_list = []
Vol_list = []

with open("table.c",mode="w") as table:

    table.write("const uint16_t DAC_DataTable={\\\n   ")
    for (i,Data) in enumerate(range(50,125,5)):
        Data_list.append(mt.floor(0x0FFF*(Data/100)/Ref_Vol))
        table.write(""+str(Data_list[i])+",")
        if((i+1) % 5==0):
            table.write("\\\n   ")
    table.write("\n};\n")
    
    table.write("const uint8_t *DAC_VoltageTable={\\\n   ")
    for (i,vol) in enumerate(Data_list):
        Vol_list.append(round(Ref_Vol*vol/0x0FFF,2))
        table.write('"'+str(Vol_list[i])+'V",')  
        if((i+1) % 5==0):
            table.write("\\\n   ")
    table.write("\n};\n")

    table.write("const uint32_t H7826_Gain={\\\n   ")
    for (i,data) in enumerate(Vol_list):
        table.write('"'+str(mt.floor(6e5*data**8.399))+'",') #y=6e5*x**8.399
        if((i+1) % 5==0):
            table.write("\\\n   ")
    table.write("\n};\n")

    table.write("const uint32_t H7826_01_Gain={\\\n   ")
    for (i,data) in enumerate(Vol_list):
        table.write('"'+str(round(mt.floor(242364*data**7.598),3))+'",') #y=242364*x**7.598
        if((i+1) % 5==0):
            table.write("\\\n   ")
    table.write("\n};\n")

table.close()

