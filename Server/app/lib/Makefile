APP=gpio
SRC=$(APP).c
OBJ=$(APP).o
CFLAG+=-I../include
DYNAMIC=lib$(APP).so
DYN_MSG="Creando biblioteca dinamica..."
COMP_MSG="Compilando gpio.c..."
CLN_MSG="Borrando bibliotecas..."

all: $(OBJ) $(DYNAMIC)

$(DYNAMIC): $(OBJ)
		@echo $(value DYN_MSG)
		$(CC) $(CFLAG) -c -fpic $(SRC)
		$(LD) $(CFLAG) -o $(DYNAMIC) $(OBJ) -shared

$(OBJ): $(SRC)
		@echo $(value COMP_MSG)
		$(CC) -c $(CFLAG) $(SRC)

clean:
		@echo $(value CLN_MSG)	
		rm $(DYNAMIC)