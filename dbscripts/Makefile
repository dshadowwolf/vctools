all: docs

docs: markdown pdf

markdown:
	python ./docgen.py ../vcdb . --md

latex: 
	python ./docgen.py ../vcdb . --latex

pdf: latex
	pdflatex vcregs.tex

clean:
	-rm -f instructions/*.pyc
	-rm -f registers/*.pyc
	-rm -f vcregs.md vcregs.tex vcregs.dvi vcregs.pdf vcregs.aux vcregs.out vcregs.toc vcregs.log

