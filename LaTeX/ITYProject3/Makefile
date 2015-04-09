all: ITYProject3.pdf

ITYProject3.pdf: ITYProject3.tex title.tex etiopan.eps oniisan.eps oniisan2.eps
	latex ITYProject3.tex
	latex ITYProject3.tex
	dvips ITYProject3.dvi
	ps2pdf -sPAPERSIZE=a4 ITYProject3.ps

clean:
	rm *.ps *.aux *.dvi *.log *.pdf

