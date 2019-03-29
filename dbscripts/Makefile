PYTHON = python
PDFLATEX = pdflatex
PDF2PS = pdf2ps
MARKDOWN = markdown

all: docs

docs: markdown html pdf ps

markdown:
	$(PYTHON) ./docgen.py ../vcdb . --md

html: markdown
	$(MARKDOWN) ./vcregs.md > vcregs.html

latex: 
	$(PYTHON) ./docgen.py ../vcdb . --latex

pdf: latex
	$(PDFLATEX) vcregs.tex

ps: pdf
	$(PDF2PS) vcregs.pdf vcregs.ps

clean:
	-rm -f instructions/*.pyc
	-rm -f registers/*.pyc
	-rm -f vcregs.md vcregs.html vcregs.tex vcregs.dvi vcregs.pdf vcregs.ps vcregs.aux vcregs.out vcregs.toc vcregs.log

