vpath %.h 	./include 
vpath %.c 	./src
 
CC = gcc 
CFLAGS = -Wall  

SRC_DIR = ./src 
COMMON_SRCS := input_handler.c client.c io.c utils.c
COMMON_SRC_OBJ = $(COMMON_SRCS:%.c=%.o)  					# common .o files 

MAIN_SRCS := download.c

OBJECTS :=  $(COMMON_SRC_OBJ) download.o 		# all .o files 
TARGETS = download
all: $(TARGETS) 

.PHONY: all 
	
download: $(OBJECTS)
	@$(CC) $(CFLAGS) -o download $(COMMON_SRC_OBJ) download.o
	@echo "download generated successfully!" 

$(OBJECTS): %.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@  
	
.PHONY: clean 
clean: 
	@rm -r *.o $(TARGETS) 
	@echo ".o and ./ files cleaned!" 
