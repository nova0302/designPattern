CC =g++
#CFLAGS =-g -std=c99

PGM =main.exe

VPATH = $(SDIR)
SDIR =.
ODIR =.
_OBJS =$(basename $(PGM)).o
OBJS =$(addprefix $(ODIR)/, $(_OBJS))
SRCS =$(OBJS:.o=.c)


$(PGM): $(OBJS)
	$(CC) -o $@ $^ && echo "Runing the program" && ./$(PGM)

$(ODIR)/%.o:$(SDIR)/%.cpp
	@echo "Compiling $<"
	@if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(PGM) $(ODIR) *.stackdump *.o *.exe

.PHONY: check-syntax

check-syntax:
	$(CC) $(CHK_SOURCES)
show:
	@echo $(OBJS) $(SRCS)
