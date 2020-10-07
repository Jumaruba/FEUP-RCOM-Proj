vpath %.h 	./include 
vpath %.c 	./src
 
CC = gcc 
CFLAGS = -Wall  

SRC_DIR = ./src 
COMMON_SRCS := utils.c  
COMMON_SRC 	:= $(addprefix $(SRC_DIR)/,$(COMMON_SRC))  	# src/common_srcs.c 
COMMON_SRC_OBJ = $(COMMON_SRC:%.c=%.o)  				# common .o files 

MAIN_SRCS := reader.c writer.c  
MAIN_SRC  := $(addprefix $(SRC_DIR)/, $(MAIN_SRCS))		# src/main_srcs.c							 

OBJECTS :=  $(COMMON_SRC_OBJ) writer.o reader.o  		# all .o files 
TARGETS = reader writer 
all: $(TARGETS) 

.PHONY: all 

reader: $(OBJECTS)
	@$(CC) $(CFLAGS) -o reader $(COMMON_SRC_OBJ) reader.o
	@echo "reader generated successfully!" 
	

writer: $(OBJECTS)
	@$(CC) $(CFLAGS) -o writer $(COMMON_SRC_OBJ) writer.o  
	@echo "writer generated successfully!" 

$(OBJECTS): %.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@  
	
.PHONY: clean 
clean: 
	@rm -r *.o $(TARGETS) 
	@echo ".o and ./ files cleaned!" 