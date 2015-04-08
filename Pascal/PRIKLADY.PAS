program priklady;
uses Crt;
var i,n,s : integer;
    x : array [1..100] of integer;          {Tu sa nacitaju vsetky cisla}
    c : array [1..100] of char;             {Tu sa nacitaju vsetky znamienka vratane =}

begin
  Clrscr;
  write('Zadaj pocet cisel v prikalde: ');
  readln(n);
  for i:=1 to N do begin
    readln(x[i]);
    if i<N then readln(c[i]);                            {Nacita sa cislo v ria}
  end;

  s:=x[1];                                  {Vysledku priradi prve cislo}
  for i:=2 to N do begin                    {Teraz bude priratavat alebo odratavat kazde dalsie cislo}
    if c[i-1]='+' then s:=s+x[i]            {Ak bude zanmienko pred cislom + tak to cislo pricita}
    else if c[i-1]='-' then s:=s-x[i]       {Ak to bude - tak odcita}
    else if c[i-1]='*' then s:=s*x[i]       {Ak * tak cely vysledok vynasobi tym cislom}
    else if c[i-1]='/' then s:=s div x[i];  {... krát a delene nemá prednost, okrem toho,nedba}
  end;
  writeln('Celkovy vysledok je: ',s);       {Uz vysledok iba vypise...}
  readln;                                   {Pozdrzanie programu...}
end.
