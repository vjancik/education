program palindrom;
uses Crt;
var i,l,n,max,d : integer;
    sedi : boolean;
    a : array [1..1000] of char;
begin
  Clrscr;
  write('Zadaj dlzku retazca: ');
  readln(N);
  write('Zadaj retazec: ');
  for i:=1 to N do read(a[i]);
  readln;
  max:=1;
  sedi:=true;
  for i:=2 to N-1 do begin
    l:=1;
    d:=1;
    sedi:=true;
    while sedi=true do begin
      if ((i-l)>0) AND ((i+l)<=N) then
        if a[i-l]=a[i+l] then begin
          d:=d+2; l:=l+1;
          if max<d then max:=d;
        end
        else sedi:=false
      else sedi:=false;
    end;
  end;
  if max<>1 then writeln('Najdlhsi Palindrom ma dlzku: ',max)
  else writeln('Palindrom sa tu nenachadza.');
  readln;
end.