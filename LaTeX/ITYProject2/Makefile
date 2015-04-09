all: ITYProject2.pdf

ITYProject.pdf: ITYProject2.tex
	latex ITYProject2.tex
	latex ITYProject2.tex
	dvips ITYProject2.dvi
	ps2pdf -sPAPERSIZE=a4 ITYProject2.ps

clean:
	rm *.ps *.aux *.dvi *.log *.pdf
