all: ITYProject.pdf

ITYProject.pdf: ITYProject.tex
	latex ITYProject.tex
	latex ITYProject.tex
	dvips ITYProject.dvi
	ps2pdf -sPAPERSIZE=a4 ITYProject.ps

clean:
	rm *.ps *.aux *.dvi *.log *.pdf
