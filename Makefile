CC = cc65
AS = ca65
LN = ld65

CFLAGS = -t none -O --cpu 65sc02
AFLAGS = --cpu 65sc02
LFLAGS = -C gametank-8k.cfg
LLIBS = lib/gametank.lib

SDIR = src
ODIR = build

_COBJS = hello.o gametank.o
COBJS = $(patsubst %,$(ODIR)/%,$(_COBJS))
_AOBJS = vectors.o wait.o interrupt.o
AOBJS = $(patsubst %,$(ODIR)/%,$(_AOBJS))


$(ODIR)/%.si: src/%.c src/%.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

$(ODIR)/%.si: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

$(ODIR)/%.o: $(ODIR)/%.si
	mkdir -p $(@D)
	$(AS) $(AFLAGS) -o $@ $<

$(ODIR)/%.o: src/%.s
	mkdir -p $(@D)
	$(AS) $(AFLAGS) -o $@ $<

$(ODIR)/hello.gtr: $(AOBJS) $(COBJS)
	mkdir -p $(@D)
	$(LN) $(LFLAGS) $^ -o $@ $(LLIBS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*