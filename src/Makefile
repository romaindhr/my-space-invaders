CC=gcc -Wall

TARGET=main
CFLAGS=-g -IGraphique -IListeChainee -IControleur -IEntities -I.
LDFLAGS=-lgraph -lSDL -lSDL_ttf -LGraphique
OBJ_PATH = obj

default: step1 step2

step1:
	make -C Graphique
	mkdir -p $(OBJ_PATH)

step2: ${TARGET}

${TARGET}: $(OBJ_PATH)/$(TARGET).o $(OBJ_PATH)/ListeChainee.o $(OBJ_PATH)/enemies.o $(OBJ_PATH)/ship.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
$(OBJ_PATH)/ListeChainee.o: ListeChainee/ListeChainee.c Graphique/libgraph.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_PATH)/enemies.o: Entities/enemies.c define.h ListeChainee/ListeChainee.h Graphique/libgraph.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_PATH)/ship.o: Entities/ship.c define.h ListeChainee/ListeChainee.h Graphique/libgraph.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_PATH)/main.o: $(TARGET).c define.h ListeChainee/ListeChainee.h Entities/enemies.h Entities/ship.h
	$(CC) -o $@ -c $< $(CFLAGS)

# .c.o:
# 	$(CC) $(CFLAGS) -c $<^

clean:
	rm -r -f -d ./$(OBJ_PATH) ./${TARGET}
	make -C Graphique -f Makefile $@
format: 
	clang-format -i -style="WebKit" main.c define.h ListeChainee/ListeChainee.c ListeChainee/ListeChainee.h Entities/ship.c Entities/ship.h Entities/enemies.c Entities/enemies.h
