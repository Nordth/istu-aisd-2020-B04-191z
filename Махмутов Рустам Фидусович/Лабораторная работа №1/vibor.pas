uses crt;
const nmax=99;
type mas=array [1..nmax]of integer;
procedure selection(var a:mas;n:integer);
var l,r,i,j,x,buf:integer;
begin
l:=1;
r:=n;
repeat
x:=l;
for j:=l+1 to r do
if a[j]<a[x] then x:=j;
buf:=a[l];
a[l]:=a[x];
a[x]:=buf;
inc(l);
r:=n;
x:=r;
for j:=r-1 downto l do
if a[j]>a[x] then x:=j;
buf:=a[r];
a[r]:=a[x];
a[x]:=buf;
dec(r);
until l>=r;
end;
var a:mas;
    n,i:integer;
Begin
clrscr;
randomize;
repeat
write('Размер массива до ',nmax,' n=');
readln(n);
until n in [1..nmax];
writeln('Исходный массив:');
for i:=1 to n do
 begin
  a[i]:=random(50);
  write(a[i]:4);
 end;
writeln;
selection(a,n);
writeln('Упорядоченный массив: ');
for i:=1 to n do
write(a[i]:4);
readln
end.