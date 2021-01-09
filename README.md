# FEUP-RCOM

This is a repository containing the projects for the classes of [Computer Networks](https://sigarra.up.pt/feup/pt/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=459483).  
__Grades__: 
- 1st projetct: 19
- 2nd project: 18.5 


## First project

This project consisted on implementing a code that enables the safe file transfer between two computers by serial port using the [stop and wait](https://en.wikipedia.org/wiki/Stop-and-wait_ARQ)
protocol.  
The source can be checked at [proj 1](https://github.com/Jumaruba/FEUP-RCOM/tree/master/proj_1) folder.  
## How to execute 
In order to execute the program you need to have the program in two computer connected by a serial port.  
- Compile the program in both computers by using `make`. 
- For the computer that will send the file, type: 
```bash 
./reader [serial port number] [file name] 
```
- For the computer that will receive the file, type: 
```c
./writer [serial port number] <file name> 
```

## Second project 

The second project was divided in two segmentations: 
- Development of a program to automate the ftp protocol   
- Experiments in lab  

The result for the experiments can be checked in the report at the folder [proj 2](https://github.com/Jumaruba/FEUP-RCOM/tree/master/proj_2).  

## How to execute 

In order to execute program to automate the ftp protocol, follow these steps: 
- Compile the program by using `make`.  
- You can use the program by following this execution format: 
```bash 
./download ftp://user:pass@server/path
```
