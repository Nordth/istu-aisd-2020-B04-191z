uses crt;
const nmax=99;
type massiv=array[1..nmax] of integer;
var n, i: integer;
A: massiv;
procedure Merge(var A: massiv; first, last: integer);
var middle, start, final , j: integer;
mas: massiv;
begin
middle:=(first+last) div 2; 
start:=first; 
final:=middle+1; 
for j:=first to last do 
if (start<=middle) and ((final>last) or (A[start]<A[final])) then
begin
mas[j]:=A[start];
inc(start);
end
else
begin
mas[j]:=A[final];
inc(final);
end;
for j:=first to last do A[j]:=mas[j];
end;
procedure MergeSort(var A: massiv; first, last: integer);
begin
if first<last then
begin
MergeSort(A, first, (first+last) div 2); 
MergeSort(A, (first+last) div 2+1, last); 
Merge(A, first, last); 
end;
end;
begin
clrscr;
write('Размер массива до ',nmax,' n=');
readln(n);
writeln('Исходный массив: ');
for i:=1 to n do
begin
a[i]:= random(50);
write(a[i]:4);
end;
writeln;
MergeSort(A, 1, n); 
writeln('Упорядоченный массив: '); 
for i:=1 to n do 
write(A[i]:4);
readln
end.