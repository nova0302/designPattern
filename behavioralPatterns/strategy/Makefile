CC =g++
#CFLAGS =-g -lm -std=c99
CFLAGS =-g -lm

PGM =strategy.exe

VPATH = $(SDIR)
SDIR =src
ODIR =obj
_OBJS =$(basename $(PGM)).o
OBJS =$(addprefix $(ODIR)/, $(_OBJS))
SRCS =$(OBJS:.o=.c)


$(PGM): $(OBJS)
	@echo "---------- Building the program ----------"
	$(CC) $(CFLAGS) -o $@ $^ && echo "------ Runing the program ------" && ./$(PGM)
run:
	$(PGM)

$(ODIR)/%.o:$(SDIR)/%.cpp
	@echo " -----   Compiling $<  --------"
	@if [ ! -d $(ODIR) ]; then echo "Creating obj directory" && mkdir $(ODIR); fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(ODIR)/%.o:$(SDIR)/%.cc
	@echo " -----   Compiling $<  --------"
	@if [ ! -d $(ODIR) ]; then echo "Creating obj directory" && mkdir $(ODIR); fi
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf $(PGM) $(ODIR) *.stackdump *.o *.exe

.PHONY: check-syntax

check-syntax:
	$(CC) $(CHK_SOURCES)
show:
	@echo $(OBJS) $(SRCS)
