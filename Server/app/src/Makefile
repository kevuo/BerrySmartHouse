APP=SmartBerryWrapper
OP=libgpio
SRC=$(APP).c
EXE=../bin/$(APP)
CFLAG+=-I../include
LD_FLAGS+=-L../lib/ -lgpio -ljson
EXE_MSG="Generando ejecutable..."
CLN_MSG="Borrando ejecutable..."

all: del $(EXE)

del:
		rm ../lib/gpio.o
		
$(EXE):
		@echo $(value EXE_MSG)
		$(CC) -o $(EXE) $(SRC) $(CFLAG) $(LD_FLAGS)

clean:
		@echo $(value CLN_MSG) 	
		rm $(EXE)
