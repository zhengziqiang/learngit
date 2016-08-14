# Makefile
MD = markdown
MDFLAGS = -T
H2P = xhtml2pdf
H2PFLAGS = --html
SOURCES := $(wildcard *.md)
OBJECTS := $(patsubst %.md, %.html, $(wildcard *.md))
OBJECTS_PDF := $(patsubst %.md, %.pdf, $(wildcard *.md))
all: build
build: html pdf
pdf: $(OBJECTS_PDF)
html: $(OBJECTS)
$(OBJECTS_PDF): %.pdf: %.html
    $(H2P) $(H2PFLAGS) $< > $@ 
$(OBJECTS): %.html: %.md
    $(MD) $(MDFLAGS) -o $@ $<
clean:
	rm -f $(OBJECTS)
